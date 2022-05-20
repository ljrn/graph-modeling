//sommet.h

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

struct sommet{
  int num;
  struct liste_arete* liste;
};

extern void ajout_en_queue_arete(int idx, int cost, struct sommet* s);
extern struct sommet* getSommet(struct sommet[],struct liste_arete* L,int k);
