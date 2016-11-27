#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graspConstruction.h"
#include "structuresDonnees.h"
#include "mouvement.h"
#include "liste.h"

void graspConstruction(int **A,int* X,int* C,int nb_cte,int nb_var,float alpha){
  int* contraintes = NULL;
  float* U = NULL;
  int * coef = NULL;
  listes RCL ;
  contraintes = malloc(nb_cte * sizeof(int));
  coef = malloc(nb_var * sizeof(int));
  U = malloc(nb_var * sizeof(float));
  int min = 0, i = 0,j = 0, tailleRCL = 0;
  float limiteRCL = 0;
  if (contraintes == NULL || U == NULL || coef == NULL) // On vérifie si l'allocation a marché ou non
    {
      printf("Insuffisance de memoire pour allouer une table de contraintes ou d'utilités\n");
      exit(0); // On arrête tout
    }
  initialiser_tab_int(contraintes,nb_cte,1);     /* Initialisation matrice des contraintes modifies au fur et à mesure par gluton*/
  initialiser_tab_float(U,nb_var,0);              /* Initialisation utilité*/
  initialiser_tab_int(coef,nb_var,0);           /* Initialisation coef*/
  do {
    coefficient(coef,nb_var,contraintes,nb_cte,A);  //mets à jour la table coefficient
    for(j= 0 ;j<nb_var;++j){
      if(coef[j] == 0){
        U[j]=(float) maximum_element(C, nb_var);
      }else{
        U[j] = C[j]/(float) coef[j];  //calcule l'utilite
      }
  }
  limiteRCL = limite(U,nb_var,alpha,X);     //calculer la limite RCL
  RCL = NULL;
  for(j= 0 ;j<nb_var;++j){
    if (U[j]<= limiteRCL) {
      RCL = ajoutListe(RCL,j);
    }
  }
  tailleRCL = sizeListe(RCL);
  if (tailleRCL == 1) {
    min = 1;
  }else{
    min = rand()%(tailleRCL-1) +1;  //le rand generé et pas le confondre avec le minimum au sens propre
  }
  min = recupererPosition(RCL,min);   //on essaye de recuperer l'element de l'indice min
  X[min] = 1; // min est dans ma solution
  /*On annule ou desactive les lignes de min avec le coef 1 */
  for (i=0; i<nb_cte; i++){
    if(A[i][min] == 1){
      contraintes[i] = 0;
    }
  }
  initialiser_tab_int(coef,nb_var,0);   //on remet tous les coef à 0 pour la prochaine Iteration
  removeListe(RCL);
} while(table_nulle_test(contraintes, nb_cte) != 1);
  /*Liberation de l'espace alouer*/
  free(contraintes);
  free(U);
  free(coef);
}
