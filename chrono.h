/* chrono.h (IGI-3005)

  JCG 15/09/2008
  maj 07/12/2017
  DV  2024-11-22

  fonctions de chronometrage 
*/

#ifndef __CHRONO_H__
#define __CHRONO_H__

/* lancement du chronometre pour un temps 'limite' */
void lanceChrono(double limite) ;

/* arret du chronometre  */
void arretChrono() ;

/* consutlation du du chronometre  */
double lectureChrono() ;

#endif
