/* tri.c (IGI-3005)

  JCG 15/09/2008
  maj 07/12/2017
  DV  2024-11-22
  
  fonctions de tri
*/
#include <stdio.h>


/* utilitaires */

/* permutation de deux doubles */
void permute(double *x, double *y) {
    double tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}




int tri_echange(double t[], int n) {
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            /* si t[i] > t[j], i < j, échanger */
            if (t[i] > t[j]) {
                permute(&t[i], &t[j]);
            }
        }
    }
    return 0;
}

/********************************************
*                 TRI BULLE                 *
********************************************/




/*
  tri bulle de base : n-1 balayages 
  le balayage n°i ne compare que n-i couples 
*/
int tri_bulle_1(double t[], int n) {
    /* a ecrire, une fois ecrit modifiez le return -1 en return 0 */
    return -1;
}


/*
  tri bulle optimise : n-1 balayages au maximum
  le balayage n°i ne compare que n-i couples 
  des que le tableau est trie, on termine le programme
*/
int tri_bulle_2(double t[], int n) {
    /* a ecrire, une fois ecrit modifiez le return -1 en return 0 */
    return -1;
}





/********************************************
*               TRI SELECTION               *
********************************************/

int tri_selection(double *v, int n) {
    /* a ecrire, une fois ecrit modifiez le return -1 en return 0 */
    return -1;
}





/********************************************
*               TRI INSERTION               *
********************************************/

/*
  trouve place dichotomique d'un double dans un tableau trie 
*/
int trouve_place_dicho(double x, double t[], int n) {
    /* a ecrire, une fois ecrit modifiez le return -1 en return pos
        (la position d'insertion de x (cf. TP3) */
    return -1;
}

/*
  trouve place sequentielle d'un double dans un tableau trie 
*/
int trouve_place_seq(double x, double t[], int n) {
    /* a ecrire, une fois ecrit modifiez le return -1 en return pos
        (la position d'insertion de x (cf. TP3) */
    return -1;
}

/*
  decalage droite de p a q inclus
  [p..q] -> [p+1..q+1]
*/
void decaleD(double t[], int p, int q) {
    /* a ecrire */
    return;
} 

/*
  tri par insertion (recherche sequentielle)
*/
int tri_insertion_seq(double t[], int n) {
    /* a ecrire, une fois ecrit modifiez le return -1 en return 0 */
    return -1;
}

/*
  tri par insertion (recherche dichotomique)
*/
int tri_insertion_dicho(double t[], int n) {
    /* a ecrire, une fois ecrit modifiez le return -1 en return 0 */
    return -1;
}





/********************************************
*                 TRI SHELL                 *
********************************************/
int tri_shell(double t[], int n) {
    int ecart, sous_tableau, i, j;
    for (ecart = n / 2 ; ecart > 0 ; ecart /= 2)  /* comp. éléments distants de ecart*/
        for (sous_tableau = 0 ; sous_tableau < ecart ; ++sous_tableau ) /* il y 'ecart' sous-tableaux distants de 'ecart' */
            for (i = sous_tableau ; i + ecart < n  ; i += ecart)
                for (j = i ; j >= 0 && t[j] > t[j + ecart] ; j -= ecart)  
                    permute(&t[j], &t[j + ecart]);
    return 0;
}





/********************************************
*                 TRI RAPIDE                *
********************************************/

/*
  la partition vue en cours
*/
int partition(double t[], int d, int f) {
    /* a ecrire, une fois ecrit modifiez le return -1 en return pos 
        (la frontiere entre petits et grands ) */
    return -1;
}


/*
  quicksort version de base
*/
int tri_rapide_1(double t[], int n) { 
    /* a ecrire, une fois ecrit modifiez le return -1 en return 0 */
    return -1;
}


/*
  quick sort améliore si n<=6, on fait un shell sort 
*/
int tri_rapide_2(double t[], int n) { 
    /* a ecrire, une fois ecrit modifiez le return -1 en return 0 */
    return -1;
} 





/********************************************
*                TRI PAR TAS                *
********************************************/

/*
  retablir un tas
  tous les arbres sous 'pere_a_retablir' sont des tas sauf peut etre 'pere_a_retablir'
 */
void retablir_tas(double t[], int n, int pere_a_retablir) {
    int pere = pere_a_retablir;
    int fils_le_plus_grand = 2 * pere + 1; /* le fils gauche */

    /* 
      On va comparer l'élément à la position 'pere' à ses fils, 
      si inférieur a un des fils, permuter avec le plus grand.
      Si on permute, il faut en plus verifier le nouveau fils "recursivement"
    */
    while (fils_le_plus_grand < n) {
        /* si le fils droit existe et est plus grand, c'est lui que l'on compare au pere */
        if (fils_le_plus_grand + 1 < n && t[fils_le_plus_grand + 1] >= t[fils_le_plus_grand]) {
            ++fils_le_plus_grand;
        }
        if (t[fils_le_plus_grand] > t[pere]) {
            permute(&t[fils_le_plus_grand], &t[pere]);
            /* Verifier position 'fils_le_plus_grand' */
            pere = fils_le_plus_grand;
            fils_le_plus_grand = 2*pere+1;
        }
        else { /* le pere est plus grand que ses fils  */
            break;
        }
    }
}

/*
  Convertit un tableau en un tas (en format tableau), en place
*/
void convertir_en_tas(double t[], int n) {
    /* 
      Appeler retablir_tas pour chaque indice de n-1 a 0
      Inutile de verifier les indices jusqu'à (n-1)/2,
      parce qu'ils ont pas de fils */
    for (int i=(n-1)/2; i>=0; i--)
        retablir_tas(t, n, i);
}

/*
  Extrait l'élément maximal et le place à la position n
*/
void extraire_max(double t[], int n) {
    /* L'élément maximal est à position 0, permute-le avec t[n] 
       À partir de ce point, on considère que la taille est n-1
    */
    permute(&t[n-1], &t[0]);
    /* On a probablement détruit la propriété du tas, 
       appeler retablir_tas pour la rétablir à la position changée */
    retablir_tas(t, n-1, 0);
}

int tri_tas(double t[], int n) {
    /* a ecrire, une fois ecrit modifiez le return -1 en return 0 */
    return -1;
}
