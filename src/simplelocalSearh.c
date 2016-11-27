#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "simplelocalSearh.h"
#include "structuresDonnees.h"
#include "mouvement.h"

void rechercheLocaleSimple(int **A,int* X,int* C,int *z,int nb_cte, int nb_var,int K, int P,int iter,int * pire_solution){
  int n=0;
  int* voisin = NULL;
  listes *bigGenerateur = NULL;
  bigGenerateur = malloc(3 * sizeof(listes));
  //format du big generateur valeurdeRetour->generateurK->generateurP
  voisin = malloc(nb_var * sizeof(int));
  for (int i = 0; i < 3; i++) {
    bigGenerateur[i]=NULL;
  }
  int mouvementGenerateur = 0;
  int firstStep = 1;
  if (voisin == NULL){  // On vérifie si l'allocation a marché ou non
      printf("Insuffisance de memoire pour allouer une table\n");
      exit(0); // On arrête tout
  }

  do{
      n = n+1;
      printf("\nITERATION %d \t",n);
      for(int j=0;j<nb_var;j++){
        voisin[j] = X[j];
      }
      if (firstStep == 1) {
        //premier mouvement pour cet x solution
        mouvementGenerateur=1;
        firstStep = 0;
      }else{mouvementGenerateur=0;}
      bigGenerateur = mouvementKPExchange(voisin,nb_var,K,P,bigGenerateur,mouvementGenerateur);
      if ( bigGenerateur[0]->contenu== 1) {
        if (valideVoisin(A,voisin,nb_cte,nb_var) == 1) {       //On teste si le mouvement obtenu est valide
          if(*z > evaluer_fonction_economique(voisin,C,nb_var)){
            printf("  --->  Better movement\t");
            for(int j=0;j<nb_var;j++){
              X[j] = voisin[j];
            }
            *z = evaluer_fonction_economique(X,C,nb_var);
            printf("\tZ = %d \n",evaluer_fonction_economique(voisin,C,nb_var));
            listes impasse;
            for (int i = 0; i < 3; i++) {
              while (bigGenerateur[i]!=NULL) {
                impasse = bigGenerateur[i];
                bigGenerateur[i]=bigGenerateur[i]->next;
                free(impasse);
              }
            }
            firstStep = 1;
          }
          else {
            printf("  ---> not a better movement\tZ = %d",evaluer_fonction_economique(voisin,C,nb_var));
            if (evaluer_fonction_economique(voisin,C,nb_var) > *pire_solution) {
            *pire_solution = evaluer_fonction_economique(voisin,C,nb_var);
            }
          }
        }
        else{
          printf("not a solution\n");
        }
      }
      else{
        printf("NO MORE POSSIBLE MOVEMENT %d-%d EXCHANGE\n",K,P);
        break;
      }
    } while(n<iter);
  free(voisin);
  listes impasse;
  for (int i = 0; i < 3; i++) {
    while (bigGenerateur[i]!=NULL) {
      impasse = bigGenerateur[i];
      bigGenerateur[i]=bigGenerateur[i]->next;
      free(impasse);
    }
  }
  free(bigGenerateur[0]);
  free(bigGenerateur[1]);
  free(bigGenerateur[2]);
  free(bigGenerateur);
}
