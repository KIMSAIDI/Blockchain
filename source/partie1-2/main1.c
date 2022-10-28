#include "../../headers/partie1.h"
#include "../../headers/partie2.h"

int main(){
    
    //Main de la partie 1
    
    //1.2
    
    // clock_t t_init = clock();
    // clock_t t_final ;
    // double temp_cpu;
    // int v = is_prime_naive(475000000);  
    // t_final = clock();
    // temp_cpu = ((double)(t_final - t_init) / CLOCKS_PER_SEC);

    // printf("%d\n", v);
    // printf("%f\n", temp_cpu); 
    
    //1.5

    srand(time(NULL));

    long a=rand(), pk=rand();
    for(int i=0; i<100000 ; i=i+100){
        long m = (long) i;
        ecriture(a, m, pk);
    }
    

    printf("-----------MAIN PARTIE 1----------\n\n");
    //Generation de cle :
    long p = random_prime_number(3, 7, 5000);
    long q = random_prime_number(3,7, 5000);
   
    while(p == q){
        q = random_prime_number(3,7,5000);
    }
    long n, s, u;
    generate_key_values(p,q,&n,&s,&u);
    //Pour avoir des cles positives :
    if (u < 0){
        long t = (p-1)*(q-1);
        u = u+t; //on aura toujours s*u mod t = 1 
    }
    printf("cle publique = (%lx , %lx) \n",s, n);
    printf("cle privee = (%lx , %lx) \n", u, n);
    //Chiffrement:
    char mess[10] = "Hello";
    int len = strlen(mess);
    long* crypted = encrypt(mess, s, n);
    printf("\n");
    printf("Initial message : %s \n", mess);
    printf("\n");
    printf("Encoded representation : \n");
    print_long_vector(crypted, len);
    //Dechiffrement
    char* decoded = decrypt(crypted, len, u, n);
    printf("\n");
    printf("Decoded message : %s\n", decoded);
    printf("\n");
    
    free(decoded);
    free(crypted);

     printf("-----------MAIN PARTIE 2----------\n\n");

        //Testing Init Keys
    Key* pKey = (Key*)malloc(sizeof(Key));
    Key* sKey = (Key*)malloc(sizeof(Key));
    init_pair_keys(pKey, sKey, 3, 7);
    printf("pKey: %lx , %lx \n", pKey->val, pKey->n);
    printf("sKey: %lx , %lx \n", sKey->val, sKey->n);

    
    //Testing Key Serialization
    char* chaine = key_to_str(pKey);
    printf("key to str : %s\n", chaine);
    Key* k = str_to_key(chaine);
    printf("str to key : %lx , %lx \n", k->val, k->n);
    printf("\n");

    free(chaine);
    free(k);


   
    //Testing signature
    //Candidate keys:
    Key* pKeyC = malloc(sizeof(Key));
    Key* sKeyC = malloc(sizeof(Key));
    init_pair_keys(pKeyC, sKeyC,3,7);

    //Declaration:
    char* message = key_to_str(pKeyC);
    char* electeur = key_to_str(pKey);
    printf("%s vote pour %s\n",electeur, message);
    printf("\n");

    free(electeur);

    Signature* sgn = sign(message, sKey);
    printf("signature : ");
    print_long_vector(sgn->content,sgn->size);

    chaine = signature_to_str(sgn);
    printf("signature to str : %s \n", chaine);

    free_signature(sgn);

    sgn = str_to_signature(chaine);
    printf("str to signature : ");
    print_long_vector(sgn->content,sgn->size);

    free(chaine);
    
    //Testing protected:
    Protected* pr = init_protected(pKey,message, sgn);

    free(message);
    

    //Verification:
    if (verify(pr)){
        printf("Signature valide\n");
    }else{
        printf("Signature non valide\n");
    }
    chaine = protected_to_str(pr);
    printf("protected to str : %s\n", chaine);

    //free_protected(pr); //4 erreurs mais 34 allocs pour 34 frees
    
    free(pr); //0 erreurs mais manque 4 frees
    
    pr = str_to_protected(chaine);

    char* m = key_to_str(pr->pKey);
    char* sign = signature_to_str(pr->signature);

    printf("str to protected : %s %s %s\n",m,pr->message,sign);

    free(chaine);
    free(m);
    free(sign); 
    free_protected(pr);
    free_signature(sgn);
    free(pKey);
    free(sKey);
    free(pKeyC);
    free(sKeyC);
    

}

