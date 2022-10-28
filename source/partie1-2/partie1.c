#include "../../headers/partie1.h"

//1.1
//Complexité en O(p)
int is_prime_naive(long p){
    long cpt = 3;
    while (cpt < p){
        if(cpt % p == 0){
            return 1;
        }
        cpt++;
    }
    return 0;
}

//1.2
/*Le nombre 475000000 est le plus grande nombre premier que l'on peu utiliser dans notre fonction
en moins de deux secondes. Elle met 1.895942 secondes.
*/

//1.3 
long modpow_naive(long a, long m, long n){
    for(int i = 0; i < m; i++){
        a = (a * a) % n;
    }
    return a;
}
//Complexité en O(m)

//1.4
long modpow(long a, long m, long n){
    long p;
    for(p = 1; m > 0; m = m/2){
        if(m%2 != 0){
            p = (p*a)%n;
        }
        a = (a*a) % n;
    }
    return p;
}

void ecriture(long a, long m, long n){
    
    FILE* fd = fopen("fichiers/fichier.txt", "a");
    if(fd == NULL){
        printf("Erreur : ouverture du fichier dans ecriture\n");
    }
    
    clock_t t_init;
    clock_t t_final;
    double temp_cpu1;
    double temp_cpu2;

    t_init=clock();
    modpow_naive(a,m,n);  
    t_final = clock();
    temp_cpu1 = ((double)(t_final - t_init) / CLOCKS_PER_SEC);


    t_init=clock();
    modpow(a,m,n);  
    t_final = clock();
    temp_cpu2 = ((double)(t_final - t_init) / CLOCKS_PER_SEC);

    if(m==0){
        fprintf(fd,"Valeur de m | Temps fcnt normal | Temps fcnt naive\n");
    }
    fprintf(fd, "%ld\t %f\t  %f\n", m ,temp_cpu2, temp_cpu1);

    fclose(fd);
}

/*

int main(){
    //1.2
    
    clock_t t_init = clock();
    clock_t t_final ;
    double temp_cpu;
    int v = is_prime_naive(475000000);  
    t_final = clock();
    temp_cpu = ((double)(t_final - t_init) / CLOCKS_PER_SEC);

    printf("%d\n", v);
    printf("%f\n", temp_cpu); 
    
    //1.5

    srand(time(NULL));
    long a=rand(), n=rand();

    for(int i=0; i<100000 ; i=i+100){
        long m = (long) i;
        ecriture(a, m, n);
    }
    

    return 0;
}

*/


//Q1.6
int witness(long a, long b, long d, long p){
    long x = modpow(a,d,p);
    if(x == 1){
        return 0;
    }
    for(long i = 0; i < b; i++){ 
        if(x == p-1){
            return 0; 
        }
        x = modpow(x,2,p);
    }
    return 1; 
}

long rand_long(long low, long up){ 
    return rand() % (up - low +1)+low;
}

int is_prime_miller (long p, int k) {
    if (p == 2)
        return 1; 
    if (!(p & 1) || p <= 1) 
        return 0; //on verifie que p est impair et different de 1 return 0;

    //on determine b et d :
    long b = 0;
    long d = p - 1;
    while (!(d & 1))
    { //tant que d n’est pas impair
        d = d/2;
        b=b+1; 
    }
    // On genere k valeurs pour a, et on teste si c’est un temoin :
    long a;
    int i;
    for(i = 0;i<k;i++)
    {
        a = rand_long(2, p-1);
        if (witness(a,b,d,p))
            return 0;
    }
    return 1; 
}

//Q1.8
long random_prime_number(int low_size, int up_size, int k){
    //On determine le plus grand entier à up_size bits
    long up = powl(2, up_size) - 1;
    //On determine le plus petit entier à low_size bits
    long low = powl(2, low_size - 1);
    long rand = rand_long(low, up);
    
    if (is_prime_miller(rand, k) != 1){  //Si rand n'est pas premier 
        return random_prime_number(low_size, up_size, k-1);
    }else{
        return rand;
    }
}

//CHIFFREMENT ET DECHIFFREMENT DE MESSAGE
//Q2.1
long extended_gcd(long s, long t, long *u, long *v){
    if(s == 0){
        *u = 0;
        *v  = 1;
        return t;
    }
    long uPrim, vPrim;
    long gcd = extended_gcd(t%s, s, &uPrim, &vPrim);
    *u = vPrim - (t/s)*uPrim;
    *v = uPrim;
    return gcd;
}

void generate_key_values(long p, long q, long* n, long *s, long *u){
    *n = p * q;
    long t = (p - 1) * (q - 1);
    long v;
    *s = rand_long(0, t);
    long gcd = extended_gcd(*s, t, u, &v);

    if(gcd != 1) {  //on appelle la fonction récursivement tant que PGCD(s, t) != 1
        generate_key_values(p, q, n, s, u);
    }
}

//Q2.2
long *encrypt(char* chaine, long s, long n){
    int i = 0;
    long *c = (long*)malloc(strlen(chaine) * sizeof(long));
    long m;
    while(chaine[i] != '\0'){
        m = (int)chaine[i];
        c[i] = modpow(m, s, n);
        i++;
    }
    return c;
}

//Q2.3
char* decrypt(long* crypted, int size, long u, long n){
    char* msg = (char*) malloc(size + 1 * sizeof(char)); 
    int i;
    for(i = 0; i < size; i++){
        msg[i] = (char) modpow(*(crypted + i), u, n);
    }
    msg[i] = '\0';
    return msg;
}

void print_long_vector(long *result, int size){
    printf("Vector : [");
    for (int i = 0; i < size; i++){
        printf("%lx   ", result[i]);
    }
    printf("]\n");
}


