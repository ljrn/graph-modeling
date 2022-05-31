//sommet.h
#include "liste_arete.h"
struct sommet{
  int num;
  int quantiteALivrer;
  struct liste_arete* liste;
};

extern void init_sommet(struct sommet*);
extern struct sommet* getSommet(struct sommet[],struct liste_arete* L,int k);
extern void clear_sommet(struct sommet*);
