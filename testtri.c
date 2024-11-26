/* testtri.c (IGI-3005)

  JCG 15/09/2008
  maj 07/12/2017
  DV  2024-11-22

  fonction de tests et de chronometrages de differents tris */

#include <stdio.h> /* pour affichages */
#include <stdlib.h> /* pour malloc */
#include <ctype.h> /* pour tolower() dans le choix de menu */

#include <time.h> /* pour l'initialisation du geneateur de nombres  aleatoires */

#include <setjmp.h> /* pour l'interruption en cas de depassement de temps */

#include "util.h" /* les differents remplissages et utilitaires*/
#include "tri.h" /* les differents tris */

#include "chrono.h" /* gestion du chronometrage et des interruptions en cas de depassement de temps */



/*
  le type type_fonction :
  pointeur sur fonction a parametre double* et int
  et a retour int
  Les fonctions de remplissage et de tris sont de ce type 
*/
typedef int (* type_fonction)(double *, int); 


/* 
  Le type des fonctions de tri et de remplissage, 
  associes a un nom, pour les messages 
*/
typedef struct {
  type_fonction f;
  char *nom;
} fonction; 

/*
  Mettre ici toutes les fonctions de tris et leurs noms pour affichage
  Commentez les lignes pour qu'elles n'apparaissent pas. 
*/ 
fonction tri[]={
    {tri_echange,          "Tri simple"},
    {tri_bulle_1,          "Tri bulle de base"},
    {tri_bulle_2,          "Tri bulle ameliore"} ,

    {tri_selection,        "Tri par selection"} ,

    {tri_insertion_seq,    "Tri par insertion (seq.)"},
    {tri_insertion_dicho,  "Tri par insertion (dicho)"},
    {tri_shell,            "Tri shell"},

    {tri_rapide_1,         "Tri rapide"},
    {tri_rapide_2,         "Tri rapide (shell si n<=6)"},

    {tri_tas,              "Tri par tas"},
};

/* calcul automatique du nombre de tris  */
int nb_tri=sizeof(tri)/sizeof(tri[0]);



/*
  Mettre ici les fonctions de remplissage et leurs noms pour affichage
  Commentez les lignes pour qu'elles n'apparaissent pas. 
*/ 
fonction rempl[]={
    {remplirTrie,"croissant"},
    {remplirInverse,"decroissant"},
    {remplirAlea,"aleatoire"},
    {remplirTrieParMorceaux,"trie par morceaux"}
}; 

/* calcul automatique du nombre de remplissages */ 
int nb_rempl=sizeof(rempl)/sizeof(rempl[0]); 




#define TRI_PAS_ECRIT (-3.0)
#define  ERREUR_TRI (-2.0)
#define  HORS_DELAI (-1.0)

/*
  chronometre
    chronometre le temps d'execution d'un tri 
    d'un tableau 'w' de 'n' double.
    Le temps de tri est limite a 'limite' secondes
    Le tri s'interrompra avant la fin si la limite de temps est atteinte
    Retourne le temps de tri s'il s'execute 
    en moins de 'limite' secondes
    retourne -1.0 si le tri a ete interrompu avant la 'limite'
*/
double chronometre(type_fonction ftri, double w[], int n, double limite) {
    /* env : sauvegarde ou restitution de l'environnement 
     declaration dans chrono.c */
    extern sigjmp_buf environnement_de_reprise;

    /* marquage du point de reprise : 
     * on sauvegarde l'environnement d'execution :
     * le retour est 0 lors de l'appel
    * si on revient ici (a cause d'un appel a siglongjump), 
    * le retour sera non nul.
    * Lors de l'interruption due a un timer, (depassement du 
    * temps autorise pour le tri, on reviendra ici 
    */ 
    if (sigsetjmp(environnement_de_reprise, 1) == 0) {
        lanceChrono(limite);

        if (ftri(w, n) != 0) { /* si tri non encore ecrit */
            arretChrono();
            return TRI_PAS_ECRIT;
        } 
        else { /* tri ecrit */
            arretChrono(); 
            if (verif_trie(w, n)) /* si le tableau est trie */
                return lectureChrono(); /* retour du temps mis a trier */
            else { /* erreur tri */
                return ERREUR_TRI; 
            }
        }
    }
    else {
        return HORS_DELAI ; /* tri interrompu par temps limite */
    }
}

/*
  chronometre le temps d'execution d'une 'fonction_de_tri'
  d'un tableau de 'n' elements initialise  par une 'fonction_de_remplissage '
  (temps de tri borne par 'limite' secondes )
*/
double chrono_rempl(type_fonction fonction_de_tri,  type_fonction fonction_de_remplissage, int n, double limite) {
    double *tableau_dyn, temps;

    /* allocation dynamique du tableau */
    if ((tableau_dyn = (double *) malloc(n * sizeof(double))) == NULL) {
        fprintf(stderr, "probleme d'allocation de memoire");
        exit(1);
    }

    /* on remplit le tableau */
    fonction_de_remplissage(tableau_dyn, n);

    /* on chronometre le tri */
    temps = chronometre(fonction_de_tri, tableau_dyn, n, limite);

    /* on libere la memoire allouee */
    free(tableau_dyn);

    /* on retourne le temps mis a trier */
    return temps;
}




/*
  Les fonctions de test
*/

