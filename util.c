/* util.c (IGI-3005)

  JCG 15/09/2008
  maj 07/12/2017
  DV  2024-11-22

  fonctions utilitaires :
    - saisies diverses
    - verification de tri
    - remplissage de tableau
    - affichage de tableau
*/

#include "util.h"
#include <stdlib.h> /* pour rand() */
#include <stdio.h>


char buffer[256];

/* saisie une reponse d'au plus 255 caracteres */
char *saisie_rep() { 
    fgets(buffer,255,stdin);
    buffer[255]='\0';
    return buffer;
}

/* saisie d'un entier */
int saisie_int() { 
    char *rep=saisie_rep();
    return atoi(rep);
}

/* saisie d'un double */
double saisie_double() { 
    char *rep=saisie_rep();
    return atof(rep);
}


/* verification qu'un tableau est trie */
int verif_trie(double v[], int n) {
    int i;
    for (i = 1 ; i < n; ++i) 
        if (v[i] < v[i-1])
            return 0;
    return 1;
}


/* remplissage d'un tableau de n double triés */
int remplirTrie(double v[], int n){
    int i;
    for (i = 0 ; i < n ; ++i)
        v[i] = (double)i;
    return 0;
}

/* remplissage d'un tableau de n double inversés */
int remplirInverse(double v[], int n){
    int i;
    for (i = 0 ; i < n ; ++i)
        v[i] = (double)(n-i);
    return 0;
}

/* remplissage d'un tableau de n double aléatoires */
int remplirAlea(double v[], int n){
    int i;
    for (i = 0 ; i< n ;++i)
        v[i] = rand() / 100000.0;
    return 0;
}

/* trié par morceaux */
int remplirTrieParMorceaux(double v[], int n){
    int i;
    v[0] = rand()/100000.0;

    for (i = 1 ; i < n ; ++i) {
        if (rand() % 100 < 99)  /*  99 fois sur 100 on met un nombre superieur au precedent */
            v[i] = v[i-1] + rand() / 100000.0;
        else /*  1 fois sur 100 on recommence une serie */
            v[i]=rand() / 100000.0;
    }
    return 0;
}


/* affichage  */
void affiche(double t[], int n) {
    int i;
    for (i=0;i<n;++i) {
        printf("%10.2f",t[i]);
    }
    printf("\n");
}
