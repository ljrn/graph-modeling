#include <stdio.h>
#include <stdlib.h>
#include "sommet.h"
void readFile(FILE* f,struct sommet sommets[],int size,int** dist){
  for(int i=0;i<size;i++){
    int lecture;
    fscanf(f,"%d",&lecture);
    sommets[i].quantiteALivrer=lecture;
    sommets[i].num=i+1;
  }
  for(int i=0;i<size+1;i++){
    for(int j=0;j<size+1;j++){
      fscanf(f,"%d",&dist[i][j]);
    }
  }
}

int valeurMinLigne(int* ligne, int taille){
  int min=ligne[0];
  int res=0;
  for(int i=1;i<taille;i++){
    if((ligne[i]!=0 && min>ligne[i]) || min == 0){
      min=ligne[i];
      res=i;
    }
  }
  return res;
}

void tourGeant(struct sommet T[], int N, int** dist){
  int j=0;
  int i=valeurMinLigne(dist[T[0].num],N);
  while(j<N){
    struct sommet tmp=T[j];
    T[j]=T[i];
    T[i]=tmp;
    i=valeurMinLigne(dist[T[i].num],N);
    j++;
  }
}

void split(struct sommet H[],struct sommet T[],int N, int Q,int **dist){
  for(int i=0;i<N;i++){
    int j=i;
    int load=0;
    int cost=0;
    while(j<N && load <Q){
      load+=T[j].quantiteALivrer;
      if(i==j){
	cost=dist[0][T[i].num]+dist[T[i].num][0];
      }else{
	cost-=dist[T[j].num-1][0]+dist[T[j].num-1][T[j].num]+dist[T[j].num][0];
      }
      if(load<=Q){
	printf("i= %d et j=%d\n",i,j);
	ajout_en_queue_arete(j,cost,H[i].liste);
      }
      j++;
    }
  }
}

int main(int argc, char** argv){
  FILE* f;
  f=fopen(argv[1], "r");
  int nbSommets;
  int capaciteMax;
  fscanf(f,"%d",&nbSommets);
  fscanf(f,"%d",&capaciteMax);
  printf("N= %d, Q=%d\n",nbSommets,capaciteMax);
  struct sommet* T=(struct sommet*)(malloc(nbSommets*sizeof(struct sommet)));
  for(int i=0; i<nbSommets; i++){
    init_sommet(&T[i]);
  }
  int** dist=(int**)(malloc((nbSommets+1)*sizeof(int*)));
  for(int i=0;i<nbSommets+1;i++){
    dist[i]=(int*)(malloc((nbSommets+1)*sizeof(int)));
  }
  readFile(f,T,nbSommets,dist);
  for(int i=0;i<nbSommets;i++){
    printf("Num: %d, Qte: %d\n",T[i].num,T[i].quantiteALivrer);
  }
  for(int i=0;i<nbSommets+1;i++){
    for(int j=0;j<nbSommets+1;j++){
      printf("%d\t",dist[i][j]);
    }
    printf("\n");
  }

  struct sommet* H=(struct sommet*)(malloc(nbSommets*sizeof(struct sommet)));
  for(int i=0; i<nbSommets; i++){
    init_sommet(&H[i]);
  }
  tourGeant(T,nbSommets,dist);
  split(H,T,nbSommets,capaciteMax,dist);
  for(int i=0;i<nbSommets;i++){
    printf("Sommet %d\t",H[i].num);
    affiche_liste_arete(H[i].liste);
  }
  
  return 0;
}
