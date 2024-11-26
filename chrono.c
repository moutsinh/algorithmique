/* chrono.c (IGI-3005)

  JCG 15/09/2008
  maj 07/12/2017
  DV  2024-11-22

  fonctions de chronometrage 
*/
#include <unistd.h> 
#include <signal.h>
#include <setjmp.h>
#include <sys/time.h> 

#include "chrono.h"


#define TMAX 2

sigjmp_buf environnement_de_reprise; /* sauvegarde ou restitution de l'environnement */

static  struct sigaction mon_action;

static  struct itimerval ancienne_valeur, valeur, annulation;


/* 
  gestionnaire d'interruption : on fait un GOTO l'endroit ou on a pose un point de reprise 
  (en debut de la fonction qu'on chronometre ) 
*/
void gestionnaire(int sig) {
    siglongjmp(environnement_de_reprise, 1);
}


/* lancement du chronometre pour un temps 'limite' */
void lanceChrono(double limite) {
    valeur.it_interval.tv_sec = 0;

    valeur.it_interval.tv_usec = 0;

    valeur.it_value.tv_sec = (int)limite;
    valeur.it_value.tv_usec = (int)((limite-(int)limite)*1000000);

    annulation.it_interval.tv_sec = 0;
    annulation.it_interval.tv_usec = 0;

    annulation.it_value.tv_sec = 0;
    annulation.it_value.tv_usec = 0;

    mon_action.sa_handler = gestionnaire;
    sigaction(SIGALRM, &mon_action, NULL);
    setitimer(ITIMER_REAL, &valeur, NULL);
}

/* arret du chronometre  */
void arretChrono() {
    getitimer(ITIMER_REAL, &ancienne_valeur);
    setitimer(ITIMER_REAL, &annulation, NULL);
}

/* consultation du du chronometre  */
double lectureChrono() {
    double z1 = valeur.it_value.tv_sec + valeur.it_value.tv_usec / 1000000.0,
           z2 = ancienne_valeur.it_value.tv_sec + ancienne_valeur.it_value.tv_usec / 1000000.0;
    return z1 - z2;
}
