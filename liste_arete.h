//liste_arete.h

struct maillon_arete{
  double poids;
  int idxSommet;
  struct maillon_arete* suivant;
};

#define NIL (struct maillon_arete*)0

struct liste_arete{
  int nbelem;
  struct maillon_arete* tete;
};

extern void init_liste_arete(struct liste_arete*);
extern void ajout_en_queue_arete(int idx, double cost, struct liste_arete* L);
extern void affiche_liste_arete(struct liste_arete*);
extern struct maillon_arete* minimum(struct liste_arete*);
extern void clear_liste_arete(struct liste_arete*);
