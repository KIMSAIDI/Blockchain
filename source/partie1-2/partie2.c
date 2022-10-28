#include "../../headers/partie1.h"
#include "../../headers/partie2.h"

//MANIPULATION DES CLES
//Q3.2
void init_key(Key* key, long val, long n){
    key->val = val;
    key->n = n;
    return;
}
//Q3.3
void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size){
    long p = random_prime_number(low_size, up_size, 5000);
    long q = random_prime_number(low_size,up_size, 5000);
    long n, s, u;
    generate_key_values(p,q,&n,&s,&u);
    if (u < 0){
        long t = (p-1)*(q-1);
        u = u + t; 
    }
    init_key(pKey, s, n);
    init_key(sKey, u, n);
    return;
}

//Q3.4
char* key_to_str(Key* key){
    if(key == NULL){
        printf("Erreur : key == NULL\n");
        exit(1);
    }
    char *message = (char*)malloc(256 * sizeof(char));
    //On ecrit dans message les valeurs val et n, contenues dans la structure Key
    sprintf(message, "(%lx,%lx)", key->val, key->n);
    
    return message;
}

Key* str_to_key(char* str){
    Key* key = (Key*)malloc(sizeof(Key));
    long val, n;
    if(key == NULL){
        printf("Erreur : alloction de la cle dans str_to_key\n");
        return NULL;
    }
    //on copie les valeurs contenues dans str pour les stocker dans val et n;
    sscanf(str, "(%lx,%lx)", &val, &n);
    init_key(key, val, n);
    return key; 
}


//SIGNATURE
//Q3.6
Signature* init_signature(long* content, int size){
    Signature* tab = (Signature*)malloc(sizeof(Signature));
    if(tab == NULL){
        printf("Erreur : allocation dans fonction init_signature\n");
        return NULL;
    }
    tab->size = size;
    tab->content = content;

    return tab;
}

//Q3.7
Signature* sign(char* mess, Key* sKey){
    long* content = encrypt(mess, sKey->val, sKey->n);
    int size = strlen(mess);

    return init_signature(content, size);
    
}

//Q3.8 
char* signature_to_str(Signature* sgn){
    char* result = malloc(10*sgn -> size*sizeof(char));
    result[0]='#';
    int pos=1;
    char buffer[156];
    for(int i=0; i < sgn->size; i++){
        sprintf(buffer, "%lx", sgn->content[i]);
        for(int j=0; j < strlen(buffer);j++){
            result[pos] = buffer[j];
            pos = pos + 1;
        }
        result[pos] = '#';
        pos=pos+1;
    }
    result[pos]='\0';
    result = realloc(result, (pos+1)*sizeof(char));
    return result;
}

Signature* str_to_signature(char* str){
    int len = strlen(str);
    long* content = (long*)malloc(sizeof(long)*len);
    int num = 0;
    char buffer[256];
    int pos=0;
    for(int i=0; i<len; i++){
        if(str[i] != '#'){
            buffer[pos] = str[i];
            pos=pos+1;
        }else{
            if(pos!=0){
                buffer[pos] = '\0';
                sscanf(buffer, "%lx", &(content[num]));
                num=num+1;
                pos=0;
            }
        }
    }
    content=realloc(content, num*sizeof(long));
    return init_signature(content, num);
}

//DECLARATIONS SIGNEES 
//Q3.10
Protected* init_protected(Key* pKey, char* mess, Signature* sgn){
    Protected* pr = (Protected*)malloc(sizeof(Protected));
    if(pr == NULL){
        printf("Erreur : allocation dans fonction init_protected\n");
        return NULL;
    }
    pr->pKey = pKey;
    pr->message = strdup(mess);
    pr->signature = sgn;

    return pr;
}

//Q3.11
int verify(Protected* pr){
    char* _cleEm = decrypt(pr->signature->content, strlen(pr->message), pr->pKey->val, pr->pKey->n);
    if(strcmp(_cleEm, pr->message) != 0){
        return 0; 
    }
    return 1;  
}


//Q3.12
char* protected_to_str(Protected* p){
    char *message = (char*)malloc(256 * sizeof(char));
    if(message == NULL){
        printf("Erreur allocation dans fonction : protected_to_str\n");
        return NULL;
    }
    sprintf(message, "%s %s %s", key_to_str(p->pKey), p->message,  signature_to_str(p->signature));
    return message; 
}

