/* tri.h (IGI-3005)

  JCG 15/09/2008
  maj 07/12/2017
  DV  2024-11-22

  fonctions de tri
*/


int tri_echange(double t[], int n); /* le tri bulle de base */
int tri_bulle_1(double t[], int n); /* le tri bulle de base amélioré*/
int tri_bulle_2(double t[], int n); /* le tri bulle de base optimisé*/

int tri_insertion_seq(double t[], int n);
int tri_insertion_dicho(double t[], int n);
int tri_selection(double t[], int n);

int tri_shell(double t[], int n);

int tri_rapide_1(double t[], int n);
int tri_rapide_2(double t[], int n);

int tri_tas(double t[], int n);
