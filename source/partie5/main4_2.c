#include "../../headers/partie5.h"
#include "../../headers/partie3.h"
#include "../../headers/partie2.h"
#include "../../headers/partie1.h"
#include "../../headers/partie4.h"



int main(){
     //MAIN EXERICE 9
    srand(time(NULL));
    printf("Exercice 9 :\n");

    printf("-------------ETAPE 1 : GENERATION DE VOTE--------------\n\n");
    generate_random_data(NB_VOTANT, NB_CAND);

    printf("La generation de vote s'est bien passe\n");

    printf("------------------FIN ETAPE 1-------------------\n\n");


    printf("-------------ETAPE 2 : LECTURE DES DECLARATIONS DE VOTE--------------\n\n");
    CellProtected *liste_decl = read_protected("fichiers/declaration.txt");
    CellKey* liste_voters = read_public_keys("fichiers/keys.txt");
    CellKey* liste_cand = read_public_keys("fichiers/candidates.txt");

    printf("La lecteure des declaration s'est bien passe\n");
    
    printf("------------------FIN ETAPE 2--------------------\n\n");


    printf("-------------ETAPE 3 : SOUMISSIONS DE VOTE--------------\n");
    Key* pKey,* sKey;
    pKey = (Key*)malloc(sizeof(Key));
    sKey = (Key*)malloc(sizeof(Key));
    init_pair_keys(pKey, sKey, LOW_SIZE, UP_SIZE);

    CellTree* tree = NULL, *arbre;
    CellProtected* tmp = liste_decl;

    int size_b = 0;
    //Boolean pour savoir quand cree la racine
    int boolean = 0;
    //Variable pour la stocker
    CellTree *racine = NULL;
    char* name;
    char str[150] = "";
    int cpt = 0;

    while(tmp){
        size_b++;
        name = strdup("Blockchain/Block");
        submit_vote(tmp->data);

        if(size_b%10 == 0){
            cpt++;
            sprintf(str, "%d.txt", cpt);
            strcat(name, str);
            create_block(tree, liste_decl->data->pKey, D);
            add_block(D, name);

            if(tree == NULL){
                tree = create_node(file_to_block(name));
            }else{
                arbre = tree;
                while(arbre->firstChild != NULL){
                    arbre = arbre->firstChild;
                }
                add_child(arbre, create_node(file_to_block(name)));
                
            }
        }
        tmp = tmp->next;
    }
    printf("La soumission s'est bien passe\n");
    
    
    
   
    
    printf("-------------FIN ETAPE 3--------------\n\n");

    printf("-------------ETAPE 4 : LECTURE--------------\n\n");

    //Ici : probleme au dans la fonction read_tree() au niveau de l'etape 2 lors de la verification

    CellTree *t = read_tree();
    printf("Affichage arbre\n");
    if(t == NULL){
        printf("erreur arbre vide\n");
        return 0;
    }else{
        print_tree(t);
    }
   

    Key* winner = compute_winner_BT(t, liste_cand, liste_voters, NB_CAND, NB_VOTANT);

    printf("le gagant porte la cle : %s\n", key_to_str(winner));
    delete_tree(tree);
    delete_liste_protected(liste_decl);
    delete_list_keys(liste_voters);
    delete_list_keys(liste_cand);
    free(pKey);
    free(sKey);


    return 0;


}