Protected* str_to_protected(char* message){
    char key[256];
    char mess[360];
    char signature[360];

    int nb_l = sscanf(message, "%s %s %s", key, mess, signature);
    if (nb_l != 3){
        printf("Erreur nombres d'arguement dans fonction : str_to_protected\n");
        return NULL;
    }
    
    return init_protected(str_to_key(key), mess, str_to_signature(signature)); 
}

//Fonction renvoie 0 si la cle key figure dans le tableau de cles tab, 1 sinon
int present(Key *tab, Key *key, int taille){
    int i = 0;
    while(i < taille){
    if (tab[i].val == key->val && tab[i].n == key->n){
        return 0;
    }
    i++;
    }

return 1;
}

// EXERCICE 4
//Q4.1 
void generate_random_data(int nv, int nc){
    if(nc > nv){
        printf("Erreur : indices incorrects\n");
        return;
    }
    //Allocation clé pulique et clé secrete
    Key *pKey = (Key*)malloc(sizeof(Key));
    Key *sKey = (Key*)malloc(sizeof(Key));
    //tableau des clés publiques
    Key *tab_pkeys = (Key*)malloc(nv*sizeof(Key));
    //tableau des candidats
    Key *tab_candidats = (Key*)malloc(nc*sizeof(Key)); 
    if(sKey == NULL && pKey == NULL && tab_pkeys == NULL && tab_candidats == NULL){
        printf("Erreur : allocation dans generate_ramdom_data\n");
    }
    //Création et ouverture des fichiers
    FILE *f_keys = fopen("fichiers/keys.txt", "w");
    FILE *f_candidates = fopen("fichiers/candidates.txt", "w");
    FILE *f_declarations = fopen("fichiers/declaration.txt", "w");
    if (f_keys == NULL && f_candidates == NULL && f_declarations == NULL){
        printf("Erreur : ouverture du fichier dans generate_random_data\n");
    }

    //génère nv couples de clés
    for(int i = 0; i < nv; i++){
        init_pair_keys(pKey, sKey, 3, 7);
        fprintf(f_keys, "(%lx,%lx),(%lx,%lx)\n", pKey->val, pKey->n, sKey->val, sKey->n);
        //on ajoute toute les cles publique dans le tableau tab_pkeys
        tab_pkeys[i] = (*pKey);
    
    }
    //On ferme le fichier car on va le réutiliser plus tard
    fclose(f_keys);

    //Selectionne nc clés publiques aléatoirement et les écrits dans f_candidates
    long val, n;
    char temp[256];
    for(int i = 0; i < nc; i++){
        int alea = rand() % nv;
        while(present(tab_candidats, &tab_pkeys[alea], i) == 0){  //pour éviter les doublons
           alea = rand() % nv;
        }
        tab_candidats[i] = tab_pkeys[alea];
        fprintf(f_candidates, "(%lx,%lx)\n", tab_candidats[i].val, tab_candidats[i].n);
    }
    
    //déclaration de vote signée pour chaque citoyen
    //On réouvre le fichier f_keys
    int cpt = 0;
    f_keys = fopen("fichiers/keys.txt", "r");
    char* vote, *mess;
    Signature* sgn;
    Protected* pr;
    while(cpt < nv){
        //on parcours le fichiers
        fgets(temp, 256, f_keys);
        //On attribut des valeurs à pKey et sKey
        sscanf(temp, "pKey : (%lx , %lx), sKey : (%lx , %lx)\n", &pKey->val, &pKey->n, &sKey->val, &sKey->n);
        //On choisit aléatoirement le candidats
        int alea_cand = rand() % nc;
        mess = key_to_str(&tab_candidats[alea_cand]);
        sgn = sign(mess, sKey);
        pr = init_protected(pKey, mess, sgn);
        vote = protected_to_str(pr);
        fprintf(f_declarations, "%s\n", vote);
        cpt++;
        }
        

    //On libere les tableaux et on ferme les fichiers
    free(sKey);
    free(pKey);
    free(tab_pkeys);
    free(tab_candidats);
    free(vote);
    free(mess);
    free(sgn);
    free(pr);

    fclose(f_keys);
    fclose(f_candidates);
    fclose(f_declarations);        
}


void free_signature(Signature* s){
    if(s){
        free(s->content);
        free(s);
    }
   
}

void free_protected(Protected* p){  
    free(p->pKey);
    free(p->message);
    free_signature(p->signature);
    free(p);

}