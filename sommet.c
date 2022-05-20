#include <stdlib.h>
#include "sommet.h"

void ajout_en_queue_arete(int idx, int cost, struct sommet* s){
  struct maillon_arete* newArete=(struct maillon_arete*)malloc(sizeof(struct maillon_arete));
  newArete->poids=cost;
  newArete->idxSommet=idx;
  newArete->suivant=NIL;
  struct maillon_arete* current=s->liste->tete;
  while(current->suivant != NIL){
    current=current->suivant;
  }
  current->suivant=newArete;
}

struct sommet* getSommet(struct sommet H[],struct liste_arete* L, int k){
  struct maillon_arete* current=L->tete;
  while(current!=NIL && current->idxSommet!=k){
    current=current->suivant;
  }
  if(current!=NIL && current->idxSommet==k){
    return &H[k];
  }
  return (struct sommet*)0;
}
