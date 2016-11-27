#ifndef LISTE_H
#define LISTE_H
//declaration de type
typedef struct element{
  int contenu;
  struct element *next;
}element;
typedef element* listes;
listes ajoutListe(listes maListe, int valeur);
int rechecherListe(listes maListe, int valeur);
int minimumListe(listes maListe);
//void supprimerListe(listes maListe, int a);
int sizeListe(listes maListe);
int recupererPosition(listes maListe,int min);
void removeListe(listes maListe);
listes removeElementListe(listes generateurK,int position);
//void meilleur_voisin(listes ensembleVoisin,int *C,int *solution,int nb_var);
#endif
