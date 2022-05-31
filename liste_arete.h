//liste_arete.h

struct maillon_arete{
  int poids;
  int idxSommet;
  struct maillon_arete* suivant;
};

#define NIL (struct maillon_arete*)0

struct liste_arete{
  int nbelem;
  struct maillon_arete* tete;
};

extern void init_liste_arete(struct liste_arete*);
extern void ajout_en_queue_arete(int idx, int cost, struct liste_arete* L);
extern void clear_liste_arete(struct liste_arete*);
