#ifndef TABLEAU_H
#define TABLEAU_H

/*
typedef struct liste
{
    int contenu[MAX_VAR];
    struct liste *next;
}liste;
typedef liste* listes;
*/
int table_nulle_test(int* matrice, int ligne);
int minimum(float* U, int colonne);
int maximum(float* U, int colonne);

int maximum_element(int* U, int colonne);
int minimum_element(int* U, int colonne);

int minimum_utilite(float* U, int colonne,int* X);
int maximum_utilite(float* U, int colonne,int* X);

void affiche_matrice(int **A,int ligne,int colonne);
void affiche_tab_int(int *A, int colonne);
void affiche_tab_float(float *A, int colonne);

void initialiser_tab_int(int*a,int nb_var,int valeur);
void initialiser_tab_float(float* a,int nb_var,int valeur);
void initialiser_matrice(int** a,int nb_cte, int nb_var,int valeur);

int evaluer_fonction_economique(int * X, int * C, int taille);
int egalite_tableau(int *tab,int *voisin,int colonne);

float limite(float* utilite,int colonne,float alpha,int* X);

#endif
