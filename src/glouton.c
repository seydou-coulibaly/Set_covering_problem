#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "glouton.h"
#include "mouvement.h"
#include "structuresDonnees.h"
#include "simplelocalSearh.h"
#include "descenteProfonde.h"

void glutonConstruction(int **A,int* X,int* C,int nb_cte, int nb_var){
  int* contraintes = NULL;
  float* U = NULL;
  int * coef = NULL;
  int min;
  contraintes = malloc(nb_cte * sizeof(int));
  coef = malloc(nb_var * sizeof(int));
  U = malloc(nb_var * sizeof(float));
  if (contraintes == NULL || U == NULL || coef == NULL){ // On vérifie si l'allocation a marché ou non
    printf("Insuffisance de memoire pour allouer une table de contraintes ou d'utilités\n");
    exit(0); // On arrête tout
    }
  /* Initialisation matrice des contraintes modifies au fur et à mesure par gluton*/
   initialiser_tab_int(contraintes,nb_cte,1);
  /* Initialisation utilité*/
  initialiser_tab_float(U,nb_var,0);
  /* Initialisation coef*/
  initialiser_tab_int(coef,nb_var,0);
  do {
        coefficient(coef,nb_var,contraintes,nb_cte,A);  //mets à jour la table coefficient
        for(int j= 0 ;j<nb_var;++j){
          if(coef[j] == 0){ //si coef est nulle, inutile de le compte dans la solution
            U[j]=(float) maximum_element(C, nb_var);
          }else{
            U[j] = C[j]/(float) coef[j];  //calcule l'utilite
          }
        }
        initialiser_tab_int(coef,nb_var,0); //on remet tous les coef à 0 pour la prochaine Iteration
        // j'essaye maintenant de comparer les utilites et de prendre le min
        min = minimum_utilite(U,nb_var,X);
        X[min] = 1; // min est dans ma solution
        //On annule ou desacctive les lignes de min avec le coef 1 //
        for (int i=0; i<nb_cte; i++){
          if(A[i][min] == 1){
          contraintes[i] = 0;
          }
        }
      } while(table_nulle_test(contraintes, nb_cte)!= 1);
      //Liberation de l'espace alouer//
      free(contraintes);
      free(U);
      free(coef);
    }
    void methodeGlouton(int **A,int* X,int* C,int *z_solution,int nb_cte, int nb_var){
    printf("****************************** METHOD GLOUTON EXECUTION ******************************\n");
    printf("\n\t--->  CONSTRUCTION GLUTON \n");
    glutonConstruction(A,X,C,nb_cte,nb_var);
    affiche_tab_int(X,nb_var);
    printf("\tZ = %d",evaluer_fonction_economique(X, C,nb_var));
    *z_solution = evaluer_fonction_economique(X, C,nb_var);

    printf("\n\n\t--->  DECESNTE\n");
    int iteration_descente_simple = 500;
    //int iteration_descente_profonde = 3;
    int *pire_solution = NULL;
    pire_solution = malloc(sizeof(int));
    *pire_solution = 0;
    rechercheLocaleSimple(A,X,C,z_solution,nb_cte,nb_var,1,0,iteration_descente_simple,pire_solution);
    //descenteProfonde(A,X,C,z_solution,nb_cte,nb_var,1,0,iteration_descente_profonde,pire_solution);
    //afficheTableau(X,nb_var);
    *z_solution = evaluer_fonction_economique(X,C,nb_var);
    //printf("\n\t\t\tBetter solution after %d iteration, Z = %d\n\n",iteration_descente_simple,*z_solution);
    free(pire_solution);
}
