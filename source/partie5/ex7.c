#include "../../headers/partie5.h"

//fonction intermediaire 
char* CellProtected_to_str(CellProtected* CP){
    char* chaine = (char*)malloc(sizeof(char)*1000000);
    strcpy(chaine, ""); //On initialise chaine pour l'utilisation de strcat
    while(CP != NULL){
        strcat(chaine, protected_to_str(CP->data));
        strcat(chaine, "\n");
        CP = CP->next;
    }
    chaine[strlen(chaine)+1] = '\0';
    chaine = (char*)realloc(chaine, (strlen(chaine)+1)*sizeof(char));
   
    return chaine;
}

//Q7.1 
FILE* write_block(Block* block, char* nom){
    FILE* f = fopen(nom, "w");
    if(f == NULL){
        printf("Erreur : ouverture fichier dans write_block\n");
        return NULL;
    }

    fprintf(f, "Author : %s\n", key_to_str(block->author));  
    fprintf(f, "Valeur hachee du bloc : %s\n", block->hash);
    fprintf(f, "Valeur hachee du bloc precedent : %s\n", block->previous_hash);
    fprintf(f, "Preuve : %d\n", block->nonce);
    while(block->votes != NULL){
        fprintf(f, "%s\n", protected_to_str(block->votes->data));
        block->votes = block->votes->next;
    }
    fclose(f);
    return f;

}

//Q7.2
Block* file_to_block(char* nom){
    FILE* f = fopen(nom, "r");
    Block* block = (Block*)malloc(sizeof(Block));
    Key* key = (Key*)malloc(sizeof(Key));
    CellProtected* cellP = NULL;
    if (f == NULL && block == NULL && key == NULL){
        printf("Erreur : fonction file_to_block\n");
        return NULL;
    }
    long val, n;
    int nonce;
    char temp[256];
    char previous_hash[256], hash[256];
    char cle_p[150], mess[256], sgn[256];  //variables pour les protected
   
    //On lit l'auteur
    fgets(temp, 256, f);
    sscanf(temp, "Author : (%lx, %lx)\n", &val, &n);
    init_key(key, val, n);
    block->author = key;
    
    //On lit la valeur hachee
    fgets(temp, 256, f);
    sscanf(temp, "Valeur hachee du bloc : %s", hash);
    block->hash = strdup(hash);
    

    //On lit la valeur previous_hash
    fgets(temp, 256, f);
    sscanf(temp, "Valeur hachee du bloc precedent : %s", previous_hash);
    block->previous_hash = strdup(previous_hash);
        
    //On lit la preuve
    fgets(temp, 256, f);
    sscanf(temp, "Preuve : %d", &nonce);
    block->nonce = nonce;
    
    //On lit les votes
    
    while(fgets(temp, 256, f) != NULL){
        sscanf(temp, "%s %s %s", cle_p, mess, sgn);
        Key* pKey = str_to_key(cle_p);
        Signature* signature = str_to_signature(sgn);
        Protected *p = init_protected(pKey, mess, signature);
        ajout_declaration(&cellP, p);   
    }
    
    block->votes = cellP;
    
    fclose(f);
    return block;
}


//Q7.3 
char* block_to_str(Block* block){
    char* bloc = (char*)malloc(sizeof(char)*1500000);
    sprintf(bloc,"Author : %s \nHash : %s \nPrevious Hash : %s \nNonce : %d\nVotes :\n%s\n", key_to_str(block->author),block->hash,block->previous_hash, block->nonce, CellProtected_to_str(block->votes));
    return bloc;

}


//Q7.5
char* hashage_by_SHA256(char* hash){
  char* mess = (char*)malloc(sizeof(char) * 256);
  unsigned char *tmp = SHA256(hash, strlen(hash), 0);

  for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
    sprintf(mess + 2*i, "%02x", tmp[i]);
  }

  return mess;
}

void compute_proof_of_work(Block *B, int d){
    if(B == NULL){
        printf("valeur NULL dans compute_proof_of_work\n");
        return;
    }
    int i = 0;
    char* block_str;
    unsigned char* hash;
    //On verifie la valeur de b->hash
    if(B->hash == NULL){
        block_str = block_to_str(B);
        hash = hashage_by_SHA256(block_str);
        free(block_str);
        B->hash = strdup(hash);
    }
    //variable qui nous permet de comparer le nombre de 0 au debut de la valeur hash
    char* nb_zero = (char*)malloc(sizeof(char)*(d + 1));
    for(int i = 0; i < d; i++){
        nb_zero[i] = '0';
    }
    //Si la valeur hash commence deja par d zero
    if(strncmp(nb_zero, B->hash, d) == 0){
        free(nb_zero);
        return;
    }
    //Sinon on boucle jusqu'a trouver une valeur hashée qui aura d 0 au debut
    B->nonce = 0;
    while(1){
        if(B->nonce == 10000){
            printf("La fonction compute_proof_of_work cherche une valeur, un peu de patience\n");
        }
        block_str = block_to_str(B);
        hash = hashage_by_SHA256(block_str);
        free(block_str);
        free(B->hash);
        B->hash = strdup(hash);
        //On verifie que le nombre de 0 == d
        if(strncmp(nb_zero, B->hash, d) == 0){
            free(nb_zero);
            return;
        }
        B->nonce++;
    }
    
   
}

// retourne 0 si le block est valide, -1 sinon
int verify_block(Block *b, int d) {
    char* block_str = block_to_str(b);
    unsigned char* hash = hashage_by_SHA256(b->hash);
    
    char* nb_zero = (char*)malloc(sizeof(char)*d);
     for(int i = 0; i < d; i++){
        nb_zero[i] = '0';
    }
    
    int bool = strncmp(nb_zero, b->hash, d);
    free(block_str); 
    free(hash);
    free(nb_zero);

    return bool;
}


// Q7.8
void ecriture_f(Block* B, int d){
    
    FILE* fd = fopen("fichiers/fichier2.txt", "a");
    if(fd == NULL){
        printf("Erreur : ouverture du fichier dans ecriture\n");
    }
    clock_t t_init;
    clock_t t_final;
    double temp_cpu;
    
    t_init=clock();
    compute_proof_of_work(B,d);  
    t_final = clock();
    
    temp_cpu = ((double)(t_final - t_init) / CLOCKS_PER_SEC);
    
    if(d==0){
    fprintf(fd,"Valeur de d | Temps fonction\n");
    }
    fprintf(fd, "%d \t %f\t \n", d ,temp_cpu);

    fclose(fd);
}


//Q7.9
void delete_block(Block* b){ 
    delete_liste_protected(b->votes);
    free(b->author);
    free(b->hash);
    free(b->previous_hash);
    free(b);

}

//Fonction intermediaire pour le main : fonction ecriture
Block* init_block(Key *k, CellProtected *votes, char *previous_hash, int nonce){ // initialisation par copie
    Block* b = (Block*)malloc(sizeof(Block));
    if(b == NULL){
        printf("Erreur dans init_block\n");
    }
    b->author = k;
    b->votes = votes;
    b->hash = NULL;
    b->previous_hash = strdup(previous_hash);
    b->nonce = nonce;
    return b;
}