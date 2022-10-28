#include "../../headers/partie5.h"
#include <dirent.h>

//VOTE ET CREATION DE BLOCS VALIDES
//Q9.1
void submit_vote(Protected* p){
    if(p == NULL){
        return;
    }
    FILE *f = fopen("fichiers/Pending_votes.txt", "a");
    if(f == NULL){
        printf("erreur ficher dans submit_vote\n");
        return;
    }
    
    fprintf(f, "%s\n", protected_to_str(p));
    fclose(f);
    return;
}

//Q9.2
void create_block(CellTree* tree, Key* author, int d){
    CellProtected* votes = read_protected("fichiers/Pending_votes.txt");
    //On peut supprimer le fichier
    remove("fichiers/Pending_votes.txt");
    
    //Initialisation variable et fichiers
    Block* block = (Block*)malloc(sizeof(Block));
    if(block == NULL ){
        printf("erreur dans fonction : create_block\n");
        return;
    }
    //On initialise le block
    block->author = author;
    CellTree* last = last_node(tree);
    if(last == NULL){
        block->previous_hash = NULL;
    }else{
        block->previous_hash = strdup(last->block->hash);
    }

    block->hash = NULL;
    block->nonce = 0;
    
    block->votes = votes;
    //On initialise la valeur block->hash et block->nonce
    compute_proof_of_work(block, d);
    //On ecrit dans le block dans le fichier Pend_block
    write_block(block, "fichiers/Pending_block.txt");
    //On rajoute un noeud dans l'arbre
    CellTree* block_to_tree = create_node(block);
    add_child_v2(last, block_to_tree);
    delete_liste_protected(votes);
     
    return;    
}


//Q9.3
void add_block(int d, char* name){
    Block* block = file_to_block("fichiers/Pending_block.txt");

    if(block == NULL){
        printf("block null dans add_block\n");
        return;
    }
    //On verifie le block
    if(verify_block(block, d) == 0){
        FILE* f = fopen(name, "w");
        if(f == NULL){
            printf("Erreur : ouverture fichier : add_block\n");
            return;
        }
        write_block(block, name);
        fclose(f);
    }else{
        printf("le block n'est pas valide\n");

    }
    remove("fichiers/Pending_block.txt");
    delete_block(block);
    return;
}


//LECTURE DE L'ARBRE ET CALCUL DU GAGNANT
//Q9.4
CellTree* read_tree(){
    int taille = NB_VOTANT;
    DIR *rep = opendir("Blockchain/");
    CellTree** T = (CellTree**)malloc(sizeof(CellTree*)*taille);
    if(rep == NULL && T == NULL){
        printf("Erreur : fichier dans read_tree\n");
        return NULL;
    }
    struct dirent* dir;
    for(int i = 0; i < taille; i++){
        T[i] = NULL;
    }
    char temp[256], *path;
    int cpt = 0;

    //ETAPE1
    while((dir = readdir(rep))){
        //Si on a un fichier
        if(dir->d_type == DT_REG){
            strcpy(temp, "Blockchain/");
             
            path = strcat(temp, dir->d_name);
            //On cree notre block
            Block* block = file_to_block(path);
            //On cree notre noeud
            CellTree *node = create_node(block);
            //On stock dans notre tableau
            T[cpt] = node;
            cpt++;
        }
    }

    //ETAPE2
    //Probleme au niveau de la verification
    for(int i = 0; i < taille; i++){
        for(int j = 0; j < taille; i++){
            //On verifie que le champ previous_hash T[j] = hash T[i]
            if((T[j]->block->previous_hash != NULL) && (T[i]->block->hash != NULL) && (strcmp(T[j]->block->previous_hash, T[i]->block->hash) == 0)){
                add_child(T[i], T[j]);
            }else{
                return NULL;
            }
        }
    }
    //ETAPE3
    CellTree* racine = NULL;
    for(int i = 0; i < taille; i++){
        if(T[i]->father == NULL){
            racine = T[i];
        }
    }
   
    free(T);
    return racine;;
}


//Q9.5
Key* compute_winner_BT(CellTree* tree, CellKey* candidates, CellKey* voters, int sizeC, int sizeV){
    //ETAPE1 : extraction de la liste des declarations
    //On prend le fils le plus loin
    CellTree *last = highest_child(tree);
    CellProtected **liste_decl = NULL;

    while(last){
        //On fusionne la liste de declaration du fils avec celle du pere
        liste_decl = fusion_list_decl(liste_decl, &last->block->votes);
        //On remonte
        last = last->father;
    }
    int size = 0;
    CellProtected *tmp = *liste_decl;
    while(tmp){
        size++;
        tmp = tmp->next;
    }
    printf("on a recupere %d declaraation dans la blockchain\n", size);

    //ETAPE2 :Suppression des declarations de vote non valide
    verify_list_protected(liste_decl);

    //ETAPE3 : Calcul du vainqueur
    Key *winner = compute_winner(*liste_decl, candidates, voters, sizeC, sizeV);

    return winner;

}

//Fonction intermediaire
CellTree *create_tree(Key *author, int d){
    CellTree *tree = NULL;
    //Racine
    Block* b = (Block*)malloc(sizeof(Block));
    if(b == NULL){
        printf("Erreur allocation : create_tree\n");
        return NULL;
    }
    CellProtected *votes = read_protected("fichiers/Pending_votes.txt");
    b->author = author;
    b->hash = NULL;
    b->previous_hash = NULL;
    b->votes = votes;
    b->nonce = 0;

    remove("fichiers/Pending_votes.txt");
    compute_proof_of_work(b, d);
   
    write_block(b, "fichiers/Pending_votes.txt");
   
    tree = create_node(b);
    delete_liste_protected(votes);
    

    return tree;


}