char affiche_menu_opt(char* rempl_nom, int nbelts, char* tri_nom, double tps_max) {
    /* etat actuel */
    printf("\n--------------- Configuration actuelle --------------\n\n");
    printf("%-20s : %-15s\n%-20s : %d\n%-20s : %-30s\n%-20s : %.3f s\n",
             "Remplissage", rempl_nom,
             "Taille", nbelts,
             "Tri",  tri_nom, 
             "Limite de temps", tps_max); 

    /********************* MENU *****************************/
    printf("\n\t\t--- Menu ---\n");
    printf("\t1. Lancer l'e(x)ecution du tri choisi\n");
    printf("\t2. L(a)ncer l'execution de tous les tris pour la configuration actuelle \n");
    printf("\n");

    printf("\t3. Changer de (r)emplissage\n");
    printf("\t4. Changer de (t)ri\n");
    printf("\t5. Changer le (n)ombre d'elements du tableau\n");
    printf("\t6. Changer la (l)imite de temps\n");
    printf("\n");
    printf("\t0. (Q)uitter le programme\n");

    /**************************** reponse  ***********************/
    char  *rep = saisie_rep();
    return tolower(rep[0]);
}

int testtri() { 
    double tps_max = 2.0;  /* temps limite */
    double x;              /* double pour la saisie */
    double t;              /* temps de tri */


    char op;               /* reponse utilisateur */
    int i;                 /* compteur */
    int n;                 /*nombre saisi */
    int numtri = 0;        /* numero de la fonction de tri */
    int numrempl = 2;      /* numero de la fonction de remplissage */

    int nbelts = 10000;    /* nombre d'elements du tableau */
    int fin = 0;           /* pour terminer */

    /* pour initialiser le generateur de nombres aleatoires */
    srand(time(NULL));

    do {
        op = affiche_menu_opt(rempl[numrempl].nom, nbelts, tri[numtri].nom, tps_max);

        printf("\n-----------------------------------------------------\n");
        if (op == 'x' || op == '1') {
            /* Tri selectionne */
            printf("%s sur tableau %s de %d nombres :\n ",
                     tri[numtri].nom, rempl[numrempl].nom, nbelts); 

            t = chrono_rempl(tri[numtri].f, rempl[numrempl].f, nbelts, tps_max);

            if (t >= 0) 
                printf("\tTri effectue en %.3f s\n", t);
            else if (t == HORS_DELAI) 
                printf("\t Tri non termine en %.3f s\n", tps_max);
            else if (t == ERREUR_TRI)
                printf("\t Tri defectueux! A reecrire !\n");
            else if (t == TRI_PAS_ECRIT)
                printf("\t Tri non encore ecrit !\n");
            fin = 1;
        }
        else if (op == 'a' || op == '2') {
            printf("Tous les tris d'un tableau %s de %d nombres :\n\n",
                     rempl[numrempl].nom, nbelts); 

            for (i = 0; i < nb_tri; ++i) {
                printf("\t%-30s", tri[i].nom);

                t = chrono_rempl(tri[i].f, rempl[numrempl].f, nbelts, tps_max);
                if (t >= 0) 
                    printf("%10.5f s\n", t);
                else if (t == HORS_DELAI) 
                    printf(">> %7.5f s\n", tps_max);
                else if (t == ERREUR_TRI) 
                    printf("defectueux \n");
                else if (t == TRI_PAS_ECRIT) 
                    printf("\t Tri non encore ecrit !\n");
            }
            fin = 1;
        }
        else if (op == 'r' || op == '3') {
            /* menu de choix du remplissage */
            for(;;) {
                printf("\nEntrez le numero du type de remplissage (0 pour quitter)\n"); 

                for (i = 0 ; i < nb_rempl ; ++i)
                    printf("\t%d. %s\n", i+1, rempl[i].nom);

                printf("Votre choix ? ");
                n = saisie_int();
                if (0 <= n && n <= nb_rempl) /* si saisie valide */
                    break; /* du for */
                printf("%d : choix invalide \n\n", n);
            }

            if (n > 0)
                numrempl = n - 1;
        }
        else if (op == 't' || op == '4') {
            /* menu de choix du tri */
            for(;;) {
                  printf("\nEntrez le numero du de tri (0 pour quitter)\n"); 
                  for (i = 0 ; i < nb_tri ; ++i) {
                    printf("\t%d. %s\n", i+1, tri[i].nom);
                  } 
                  printf("Votre choix ? ");
                  n = saisie_int();
              if (0 <= n && n <= nb_tri) /* si saisie valide */
                break; /* du for */
                  printf("%d : choix invalide \n\n", n);
            }

            if (n > 0)
                  numtri = n - 1;

        }
        else if (op == 'n' || op == '5') {
            /* choix du nombre d'elements */
            printf("\nEntrez la taille du tableau a trier (0 pour quitter) : ");

            n = saisie_int();
            if (n < 0 )  /* on ne change pas */
                  printf("%d : nb elements impossible \n\n", n);
            if (n > 0)  /* on change nbelts */
                  nbelts = n;
        }
        else if (op == 'l' || op == '6') {
            /* saisie du temps max autorisé */
            printf("\nEntrez le temps maximum autorise (0 pour quitter) : ");

            x = saisie_double();
            if (x < 0) 
                  printf("%.3f : temps maxi autorise impossible \n\n", x);
            if (x > 0) 
                  tps_max = x;
        }
        else if (op == 'q' || op == '0') {
            /* fin du programme */
        fin = -1;
        }

        if (fin == 1) {
            printf("\n-----------------------------------------------------\n");
            printf("Tapez <Entr> pour continuer");
            getchar();
            fin = 0;
        }
    } while (! fin);

    return 0;
}

