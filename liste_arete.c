#include "liste_arete.h"
#include <stdlib.h>
#include <stdio.h>
//liste_arete.c

void init_liste_arete(struct liste_arete* L){
  L->nbelem=0;
  L->tete=NIL;
}
void ajout_en_queue_arete(int idx, int cost, struct liste_arete* L){
  struct maillon_arete* nvMaillon=(struct maillon_arete*)(malloc(sizeof(struct maillon_arete)));
  nvMaillon->poids=cost;
  nvMaillon->idxSommet=idx;
  nvMaillon->suivant=NIL;
  if(L->tete == NIL){
    L->tete=nvMaillon;
  }else{
    struct maillon_arete* courant=L->tete;
    while(courant->suivant!=NIL){
      courant=courant->suivant;
    }
    courant->suivant=nvMaillon;
  }
  L->nbelem++;
}

void affiche_liste_arete(struct liste_arete* L){
  if(L->tete != NIL){
    struct maillon_arete* courant=L->tete;
    while(courant!=NIL){
      printf("Vers: %d   Poids: %d\n",courant->idxSommet, courant->poids);
      courant=courant->suivant;
    }
  }
}

void clear_liste_arete(struct liste_arete* L){
  if(L->tete != NIL){
    if(L->tete->suivant!=NIL){
      struct maillon_arete* last=L->tete;
      struct maillon_arete* courant=last->suivant;
      while(last!=NIL){
	free(last);
	last=courant;
	if(courant->suivant!=NIL)
	  courant=courant->suivant;
      }
    }
  }
}
