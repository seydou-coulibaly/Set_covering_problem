#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
//ajout dans une liste
listes ajoutListe(listes maListe, int a){
  listes nouvelElement = malloc(sizeof(element));
  nouvelElement->contenu = a;
  nouvelElement->next = NULL;

  if(maListe == NULL){
      //maListe = nouvelElement;
      return nouvelElement;
  }
  else{
      listes temp = maListe;
      while(temp->next != NULL)
      {
          temp = temp->next;
      }
      temp->next = nouvelElement;
      return maListe;
  }
}
void removeListe(listes maListe){
  if(maListe != NULL){
      listes temp ;
      while(maListe != NULL)
      {
        temp = maListe;
        maListe = maListe->next;
        free(temp);
    }
}
}
listes removeElementListe(listes maListe,int position){
  listes retour=NULL ;
  int n=2;
  if (maListe!=NULL) {
      listes temp ;
      listes temp1 ;
      temp = maListe;
      if (position == 1) {
        maListe = maListe->next;
        free(temp);
        retour =  maListe;
      }
      else if (position == sizeListe(maListe)) {
        while ((temp->next)->next != NULL) {
          temp = temp->next;
        }
        temp1 = temp->next;
        temp->next = NULL;
        free(temp1);
        retour =  maListe;
      }
      else{
        while (n!=position) {
          n++;
          temp = temp->next;
        }
        temp1 = temp->next;
        temp->next = temp1->next;
        free(temp1);
        retour =  maListe;
      }
  }
  return retour;
}
int rechecherListe(listes maListe, int a){
  listes temp = maListe;
  if (maListe == NULL) {
    return 0;
  }
  else{
    while(temp->next != NULL)
    {
      if ((temp->contenu) == a) {
        return 1;
      }
      temp = temp->next;
    }
  }
  return 0;
}
//minimum d'une liste, mais on suppose qu'elle n'est pas vide
int minimumListe(listes maListe){
  listes temp = maListe->next;
  int min = maListe->contenu;
    while(temp->next != NULL)
    {
      if ((temp->contenu) < min) {
        min = temp->contenu;
      }
      temp = temp->next;
    }
  return min;
}
/*
void supprimerListe(listes maListe, int a){
//TODO
}
*/
int sizeListe(listes maListe){            //taille de la liste
  int n = 1;
  listes tmp = maListe;
  if (tmp == NULL) {
    return 0;
  }else{
    while(tmp->next != NULL)
    {
        tmp = tmp->next;
        n++;
    }
    return n;
  }
}
//on suppose min different de 0
//recupere l'element dont la position est fournie
int recupererPosition(listes maListe,int min){
  int n = 1;
  listes temp = maListe;
  if (temp == NULL) {
    exit(0);
  }
  else{
    if (min <= sizeListe(maListe)) {
      while(n != min)
      {
        temp = temp->next;
        n++;
      }
    }
  }
return (temp->contenu);
}
