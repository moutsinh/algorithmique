/* util.h (IGI-3005)

  JCG 15/09/2008
  maj 07/12/2017
  DV  2024-11-22

  fonctions utilitaires :
    - vérification de tri
    - remplissage de tableau
    - affichage de tableau
*/


#ifndef __UTIL_H__
#define __UTIL_H__

/* saisie une reponse d'au plus 255 caracteres */
char *saisie_rep() ;

/* saisie d'un entier */
int saisie_int();

/* saisie d'un double */
double saisie_double() ;


/* verification qu'un tableau est trie */
int verif_trie(double *v, int n) ;


/* remplissage d'un tableau de n double triés */
int remplirTrie(double v[], int n); 

/* remplissage d'un tableau de n double inversés */
int remplirInverse(double v[], int n);

/* remplissage d'un tableau de n double aléatoires */
int remplirAlea(double v[], int n);

/* trié par morceaux */
int remplirTrieParMorceaux(double v[], int n);


/* affichage  */
void affiche(double t[], int n) ;

#endif
