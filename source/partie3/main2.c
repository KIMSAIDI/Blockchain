#include "../../headers/partie3.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

int main(){

    srand(time(NULL));
    
     printf("\n-----------MAIN PARTIE 3----------\n\n");
     

     
     generate_random_data(10, 7);

    // test Q5.3 : fonction de lecture pour liste chainée de clés
    CellKey* p_keys = read_public_keys("fichiers/candidates.txt"); 
    printf("liste des cles du fichiers keys.txt : \n");
    print_list_key(p_keys);

    
    printf("\n\n");

    //test Q5.8 : fonction de lecture pour les declarations de votes
        printf("liste des declarations du fichiers declarations.txt : \n");
    CellProtected* pro = read_protected("fichiers/declaration.txt");
    print_list_pr(pro);

    
    delete_liste_protected(pro);
    delete_list_keys(p_keys);
}