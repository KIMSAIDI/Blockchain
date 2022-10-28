#ifndef PARTIE2_H
#define PARTIE2_H

//Q3.1
typedef struct _key{
    long val;
    long n;
}Key;

//Q3.5
typedef struct Signature{
    int size;
    long *content;
} Signature;

//Q3.9
typedef struct Protected{
    Key* pKey;               //Electeur
    char* message;           //Declaration de vote
    Signature* signature;    //Signature associé
}Protected;


void init_key(Key* key, long val, long n);

void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size);

char* key_to_str(Key* key);

Key* str_to_key(char* str);

Signature* init_signature(long* content, int size);

Signature* sign(char* mess, Key* sKey);

char* signature_to_str(Signature* sgn);

Signature* str_to_signature(char* str);

Protected* init_protected(Key* pKey, char* mess, Signature* sgn);

int verify(Protected* pr);

char* protected_to_str(Protected* p);

Protected* str_to_protected(char* message);

int present(Key *tab, Key *key, int taille);

void generate_random_data(int nv, int nc);

void free_signature(Signature* s);

void free_protected(Protected* p);

#endif  //PARTIE2_H