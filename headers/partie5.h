#ifndef PARTIE5_H
#define PARTIE5_H
#include "partie4.h"
#include <assert.h>
#include <openssl/sha.h>

#define NB_CAND 5
#define NB_VOTANT 150
#define NB_VOTE_B 10
#define D 3
#define UP_SIZE 7
#define LOW_SIZE 4


 typedef struct block {
    Key * author;
    CellProtected * votes;
    char * hash;
    char * previous_hash;
    int nonce;
} Block;

typedef struct block_tree_cell{
    Block* block;
    struct block_tree_cell* father;
    struct block_tree_cell* firstChild;
    struct block_tree_cell* nextBro; 
    int height;                     
}CellTree;


FILE* write_block(Block* block, char* nom);

Block* file_to_block(char* nom);

char* CellProtected_to_str(CellProtected* CP);

char* block_to_str(Block* block);

char* hashage_by_SHA256(char* str);

char* ajout_en_tete_caractere(char* chaine, char* s);

void compute_proof_of_work(Block* B, int d);

int verify_block(Block* b, int d);

void delete_block(Block* b);

CellTree* create_node(Block* b);

int update_height(CellTree* father, CellTree* child);

void add_child(CellTree* father, CellTree* child);

void add_child_v2(CellTree* father, CellTree* child);

void print_tree(CellTree* arbre);

void delete_node(CellTree* node);

void delete_tree(CellTree* arbre);

CellTree* highest_child(CellTree* cell);

CellTree* last_node(CellTree* tree);

void submit_vote(Protected* p);

void create_block(CellTree* tree, Key* author, int d);

void ecriture_f(Block* B, int d);

Block* init_block(Key *k, CellProtected *votes, char *previous_hash, int nonce);

CellProtected** fusion_list_decl(CellProtected** l1, CellProtected** l2);

void create_block(CellTree* tree, Key* author, int d);

void add_block(int d, char* name);

CellTree* read_tree();

Key* compute_winner_BT(CellTree* tree, CellKey* candidates, CellKey* voters, int sizeC, int sizeV);

CellTree *create_tree(Key *author, int d);

#endif
