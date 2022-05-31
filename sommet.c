#include <stdlib.h>
#include <stdio.h>
#include "sommet.h"

void init_sommet(struct sommet S){
  S.num=0;
  S.quantiteALivrer=0;
  S.liste=(struct liste_arete*)(malloc(sizeof(struct liste_arete)));
  init_liste_arete(S.liste);
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

void clear_sommet(struct sommet* S){
  clear_liste_arete(S->liste);
}
