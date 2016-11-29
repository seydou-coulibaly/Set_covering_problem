#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "structuresDonnees.h"
#include "recuit.h"
#include "glouton.h"
#include "simplelocalSearh.h"
void recuit(int **A,int* X,int* C,int nb_cte, int nb_var,int iteration,int *Z,float T, int L, float alpha){
  glutonConstruction(A,X,C,nb_cte,nb_var);
  int *pire_solution = NULL;
  pire_solution = malloc(sizeof(int));
  *pire_solution = 0;
  int n = 0;
  int *voisin = NULL;
  int *solution = NULL;
  int *solution_voisin = 0;
  int solution_courante = NULL;
  solution_voisin = malloc(sizeof(int));
  *solution_voisin = 1000000;
  float *t_courant = NULL;
  int *k = NULL;
  t_courant = malloc(sizeof(float));
  k = malloc(sizeof(int));
  *t_courant = T;
  *k = 0;
  float delta = 0;
  float probabilite_generer;

  voisin = malloc(nb_var * sizeof(int));
  solution = malloc(nb_var * sizeof(int));
  if (solution == NULL || voisin == NULL || solution_voisin == NULL){
      printf("Insuffisance de memoire pour allouer une table de contraintes ou d'utilités\n");
      exit(1);
  }
  for (int i = 0; i < nb_var; i++) {
    solution[i] = X[i];
    voisin[i] = X[i];
  }
  solution_courante = evaluer_fonction_economique(solution,C,nb_var);
  do {
    n++;
    *k = *k + 1;
    //tirer un voisin de X
    rechercheLocaleSimple(A,voisin,C,solution_voisin,nb_cte,nb_var,1,0,50,pire_solution);
    *solution_voisin = evaluer_fonction_economique(voisin,C,nb_var);
    //calcule de delta
    delta = *solution_voisin - solution_courante;
    //generer probabilite_acceptation
    probabilite_generer = rand()%11;
    probabilite_generer = probabilite_generer/10;
    //tester la qualité de la solution
    if ( delta < 0.0 || probabilite_generer < probabilite_acceptation(delta,*t_courant)) {
      // S <- S'
      for (int i = 0; i < nb_var; i++) {
        solution[i] = voisin[i];
      }
      if ( *solution_voisin <  *Z) {
        for (int i = 0; i < nb_var; i++) {
          X[i] = voisin[i];
        }
        *Z = evaluer_fonction_economique(voisin,C,nb_var);
      }
    }
    //Mettre à jour T
    update(t_courant,k,L, alpha);
    if (iteration/2 == n) {
      *t_courant = T;
    }
  } while(n != iteration);

  free(pire_solution);
  free(solution_voisin);
  free(voisin);
  free(solution);
}
void update(float *t_courant,int *k, int L, float alpha){
  if (L == *k) {
    *t_courant = (*t_courant) * alpha;
    *k = 0;
  }
}
float probabilite_acceptation(float delta, float temps){
  return exp(-delta/temps);
}
