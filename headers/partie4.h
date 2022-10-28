#ifndef PARTIE4_H
#define PARTIE4_H
#include "partie3.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


typedef struct hashcell {
    Key * key ;     
    int val ;       
} HashCell ;


typedef struct hashtable {
    HashCell ** tab ;
    int size ; //nombre de vote compatibilisé
} HashTable ;


void verify_list_protected(CellProtected** c);

HashCell* create_hashcell(Key* key);

void print_hashcell(HashCell* h);

int hash_function(Key* key, int size);

int find(CellKey* tab, Key* key);

int find_position(HashTable* t, Key* key);

HashTable* create_hashtable(CellKey* keys, int size);

void print_hashtable(HashTable* t);

void delete_hashtable(HashTable* t);

int compare_key(Key* key1, Key* key2);

Key *compute_winner(CellProtected *decl, CellKey *candidates, CellKey *voters, int sizeC, int sizeV);

#endif 