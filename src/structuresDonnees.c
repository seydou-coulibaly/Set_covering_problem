#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structuresDonnees.h"
void initialiser_tab_int(int* a,int nb_var,int valeur){
    for (int i=0; i<nb_var; i++){
      a[i] = valeur;
    }
  }
void initialiser_matrice(int** a,int nb_cte, int nb_var,int valeur){
    for (int i=0; i<nb_cte; i++){
      for (int j=0; j<nb_var; j++){
        a[i][j] = valeur;
    }
  }
}
void initialiser_tab_float(float* a,int nb_var,int valeur){
    for (int i=0; i<nb_var; i++){
      a[i] = valeur;
    }
  }
int table_nulle_test(int* matrice, int ligne){
  int n = 0;
  for (int i=0; i<ligne; i++){
      if(matrice[i]== 0){n++ ;}
  }
  if(n == ligne){return 1;}
  else{return 0;}
}
int minimum(float* U, int colonne){     //A VOIR
  int indice = 0;
  U[indice] = U[0];
  for (int j=1; j<colonne; j++){
    if(U[j] < U[indice]){U[indice] = U[j];}
  }
  return indice;
}
int maximum(float* U, int colonne){     //A VOIR
  int indice = 0;
  U[indice] = U[0];
  for (int j=1; j<colonne; j++){
    if(U[j] > U[indice]){U[indice] = U[j];indice = j;}
  }
  return indice;
}
int maximum_element(int* U, int colonne){
  int indice = 0;
  U[indice] = U[0];
  for (int j=1; j<colonne; j++){
    if(U[j] > U[indice]){indice = j;}
  }
  return U[indice];
}
int minimum_element(int* U, int colonne){
  int indice = 0;
  for (int j=1; j<colonne; j++){
    if(U[j] < U[indice]){indice = j;}
  }
  return U[indice];
}
int minimum_utilite(float* U, int colonne,int* X){
  int indice = 0;
  U[indice] = U[0];
  for (int j=1; j<colonne; j++){
    if(U[j] < U[indice] && X[j]!= 1){indice = j;}
  }
  return indice;
}
int maximum_utilite(float* U, int colonne,int* X){
  int indice = 0;
  U[indice] = U[0];
  for (int j=1; j<colonne; j++){
    if(U[j] > U[indice] && X[j]!= 1){indice = j;}
  }
  return indice;
}
void affiche_matrice(int **A,int ligne,int colonne){
  for(int j=0;j<ligne;j++){
    printf("    ");
    for(int i=0;i<colonne;i++){
        printf("%4d",A[j][i] );
    }
    	printf("\n");
  }
    printf("\n\n");
}
void affiche_tab_int(int *A, int colonne){
  for(int i=0;i<colonne;i++){
      printf("%4d", A[i]);
  }
  printf("\t\t");
}
void affiche_tab_float(float *A, int colonne){
  for(int i=0;i<colonne;i++){
      printf("%4f\t", A[i]);
  }
  printf("\n\n");
}
//fonction evaluant une solution donné X sous les cout C
int evaluer_fonction_economique(int * X, int * C, int taille){
  int somme = 0;
    for(int i=0;i<taille;i++){
      somme = somme + X[i] * C[i];
    }
    return somme;
}
//egaliteTableau
int egalite_tableau(int *tab,int *voisin,int colonne){
  int n = 0, retour = 0;
  for(int j=0;j<colonne;j++){
    if(tab[j] == voisin[j]){
      n++;
    }
  }
  if(n!=colonne){
    retour = 0;
  }
  else{
    retour = 1;
  }
  return retour;
}
//calcule de la limite
float limite(float* utilite,int colonne,float alpha,int* X){
int max = 0, min = 0;
max = maximum_utilite(utilite,colonne,X);
min = minimum_utilite(utilite,colonne,X);
return (utilite[min] + alpha * (utilite[max] - utilite[min]));
}
