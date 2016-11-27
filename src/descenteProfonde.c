#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "descenteProfonde.h"
#include "structuresDonnees.h"
#include "mouvement.h"
#include "liste.h"
void descenteProfonde(int **A,int* X,int* C,int *z,int nb_cte, int nb_var,int K, int P,int iter,int * pire_solution){
  int n=0,test=1,mouvementGenerateur=0,firstStep=1;
  int* voisin;
  int* solution;
  int* best_solution;
  listes *bigGenerateur;
  bigGenerateur = malloc(3 * sizeof(listes));
  //format du big generateur valeurdeRetour->generateurK->generateurP
  voisin = malloc(nb_var * sizeof(int));
  solution = malloc(nb_var * sizeof(int));
  best_solution = malloc(nb_var * sizeof(int));
  if (voisin == NULL || bigGenerateur == NULL || solution == NULL || best_solution == NULL){  // On vérifie si l'allocation a marché ou non
      printf("Insuffisance de memoire pour allouer une table\n");
      exit(0); // On arrête tout
  }
  for (int i = 0; i < 3; i++) {
    bigGenerateur[i]=NULL;
  }
  for(int j=0;j<nb_var;j++){
    best_solution[j] = X[j];
  }
  do {
    n++;
    printf("iter = %d\n",n);
    for(int j=0;j<nb_var;j++){
      solution[j] = best_solution[j];
    }
    printf("Mis a jour solution\n");
    if (firstStep == 1){
      printf("firstStep\n");
      //premier mouvement pour cet x solution
      mouvementGenerateur=1;
      firstStep = 0;
    }
    else{mouvementGenerateur=0;}
    for(int j=0;j<nb_var;j++){
      voisin[j] = solution[j];
    }
    bigGenerateur = mouvementKPExchange(voisin,nb_var,K,P,bigGenerateur,mouvementGenerateur);
    test = bigGenerateur[0]->contenu;
    while (test != 0){
      affiche_tab_int(voisin,nb_var);
      printf("\n");
      //tester si le voisin est valide et l'ajouter
      if (valideVoisin(A,voisin,nb_cte,nb_var) == 1) {
        if (evaluer_fonction_economique(voisin,C,nb_var) < evaluer_fonction_economique(best_solution,C,nb_var) ) {
          //mettre à jour best_solution
          for(int j=0;j<nb_var;j++){
            best_solution[j] = voisin[j];
          }
        }
        else{
          if (evaluer_fonction_economique(voisin,C,nb_var) > *pire_solution) {
            *pire_solution = evaluer_fonction_economique(voisin,C,nb_var);
          }
        }
      }
      for(int j=0;j<nb_var;j++){
        voisin[j] = best_solution[j];
      }
      bigGenerateur = mouvementKPExchange(voisin,nb_var,K,P,bigGenerateur,mouvementGenerateur);
      test = bigGenerateur[0]->contenu;
    }
    *z = evaluer_fonction_economique(best_solution,C,nb_var);
    listes impasse;
    for (int i = 0; i < 3; i++) {
      while (bigGenerateur[i]!=NULL) {
        impasse = bigGenerateur[i];
        bigGenerateur[i]=bigGenerateur[i]->next;
        free(impasse);
      }
    }
    firstStep = 1;
    printf("\n Iteration %d \t",n);
    printf("\t solution actuelle = %d\n", *z);
  } while(n<iter);
  free(bigGenerateur[0]);
  free(bigGenerateur[1]);
  free(bigGenerateur[2]);
  free(bigGenerateur);
  free(voisin);
  free(solution);
  free(best_solution);
}
