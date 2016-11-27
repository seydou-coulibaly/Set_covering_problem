#ifndef MOUVEMENT_H
#define MOUVEMENT_H
#include "liste.h"
void extraireCoefficient(int **A, int * vecteur, int ligne, int colonne);
void coefficient(int *coef,int nb_var,int *contraintes, int nb_cte, int **A);
int valideVoisin(int **A, int * voisin,int ligne, int colonne);
listes* mouvementKPExchange(int* tmp, int colonne,int K,int P,listes* bigGenerateur,int new_solution);
void coefficient(int*coef,int nb_var,int *contraintes, int nb_cte, int **A);
int nombreDeK(int *A, int colonne,int k);
#endif
