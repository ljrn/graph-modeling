#include <stdio.h>
#include <stdlib.h>
#include "sommet.h"
void readFile(FILE* f,struct sommet sommets[],int size,int** dist){
  for(int i=0;i<size;i++){
    int lecture;
    fscanf(f,"%d",&lecture);
    sommets[i].quantiteALivrer=lecture;
    sommets[i].num=i;
  }
  for(int i=0;i<size+1;i++){
    for(int j=0;j<size+1;j++){
      fscanf(f,"%d",&dist[i][j]);
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
  struct sommet* sommets=(struct sommet*)(malloc(nbSommets*sizeof(struct sommet)));
  for(int i=0; i<nbSommets; i++){
    init_sommet(sommets[i]);
  }
  int** dist=(int**)(malloc((nbSommets+1)*sizeof(int*)));
  for(int i=0;i<nbSommets+1;i++){
    dist[i]=(int*)(malloc((nbSommets+1)*sizeof(int)));
  }
  readFile(f,sommets,nbSommets,dist);
  for(int i=0;i<nbSommets;i++){
    printf("Num: %d, Qte: %d\n",sommets[i].num,sommets[i].quantiteALivrer);
  }
  for(int i=0;i<nbSommets+1;i++){
    for(int j=0;j<nbSommets+1;j++){
      printf("%d\t",dist[i][j]);
    }
    printf("\n");
  }
  return 0;
}
