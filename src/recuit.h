#ifndef RECUIT_H
#define RECUIT_H
float probabilite_acceptation(float delta);
void recuit(int **A,int* X,int* C,int nb_cte, int nb_var,int iteration,int *z_solution);
#endif
