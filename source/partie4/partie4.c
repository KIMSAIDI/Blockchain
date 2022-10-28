#include "../../headers/partie4.h"

//Exercice 6
//Q6.1
void verify_list_protected(CellProtected** cp){
    CellProtected *tmp;
    CellProtected *prec, *nouv_tete;
    int nb_non_valide = 0;

    tmp = *cp;
    while (tmp){
        CellProtected *to_del;
        if (verify(tmp->data) == 1){ // signature valide
            prec = tmp;
            tmp = tmp->next;
        
        }else{ // signature invalide
            nb_non_valide += 1;
            if (prec){ // Si on a un element precedent
                prec->next = tmp->next;
                delete_cell_protected(tmp);
                tmp = prec->next;

            }else{ // pas d'element precedent --> tete de liste
                nouv_tete = tmp->next;
                delete_cell_protected(tmp);
                *cp = nouv_tete;
                tmp = nouv_tete;
            }
        }
    }
    printf("nombre de declaration non valide\n : %d", nb_non_valide);
    return;

}

    


//Q6.2
HashCell* create_hashcell(Key* key){
    HashCell *hash_cell = (HashCell*)malloc(sizeof(HashCell));
    if(hash_cell == NULL){
        printf("Erreur : allocation dans fonction hashcell\n");
        return NULL;
    }
    hash_cell->key = key;
    hash_cell->val = 0;
    return hash_cell;
}

void print_hashcell(HashCell* h){
   
    printf("cle : %s, a vote : %d\n", key_to_str(h->key), h->val);

}

//Q6.3
int hash_function(Key* key, int size){
    float nb = (sqrtf(5)-1)/2; //Nombre d'or
    return ((int) floor(size * (key->val * nb - floor(key->val * nb))));
}


//Fonction intermediaire : utiliser dans le main
int find(CellKey* tab, Key* key){
    while(tab != NULL){
        if (tab->data->n == key->n && tab->data->val == key->val){
            return 0;
        }
        tab = tab->next;
    }
    return 1;
}

//Fonction intérmediaire : renvoie 1 si deux cles sont egales, 0 sinon
int compare_key(Key* key1, Key* key2){
    if(key1->n == key2->n && key1->val == key2->val){
        return 1;
    }
    return 0;
}


//Q6.4
int find_position(HashTable* t, Key* key){
    int i = 0;
    int g = hash_function(key, t->size);
    //Probing lineaire modulé par la taille du tableau
    int h = (g + i)%(t->size);

    while(t->tab[h] != NULL){
        if(compare_key(t->tab[h]->key, key) == 1){ //Si key se trouve dans le tableau
            return h;
        }
        h = (g + i)%(t->size);
        i++;
    }
    return h;
}

//Q6.5
HashTable* create_hashtable(CellKey* keys, int size){
    HashTable* t = (HashTable*)malloc(sizeof(HashTable));
    t->tab = (HashCell**)malloc(sizeof(HashCell)*size);
    if(t == NULL && t->tab == NULL){
        printf("Erreur allocation fonction : create_hashtable\n");
        return NULL;
    }

    t->size = size; 
    for(int i = 0; i < t->size; i++){
	    t->tab[i] = NULL;
    }
    int ind;
    while(keys != NULL){
        ind = find_position(t, keys->data);
        t->tab[ind] = create_hashcell(keys->data);
        keys = keys->next;
    }
    
    return t;
}
    
    

void print_hashtable(HashTable* t){
    for(int i = 0; i < t->size; i++){
        print_hashcell(t->tab[i]);
    }
}

//Q6.6
void delete_hashtable(HashTable* t){
    int taille = t->size;
    if(t == NULL){
        return;
    }
    for(int i=0; i<taille; i++){
        free(t->tab[i]);
    }
    free(t);
    return;
}


//Q6.7
Key *compute_winner(CellProtected *decl, CellKey *candidates, CellKey *voters, int sizeC, int sizeV){
    HashTable* Hc = create_hashtable(candidates, sizeC);
    HashTable* Hv = create_hashtable(voters, sizeV);
    int indC, indV;
    Key* mess;
    
    while(decl){
        indV = find_position(Hv, decl->data->pKey);
        mess = str_to_key(decl->data->message);
        indC = find_position(Hc, mess);

        //On verifie que les cles correspondent et que le votant n'a pas deja voter         
        if(Hv->tab[indV] != NULL && Hv->tab[indV]->val == 0 && compare_key(Hc->tab[indC]->key, mess) == 1){
            Hv->tab[indV]->val = 1;
            //On ajoute un point pour le candidats
            Hc->tab[indC]->val++;
        }
        
        free(mess);   
        decl = decl->next;
    }


    int max = 0;
    int posmax;
    Key* gagnant = (Key*)malloc(sizeof(Key));
    Key* tmp;
    if(gagnant == NULL){
        printf("erreur allocation cle : compute winner\n");
    }

    while(candidates != NULL){
        posmax = find_position(Hc, candidates->data);

        if(Hc->tab[posmax] != NULL && Hc->tab[posmax]->val > max){ 
            max = Hc->tab[posmax]->val;
            tmp = Hc->tab[posmax]->key;
            init_key(gagnant, tmp->val, tmp->n);
        }
        candidates = candidates->next;
    }


    delete_hashtable(Hc);
    delete_hashtable(Hv);

    return gagnant;
   
}
