#include "../../headers/partie4.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>


int main(){

    srand(time(NULL));

    printf("-----------MAIN PARTIE 4----------\n\n");
    Key *key1 = (Key*)malloc(sizeof(Key));
    Key *key2 = (Key*)malloc(sizeof(Key));
    Key *key3 = (Key*)malloc(sizeof(Key));
    CellKey* liste_c = NULL;

    //Initalisé les clés :
    init_key(key1, 6, 9);
    init_key(key2, 5, 3);
    init_key(key3, 8, 5);
    
    //Les ajouters dans la liste :
    ajouter_cle(key1, &liste_c);
    ajouter_cle(key2, &liste_c);
    ajouter_cle(key3, &liste_c);
    
    printf("liste de cles :\n");
    print_list_key(liste_c);
    
    // //Verification Q6.2
    HashCell* h = create_hashcell(key1);
    printf("Fonction create_hashcell :\n");
    print_hashcell(h);
    printf("\n");

    // //Verification Q6.5
    HashTable* t = create_hashtable(liste_c, 3);
    printf("Fonction create_hashatbale :\n");
    print_hashtable(t);

    free(key1);
    free(key2);
    free(key3);

    free(h);
    delete_hashtable(t);
    printf("\n");

    //TEST COMPUTE_WINNER
    printf("TEST COMPUTE WINNER\n\n");
    CellProtected* decl = read_protected("fichiers/declaration.txt");
    CellProtected* tmp_decl = decl;
    CellKey* candidates = NULL;
    CellKey* voters = NULL;
    
    int sizeC = 0;
    int sizeV = 0;
    
    while(tmp_decl){
        //evite les doublons
        if(find(candidates, str_to_key(tmp_decl->data->message)) == 1){
            //On ajoute les cles des candidats
            ajouter_cle(str_to_key(tmp_decl->data->message), &candidates);
            sizeC++;
        }
        //On ajoute les voters
        ajouter_cle(tmp_decl->data->pKey, &voters);
        tmp_decl = tmp_decl->next;
        sizeV++;
    }
    
   
    Key* gagnant = compute_winner(decl, candidates, voters, sizeC, sizeV);

    printf("cle gagnante : %s\n", key_to_str(gagnant));

    delete_cell_protected(decl);
    delete_cell_key(candidates);
    delete_cell_key(voters);
    
}