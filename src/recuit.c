#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "structuresDonnees.h"
#include "recuit.h"
#include "glouton.h"
#include "simplelocalSearh.h"
float probabilite_acceptation(float delta);
void recuit(int **A,int* X,int* C,int nb_cte, int nb_var,int iteration,int *z_solution){
  printf("DEMARRAGE RECUIT\n");
  //Construction gloutonne
  glutonConstruction(A,X,C,nb_cte,nb_var);
  affiche_tab_int(X,nb_var);
  *z_solution = 0;
  //printf("Z = %d \n",*z_solution);
  printf("FIN CONSTRUCTION \n");
  //*z_solution = evaluerFonctionEconomique(X,C,nb_var);
  int n = 0;
  int *voisin = NULL;
  int *solution = NULL;
  float delta = 0;
  float probabilite_accept;
  int solution_courante = 0;
  for (int i = 0; i < nb_var; i++) {
    solution[i] = X[i];
    voisin[i] = X[i];
  }
  int *zSolution_courante = &solution_courante;
  *zSolution_courante = evaluer_fonction_economique(solution,C,nb_var);
  //pire solutin durant les iterations
  int *pire_solution = NULL;
  pire_solution = malloc(sizeof(int));
  *pire_solution = 0;
  voisin = malloc(nb_var * sizeof(int));
  solution = malloc(nb_var * sizeof(int));
  if (solution == NULL || voisin == NULL){
			printf("Insuffisance de memoire pour allouer une table de contraintes ou d'utilités\n");
			exit(1);
	}
  do {
    n++;
    //tirer un voisin de X
    rechercheLocaleSimple(A,voisin,C,zSolution_courante,nb_cte,nb_var,1,0,50,pire_solution);
    //calcule de delta
    delta = evaluer_fonction_economique(voisin,C,nb_var) - evaluer_fonction_economique(solution,C,nb_var);
    //generer probabilite_acceptation
    probabilite_accept = rand()%11;
    probabilite_accept = probabilite_accept/10;
    //tester la qualité de la solution
    if ( delta < 0.0 || probabilite_accept < probabilite_acceptation(delta)) {
      // S <- S'
      for (int i = 0; i < nb_var; i++) {
        solution[i] = voisin[i];
      }
      *zSolution_courante = evaluer_fonction_economique(voisin,C,nb_var);
      if ( evaluer_fonction_economique(voisin,C,nb_var) < *z_solution) {
        for (int i = 0; i < nb_var; i++) {
          X[i] = voisin[i];
        }
        *z_solution = evaluer_fonction_economique(voisin,C,nb_var);
      }
    }
    //Mettre à jour T
  } while(n != iteration);

  free(pire_solution);
  free(voisin);
  free(solution);
}
float probabilite_acceptation(float delta){
    int temps = 0;
    temps = clock()/CLOCKS_PER_SEC;
  return exp(-delta/temps);
}
