#ifndef RECUIT_H
#define RECUIT_H
float probabilite_acceptation(float delta, float temps);
void recuit(int **A,int* X,int* C,int nb_cte, int nb_var,int iteration,int *Z,float T, int L, float alpha);
void update(float *t_courant,int *k, int L,float alpha);
#endif
