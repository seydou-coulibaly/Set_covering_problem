#include <stdio.h>
#include <stdlib.h>
#include "structuresDonnees.h"
#include "mouvement.h"

//fonction qui va nous aider à verifier la validiter d'un voisin en fournissant un tableau vecteur
void extraireCoefficient(int **A, int *vecteur, int ligne, int colonne){
  int somme;
  for(int i=0;i<ligne;i++){
    somme = 0;
    for(int j=0;j<colonne;j++){
      somme = somme + A[i][j];
    }
    vecteur[i] = somme;
  }
}
void coefficient(int *coef,int nb_var,int *contraintes, int nb_cte, int **A){
  for (int j=0; j<nb_var; ++j){
    int i = 0;
    while (i< nb_cte) {
      if(contraintes[i] == 1){
        coef[j] = coef[j] + A[i][j];
      }
      i++;
    }
  }
}
int valideVoisin(int **A, int * voisin,int ligne, int colonne){
  int* vecteur = NULL;
  int test,verif;
  vecteur = malloc(ligne * sizeof(int));
  if (vecteur == NULL) // On vérifie si l'allocation a marché ou non
    {
      printf("Insuffisance de memoire pour allouer une table\n");
      exit(0); // On arrête tout
    }
  extraireCoefficient(A,vecteur,ligne,colonne);
  for(int i=0;i<ligne;i++){
    test = 0;
    verif = 0;
    for(int j=0;j<colonne;j++){
      if(A[i][j]==1 && voisin[j]==0){test++;}
    }
    verif = vecteur[i]-test;
    if(verif<1){
      free(vecteur);
      return 0;
    }
  }
  free(vecteur);
  return 1;
}
//mouvementKPExchange
listes* mouvementKPExchange(int* tmp, int colonne,int K,int P,listes* bigGenerateur,int new_solution){
      //afficheTableau(tmp,colonne);
      int generer=0,position=0,nbrK=0,nbrP=0;
      listes retour = NULL;
      nbrK = nombreDeK(tmp,colonne,1);
      nbrP = nombreDeK(tmp,colonne,0);
      if (nbrK >= K && nbrP >= P) {
        //remplir generateur k et generateur p
        if (new_solution == 1) {
          for (int i = 0; i < colonne; i++) {
            if (tmp[i]==1) {
              bigGenerateur[1] =  ajoutListe(bigGenerateur[1],i);
            }
          }
          for (int i = 0; i < colonne; i++) {
            if (tmp[i]==0) {
              bigGenerateur[2] =  ajoutListe(bigGenerateur[2],i);
            }
          }
        }
        if (sizeListe(bigGenerateur[1])!=0 && sizeListe(bigGenerateur[2])!=0) {
          for(int i=0;i<K;i++){
              do {
                if (sizeListe(bigGenerateur[1])==1) {
                  position = 1;
                }else{
                  position = rand()% (sizeListe(bigGenerateur[1])-1)+1;
                }
                generer = recupererPosition(bigGenerateur[1],position);
              } while(tmp[generer] != 1);
            tmp[generer] = 0;
            bigGenerateur[1] = removeElementListe(bigGenerateur[1],position);
          }
          for(int i=0;i<P;i++){
            do {
              if (sizeListe(bigGenerateur[2])==1) {
                position = 1;
              }else{
                position = rand()% (sizeListe(bigGenerateur[2])-1)+1;
              }
              generer = recupererPosition(bigGenerateur[2],position);
            } while(tmp[generer] != 0);
            tmp[generer] = 1;
            bigGenerateur[2] = removeElementListe(bigGenerateur[2],position);
          }
          retour = ajoutListe(retour,1);
          bigGenerateur[0]=retour;
          return bigGenerateur;
        }
        else{
          retour = ajoutListe(retour,0);
          bigGenerateur[0]=retour;
          listes impasse;
          for (int i = 1; i < 3; i++) {
            while (bigGenerateur[i]!=NULL) {
              impasse = bigGenerateur[i];
              bigGenerateur[i]=bigGenerateur[i]->next;
              free(impasse);
            }
          }
          return bigGenerateur;
        }

      }
      else{
        retour = ajoutListe(retour,0);
        bigGenerateur[0]=retour;
        listes impasse;
        for (int i = 1; i < 3; i++) {
          while (bigGenerateur[i]!=NULL) {
            impasse = bigGenerateur[i];
            bigGenerateur[i]=bigGenerateur[i]->next;
            free(impasse);
          }
        }
        return bigGenerateur;
      }
}
int nombreDeK(int *A, int colonne,int k){
  int n = 0;
  for(int i=0;i<colonne;i++){
      if (A[i]==k) {
        n++;
      }
  }
  return n;
}
//mouvementKPExchange
int* exchange0_1(int* solution,int **matrice,int* C,int ligne,int colonne,int * pire_solution){
  int nbrK=0,nbrP=0,var_test=0;
  int *retour = NULL;
  int *courante = NULL;
  retour = malloc(colonne * sizeof(int));
  courante = malloc(colonne * sizeof(int));
  if (retour == NULL || courante == NULL){  // On vérifie si l'allocation a marché ou non
    printf("Insuffisance de memoire pour allouer une table\n");
    exit(0); // On arrête tout
  }
  for(int j=0;j<colonne;j++){
    retour[j] = solution[j];
    courante[j] = solution[j];
  }
  nbrK = nombreDeK(solution,colonne,1);
  nbrP = nombreDeK(solution,colonne,0);
  if (nbrK >= 0 && nbrP >= 1) {
    //fixer une variable
    for (int i = 0; i < colonne; i++) {
      if (solution[i] == 0) {
        for (int j = 0; j < colonne; j++) {
          if (solution[j] == 1) {
            //pour k rien à faire
            //pour p qui vaut 1 alors une variable est mis à 0
            courante[j] = 0;
            var_test = valideVoisin(matrice,courante,ligne,colonne);
            if (var_test == 1) {
              //solution realisable alors tester si c'est le meilleur
              if (evaluer_fonction_economique(courante,C,ligne) < evaluer_fonction_economique(retour,C,ligne)) {
                for(int k=0;k<colonne;k++){
                  retour[k] = courante[k];
                }
              if (evaluer_fonction_economique(courante,C,ligne) > *pire_solution) {
                *pire_solution = evaluer_fonction_economique(courante,C,ligne);
              }
                // recommencer avec le même vecteur x
                for(int k=0;k<colonne;k++){
                  courante[k] = solution[k];
                }
              }
            }
          }
          //sinon rien à traiter
        }
      }
    }
    return retour;
  }
  else{
    printf("Mission Impossible\n");
    return retour;
  }
}
