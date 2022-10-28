#include "../../headers/partie5.h"

//EXERCICE 8
//Q8.1
CellTree* create_node(Block* b){
    CellTree* arbre = (CellTree*)malloc(sizeof(CellTree));
    if(arbre == NULL){
        printf("Erreur allocation dans fonction create_node\n");
        return NULL;
    }
    arbre->block = b;
    arbre->father = NULL;
    arbre->firstChild = NULL;
    arbre->nextBro = NULL;
    arbre->height = 0;

    return arbre;
}

//Q8.2
int update_height(CellTree* father, CellTree* child){
    if(father != NULL && child != NULL){
        father->height = 1 + fmax(father->height, child->height);
        return 1;
    }
    return 0;
}

//Q8.3
void add_child(CellTree* father, CellTree* child){
    if(father->firstChild == NULL){
        father->firstChild = child;
    }else{
        add_child(father->firstChild, child);
    }
    int bool = update_height(father, child);
    //On verifie que la mise à jour de la hauteur se fait bien
    assert(bool == 1);   
    
     
}

//A utiliser dans un autre cas de figure
void add_child_v2(CellTree* father, CellTree* child){
    if (father == NULL || child == NULL){
        return;
    }
    // on annonce au fils qu'il a un père
    child->father = father;
    // on annonce au pere qu'il a un autre fils
    child->nextBro = father->firstChild;
    father->firstChild = child;

    CellTree *tmp_father, *tmp_child;
    tmp_father = father;
    tmp_child = child;


    // update de la hauteur
    while (tmp_father){
        update_height(tmp_father, tmp_child);
        tmp_father = tmp_father->father;
        tmp_child = tmp_child->father;
    }
}

//Q8.4
void print_tree(CellTree* arbre){
    if(arbre != NULL){
        printf("valeur hashe : %s ,hauteur : %d\n",arbre->block->hash,arbre->height);    
    }
        if(arbre->firstChild != NULL){
            print_tree(arbre->firstChild);
        } 
        if(arbre->father != NULL){
            print_tree(arbre->father);
        }
    
}


//Q8.5
void delete_node(CellTree* node){
    if(node == NULL){
        return;
    }
    delete_block(node->block);
    free(node);
}

void delete_tree(CellTree *arbre){
  if (arbre == NULL){
    return;
  }

  CellTree *firstBro, *firstChild;

  firstBro = arbre->nextBro;
  firstChild = arbre->firstChild;

  // supression du block associe a arbre
  delete_node(arbre);
  // appel recursif sur le premier frere et le premier fils
  delete_tree(firstBro);
  delete_tree(firstChild);

  return;
}

//DETERMINATION DU DERNIER BLOC
//Q8.6
CellTree* highest_child(CellTree* cell){
    if(cell == NULL){
        return NULL;
    }

    //On suppose que le premier fils à la plus grande hauteur
    CellTree* highest = cell->firstChild;
    //On stock sa hauteur dans max
    int max = highest->height;
  
    
    CellTree* tmp = highest->nextBro;

    while(tmp != NULL){
        //Si on trouve une hauteur plus grande que max
        if(tmp->height > max){
            max = tmp->height;
            highest = tmp;
        }
        tmp = tmp->father;
    }
    return highest;
}

//Q8.7
CellTree* last_node(CellTree* tree){
    if(tree == NULL){
        return NULL;
    }
    if(tree->firstChild == NULL){
        return tree;
    }
    CellTree* highest = highest_child(tree);
    return last_node(highest);
}

//Q8.8
CellProtected** fusion_list_decl(CellProtected** l1, CellProtected** l2){
    if(l1 == NULL){
        return l2;
    }
    if(l2 == NULL){
        return l1;
    }
    CellProtected* tmp = *l1;
    while(tmp->next){
        tmp = tmp->next;
    }
    tmp->next = *l2;
    return l1;
}

//Q8.9
CellProtected* highest_fusion_list(CellTree* arbre){
    if(arbre == NULL){
        return NULL;
    }
    CellProtected* list = NULL;
    CellTree* highest = highest_child(arbre);
    fusion_list_decl(&list, &(arbre->block->votes));

   
    //On rajoute les autres
    while(highest != NULL){
        fusion_list_decl(&list, &(highest->block->votes));
        highest = highest_child(highest);
    }

    return list;

}
