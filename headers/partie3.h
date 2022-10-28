#ifndef PARTIE3_H
#define PARTIE3_H
#include "partie2.h"

typedef struct cellKey{
    Key* data;
    struct cellKey* next;
}CellKey;

typedef struct cellProtected{
    Protected* data;
    struct cellProtected* next;
} CellProtected;


CellKey* create_cell_key(Key* key);

void ajouter_cle(Key* key, CellKey** cell_key);

CellKey* read_public_keys(char* nom);

void print_list_key(CellKey* LCK);

void delete_cell_key(CellKey* c);

void delete_list_keys(CellKey* c);

CellProtected* create_cell_protected(Protected* pr);

void ajout_declaration(CellProtected** cp, Protected* pr);

CellProtected* read_protected(char* nom);

void print_list_pr(CellProtected* cp);

void liberer_signature(Signature* sgn);

void delete_cell_protected(CellProtected* c);

void delete_liste_protected(CellProtected *c);


#endif