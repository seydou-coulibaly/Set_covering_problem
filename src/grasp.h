#ifndef GRASP_H
#define GRASP_H
void grasp(int **A,int* X,int* C,int nb_cte, int nb_var,float alpha,int iteration,int *z_solution,int* pire_solution);
void methodeGrasp(int **A,int* X,int* C,int *z_solution,int nb_cte, int nb_var,int iteration);
#endif
