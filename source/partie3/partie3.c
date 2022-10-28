#include "../../headers/partie3.h"
#include "../../headers/partie1.h"

//Exercice 5
// LISTE CHAINEE DE CLES
//Q5.1
CellKey* create_cell_key(Key* key){
    CellKey* cell_key = (CellKey*) malloc(sizeof(CellKey));
    if(cell_key == NULL){
        printf("Erreur allocation dans fonction : create_cell_key\n");
        return NULL;
    }
    cell_key->data = key;
    cell_key->next = NULL;

    return cell_key;
}

//Q5.2
void ajouter_cle(Key* key, CellKey** cell_key){
    //cas 1 : la liste est vide
    if(*cell_key == NULL){
        *cell_key = create_cell_key(key);
        return;
    }
     //cas 2 : la liste n'est pas vide
    CellKey* tmp = *cell_key;
    while(tmp->next != NULL){
        tmp = tmp->next;
    }
    tmp->next = create_cell_key(key);
    cell_key = &tmp;
}


//Q5.3  FONCTIONNE
CellKey* read_public_keys(char* nom){
    FILE* f = fopen(nom, "r");
    if (f == NULL){
        printf("Erreur ouverture du fichier dans fonction : read_public_keys\n");
        return NULL;
    }
    char temp[256];
    char val[256] = ""; 
    char n[256] = "";
    char cle_p[512];
    CellKey* cell_key = NULL;
   
    while(fgets(temp, 256, f) != NULL){
        sscanf(temp,"%s,%s\n", val, n);
        sprintf(cle_p, "%s %s", val, n);
        Key *pKey = str_to_key(cle_p);
        ajouter_cle(pKey, &cell_key);
    }
    
    fclose(f);
    return cell_key;
}

//Q5.4
void print_list_key(CellKey* LCK){
    while(LCK != NULL){
        printf("(%lx, %lx)\n", LCK->data->val, LCK->data->n);
        LCK = LCK->next;
    }
    return;
}

//Q5.5
void delete_cell_key(CellKey* c){
    free(c->data);
    free(c);
}

void delete_list_keys(CellKey* c){
    CellKey* tmp;
    while(c != NULL){
        tmp = c->next;
        delete_cell_key(c);
        c = tmp;
    }
    free(c);
    
}

//LISTE CHAINEE DE DECLARATION SIGNEES
//Q5.6
CellProtected* create_cell_protected(Protected* pr){
    CellProtected* cp = (CellProtected*)malloc(sizeof(CellProtected));
    if(cp == NULL){
        printf("Erreur allocation dans fonction : create_cell_protected\n");
        return NULL;
    }
    cp->data = pr;
    cp->next = NULL;
    return cp;
}

//Q5.7
void ajout_declaration(CellProtected** cp, Protected* pr){
    
    //cas 1 : liste vide
    if(*cp == NULL){
        *cp = create_cell_protected(pr);
        return;
    }
     //cas 2 : liste non vide
    CellProtected* tmp = *cp;
    while(tmp->next != NULL){
        tmp = tmp->next;
    }
    tmp->next = create_cell_protected(pr);
    cp = &tmp;
}

//Q5.8
CellProtected* read_protected(char* nom){
    FILE* f = fopen(nom, "r");
    if (f == NULL){
        printf("Erreur ouverture du fichier dans fonction : read_protected\n");
        return NULL;
    }
    char temp[256], mess[150];
    char cle_p[150];
    char sgn[256];
    CellProtected* cp = NULL;

    
    while(fgets(temp, 256, f) != NULL){
        sscanf(temp, "%s %s %s", cle_p, mess, sgn);
        Key* pKey = str_to_key(cle_p);
        Signature* signature = str_to_signature(sgn);
        Protected *p = init_protected(pKey, mess, signature);
        ajout_declaration(&cp, p);
    }
   
    fclose(f);
    
    return cp;
    
}

//Q5.9
void print_list_pr(CellProtected* cp){
    if(cp == NULL){
        printf("liste vide\n");
    }
    while(cp != NULL){
        char *s = protected_to_str(cp->data);
        printf("%s\n\n", s);
        free(s);
        cp = cp->next;
    }
    
}

//Q5.10
void delete_cell_protected(CellProtected* c){
    free(c->data->message);
    free(c->data->signature);
    free(c->data);
    c->next = NULL;
    free(c);
}

void delete_liste_protected(CellProtected *c){
    while(c != NULL){
        CellProtected* tmp = c->next;
        delete_cell_protected(c);
        c = tmp;
    }
    free(c);
}



