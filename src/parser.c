/* ==================================================================================================
   Format des instances :
     number of rows (m), number of columns (n)
     the cost of each column c(j),j=1,...,n
     for each row i (i=1,...,m): the number of columns which cover
     row i followed by a list of the columns which cover row i

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "structuresDonnees.h"
#include "glouton.h"
#include "grasp.h"
#include "recuit.h"
#include "reactiveGrasp.h"

/*------------------------------------------------------------
#  Prototype
--------------------------------------------------------------
*/
void liberation (int **X,int n);

/*------------------------------------------------------------
#  Main
--------------------------------------------------------------
*/
int main(int argc, char const *argv[]) {

  int nb_var = 0;
  int nb_cte = 0;
  int iteration_grasp = 100;
  int iteration_recuit = 50;

  FILE* fichier = NULL;
  if (argc < 2) {
    exit(1);
  }
  //srand(0); //
  srand(time(NULL));
  //sinon aucun problème avec les paramètres
  for (int indice = 1; indice < argc; indice++) {
    int **Matrice;
    int *C;
    int *X;
    int *Z ;
    int tmp;
    // Ouverture du fichier d'entree/sortie
    //La taille du chemin vaut au plus 250 caractères
    char chemin[250] = "../instances/";
    printf("%s\n",argv[indice]);
    strcat(chemin, argv[indice]);
    printf("%s\n",chemin);
    strcat(chemin, ".txt");
    fichier   = fopen(chemin,"r");
    printf("\n =========================== INSTANCES  %s =========================== \n",chemin);
    // lecture nombre de contraintes
    fscanf(fichier, "%d", &nb_cte);
    printf("le nbre de contraintes %d\n",nb_cte);
    // lecture nombre de variables
    fscanf(fichier, "%d", &nb_var);
    printf("le nbre de variables %d\n",nb_var);

      //allocations de memoires pour nos tableaux
    C = malloc(nb_var * sizeof(int));
    X = malloc(nb_var * sizeof(int));
    Z = malloc(sizeof(int));
    Matrice = malloc(nb_cte * sizeof(* Matrice));
    if(C == NULL || X == NULL || Matrice == NULL || Z == NULL){
      printf("ERREUR ALLOCATION\n");
      exit(1);
    }
    for(int i=0 ; i < nb_cte ; i++){
      Matrice[i] = malloc(nb_var * sizeof(**Matrice) );
      if(Matrice[i] == NULL){
        printf("ERREUR ALLOCATION\n");
        exit(1);
      }
    }

    initialiser_matrice(Matrice,nb_cte,nb_var,0);
    initialiser_tab_int(X,nb_var,0);
    initialiser_tab_int(C,nb_var,0);
    initialiser_tab_int(Z,1,1000000);

    //Tout est alloué donc remplissage de tableau
    /* lecture vecteur des couts */
    for(int i = 0; i< nb_var;++i){
          fscanf(fichier, "%d", &C[i]);
        }
    /* lecture matrice des contraintes format OR-LIB */
    for (int i=0; i< nb_cte; i++){
          // nbre elements non nuls sur la contrainte i
          fscanf(fichier,"%d",&tmp);
          for(int j = 0; j<tmp;j++){
            fscanf(fichier,"%d",&indice);
            Matrice[i][indice-1] = 1;
          }
        }

        fclose(fichier);
        //         =============================  DEBUT EXECUTION PROGRAMME =====================================


        //AFFICHAGE
        /*
        printf("\nAffichage de C\n");
        affiche_tab_int(C, nb_var);
        printf("\n");
        printf("\nAffichage de X\n");
        affiche_tab_int(X, nb_var);
        printf("\n");
        printf("\nAffichage de Matrice\n");
        affiche_matrice(Matrice,nb_cte,nb_var);
        printf("\nAffichage de Z = ");
        affiche_tab_int(Z,1);
        printf("\n");
        */

        //methodeGlouton(Matrice,X,C,Z,nb_cte,nb_var);
        printf("Z = %d\n",*Z);
        //methodeGrasp(Matrice,X,C,Z,nb_cte,nb_var,iteration_grasp);
        printf("\n\n");
        reactiveGrasp(Matrice,X,Z,C,nb_cte,nb_var);
        printf("\n\n");

        /**
        Donnees recuit
        */
        float T = 100;
        float alpha = 0.70;
        int L = 3;

        //recuit(Matrice,X,C,nb_cte,nb_var,iteration_recuit,Z,T,L,alpha);
        printf("\n");

        affiche_tab_int(X,nb_var);
        printf("Z = %d\n",*Z);


        //Liberations des espaces alloués
        free(C);
        free(X);
        free(Z);
        liberation(Matrice,nb_cte);

  }
    return 0;
}

// Fonction liberation
void liberation (int **ptr,int n){
    for (int  i = 0; i < n; i++) {
          free(ptr[i]);
    }
     free (ptr);
     //*ptr = NULL;
}
