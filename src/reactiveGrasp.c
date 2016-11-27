#include <stdio.h>
#include <stdlib.h>
#include "reactiveGrasp.h"
#include "structuresDonnees.h"
#include "graspConstruction.h"
#include "reactiveGrasp.h"
#include "mouvement.h"
#include "simplelocalSearh.h"
#include "grasp.h"
#include "liste.h"
void reactiveGrasp(int **A,int* X,int *z,int* C,int nb_cte,int nb_var){
  int* pire_solution = NULL;
  int* solution = NULL;
  float *ensembleAlapha = NULL;
  float *probabiliteAlpha = NULL;
  float *q_k = NULL;
  float *z_avg_alpha = NULL;
  int *z_temp = NULL;
  pire_solution = malloc(sizeof(int));
  solution = malloc(nb_var * sizeof(int));
  z_temp = malloc(sizeof(int));
  int iteration_descente_simple = 500;
  int N_iteration_grasp = 100;
  *pire_solution = 0;
  *z_temp = 10000000;

  ensembleAlapha = malloc(11 * sizeof(float));
  probabiliteAlpha = malloc(11 * sizeof(float));
  q_k = malloc(11 * sizeof(float));
  z_avg_alpha = malloc(11 * sizeof(float));


  float alpha=0,somme=0;
  int elementGenerer = 0;
  int n=0,z_courant=0,z_best=100000,z_worst=0,max=0;
  //initialisation de l'ensemble alpha avec ses proba
  ensembleAlapha[0] = 0.0;
  ensembleAlapha[1] = 0.1;
  ensembleAlapha[2] = 0.2;
  ensembleAlapha[3] = 0.3;
  ensembleAlapha[4] = 0.4;
  ensembleAlapha[5] = 0.5;
  ensembleAlapha[6] = 0.6;
  ensembleAlapha[7] = 0.7;
  ensembleAlapha[8] = 0.8;
  ensembleAlapha[9] = 0.9;
  ensembleAlapha[10] = 1.0;
  if (ensembleAlapha == NULL || z_avg_alpha == NULL || q_k == NULL || solution == NULL || probabiliteAlpha == NULL || pire_solution == NULL || z_temp == NULL) // On vérifie si l'allocation a marché ou non
  {
    printf("Insuffisance de memoire pour allouer une table de contraintes ou d'utilités\n");
    exit(0); // On arrête tout
  }

    //iterations grasp
    initialiser_tab_float(probabiliteAlpha,11,1/10);
    initialiser_tab_float(z_avg_alpha,11,0);
    initialiser_tab_float(q_k,11,0);
    do {
      //On applique grasp sur la solution recente X
      for (int i = 0; i < nb_var; i++) {
        solution[i] = X[i];
      }
      n++;
      // valeur de alpha choisit aleatoirement
      elementGenerer = rand()%11;
      alpha = ensembleAlapha[elementGenerer];
      //printf("alpha dans la boucle %f\n",alpha);
      grasp(A,solution,C,nb_cte,nb_var,alpha,1,z_temp,pire_solution);
      rechercheLocaleSimple(A,solution,C,z_temp,nb_cte,nb_var,1,0,iteration_descente_simple,pire_solution);
      z_courant = *z_temp;
      z_avg_alpha[elementGenerer] = (z_avg_alpha[elementGenerer] + z_courant)/2;
      if (z_best > z_courant) {
        z_best = z_courant;
      }
      if(z_worst < *pire_solution){
        z_worst = *pire_solution;
      }
    } while(n < N_iteration_grasp);
    //Calcule des q_k
    for (int i = 0; i < 11; i++) {
      q_k[i] = ((z_avg_alpha[i])-(z_worst))/(z_best - z_worst);
    }
    somme = 0;
    //Calcule de la somme des q_k
    for (int i = 0; i < 11; i++) {
      somme = somme + q_k[i];
    }
    //calcule de la probabilité des elements
    for (int i = 0; i < 11; i++) {
      probabiliteAlpha[i] = q_k[i]/somme;
    }
    max = maximum(probabiliteAlpha,11);               //recuperation du max de la probabilité
    alpha = ensembleAlapha[max];                     //On a maintenant alpha
    printf("\nALPHA = %f\n\n",alpha);
    grasp(A,X,C,nb_cte,nb_var,alpha,2,z,pire_solution);
    printf("\n\n\t\t\t \t\t REACTIVE GRASP CONSTRUCTION SOLUTION	Z = %d\n\n",*z);
    rechercheLocaleSimple(A,X,C,z,nb_cte,nb_var,1,0,iteration_descente_simple,pire_solution);
    printf("\n\n\t\t\t \t\t REACTIVE GRASP FINAL SOLUTION	Z = %d\n\n",*z);
    /*Liberation de l'espace alouer*/
    free(solution);
    free(ensembleAlapha);
    free(z_avg_alpha);
    free(probabiliteAlpha);
    free(q_k);
    free(z_temp);
}
