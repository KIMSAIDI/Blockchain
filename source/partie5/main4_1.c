#include "../../headers/partie5.h"
#include "../../headers/partie3.h"
#include "../../headers/partie2.h"
#include "../../headers/partie1.h"
#include "../../headers/partie4.h"

int main(){
     //MAIN EXERICE 7-8
    srand(time(NULL));

    generate_random_data(NB_VOTANT, NB_CAND);
    
    Block *block = (Block*)malloc(sizeof(Block));
    CellProtected* votes = read_protected("fichiers/declaration.txt");
    Key *key = (Key*)malloc(sizeof(Key));
    init_key(key, 5, 7);
    block->author = key;
    block->votes = votes;
    block->hash = strdup(hashage_by_SHA256("hash"));
    block->previous_hash = strdup(hashage_by_SHA256("prev_hash"));
    block->nonce = 90;


   
    //Verification de la fonction block_to_file
    FILE *f = write_block(block, "fichiers/fichier_block.txt");    
    //Verification de la fonction file_to_block
    Block* block2 = file_to_block("fichiers/fichier_block.txt");
    char* block2_str = block_to_str(block2);
    printf("%s\n", block2_str);

     //Verification de la fonction compute_proof_of_work
    printf("valeur hash avant de la rendre valide : %s\n", block2->hash);
    compute_proof_of_work(block2, D);
    printf("valeur hash apres validation : %s\n", block2->hash);
    printf("valeur de nonce apres validation : %d\n", block2->nonce);
    printf("\n");

    printf("Block : %s\n", (verify_block(block2, D)) == 0 ? "Valide\n" : "Non Valide\n");

    free(block2_str);
    delete_block(block);
    delete_block(block2);

    //TEST FONCTION ECRITURE
    // Création et initialisation d'une key
    // printf("----------------------test : fonction ecriture-----------------------\n");
    // Key* k2=(Key*)malloc(sizeof(Key));
    // init_key(k2, 12345, 54321);
    // // Création et initialisation d'une protected
    // CellProtected* cp2 = read_protected("fichiers/declaration.txt");
    // char* str2 = "cgfb";
    // unsigned char* prev2 = hashage_by_SHA256(str2);

    // Block* bl = init_block(k2, cp2, prev2, 0);
   
    // for(int i=0; i<5;i++){
    //     int d = i;
    //     ecriture_f(bl,d);
    //     if(i!=4){
    //         free(bl->hash);
    //     }
    // }
    // delete_block(bl);
    // free(cp2);


    //TEST PARTIE ARBRE
    printf("----------------------test : fonctions arbre-----------------------\n");
    Block *b = file_to_block("fichiers/fichier_block.txt");
    Block* b1 = file_to_block("fichiers/fichier_block.txt");
    Block* b2 = file_to_block("fichiers/fichier_block.txt");
    b->hash = strdup("father");
    b1->hash = strdup("fils1");
    b2->hash = strdup("fils2");
    

    CellTree* tree = create_node(b);  //father
    CellTree* child1 = create_node(b1); //child1
    CellTree* child2 = create_node(b2); //child2
    
    add_child(tree, child1);  
    add_child(tree, child2);
    
    
    print_tree(tree);
    printf("\n");

   
   CellTree* high = highest_child(tree);
   CellTree* last = last_node(high);
   printf("hightest : hauteur : %d, valeur hash : %s\n", high->height, high->block->hash);
   printf("laste_node : hauteur : %d, valeur hash : %s\n", last->height, last->block->hash);

    
    delete_tree(tree);

    //TEST FONCTION FUSION
    printf("----------------------test : fonction fusion-----------------------\n");
    generate_random_data(6, 4);
    CellProtected* l1 = read_protected("fichiers/declaration.txt");
    generate_random_data(5, 4);
    CellProtected* l2 = read_protected("fichiers/declaration.txt");

    printf("liste1 : \n");
    print_list_pr(l1);
    printf("liste2 : \n");
    print_list_pr(l2);

    printf("liste fusionnee : \n");
    CellProtected** fusion = fusion_list_decl(&l1, &l2);
    print_list_pr(*fusion);

    
    delete_cell_protected(*fusion);

    return 0;
}