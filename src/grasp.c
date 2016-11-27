#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structuresDonnees.h"
#include "simplelocalSearh.h"
#include "graspConstruction.h"
#include "grasp.h"
void methodeGrasp(int **A,int* X,int* C,int *z_solution,int nb_cte, int nb_var,int iteration){
	int choixMenu;
	float alpha;
	int generer = 0;
  int *pire_solution = NULL;
	pire_solution = malloc(sizeof(int));
  *pire_solution = 0;
  printf("******************************** MENU GRASP ********************************\n\n");
  printf("1.	Begin GRASP with a knwon parameter alpha\n");
  printf("2.	Begin GRASP with a randomly parameter alpha betwen [0,1]\n");
  //printf("\nYour choice ? ");
  //scanf("%d", &choixMenu);
	choixMenu = 2;
  printf("\n");
  switch (choixMenu)
  	{
    	case 1:
      	printf("Type the value of parameter alpha!");
 	//			scanf("%f", &alpha);
      	break;
    	case 2:
				srand(time(NULL));
				generer = rand();
				alpha = (float)(generer%10)/10;
       	printf("A generate alpha is = %f\n", alpha);
       	break;
    	default:
				alpha = 0;
       	printf("Default case, alpha is %f\n",alpha);
       	break;
  }
	//alpha = 0;
  printf("\n\n");
	grasp(A,X,C,nb_cte,nb_var,alpha,iteration,z_solution,pire_solution);
	printf("Pire solution trouvé = %d\n", *pire_solution);
  free(pire_solution);
}
void grasp(int **A,int* X,int* C,int nb_cte, int nb_var,float alpha,int iteration,int *z_solution,int *pire_solution){
	int n=0;
	int iteration_descente_simple = 10;
	//int iteration_descente_profonde = 1;
	int * solution = NULL;
	int *z = NULL;
	z = malloc(sizeof(int));
	solution = malloc(nb_var * sizeof(int));
	if (solution == NULL || z == NULL) // On vérifie si l'allocation a marché ou non
		{
			printf("Insuffisance de memoire pour allouer une table de contraintes ou d'utilités\n");
			exit(1); // On arrête tout
		}
	do{
		n++;
		printf("============================================================\n");
		initialiser_tab_int(solution,nb_var,0);
		//parameter alpha in parameter
		printf("\n\t--->  CONSTRUCTION GRASP \n");
		graspConstruction(A,solution,C,nb_cte,nb_var,alpha);
		*z = evaluer_fonction_economique(solution, C,nb_var);
    if (*pire_solution < *z) {
      *pire_solution = *z;
    }
		printf("\n\t\t\t -----	Z = %d\n",*z);
		//afficheTableau(X,nb_var);
		printf("\n\t--->  LOCAL SEARCH ON GRASP \n");
		rechercheLocaleSimple(A,solution,C,z,nb_cte,nb_var,1,0,iteration_descente_simple,pire_solution);
		//descenteProfonde(A,X,C,z_solution,nb_cte,nb_var,1,0,iteration_descente_profonde,pire_solution);
		printf("\n\t\t\t +++++	Z = %d\n",*z);
		if(*z_solution>*z){
				for (int i = 0; i < nb_var; i++) {
					X[i] = solution[i];
				}
				*z_solution = evaluer_fonction_economique(X,C,nb_var);
		}
	}while(n<iteration);
	printf("\n\n\t\t\t \t\t GRASP FINAL SOLUTION	Z = %d\n\n",*z_solution);
	//printf("\n%f\n",alpha);
	free(z);
	free(solution);
}
