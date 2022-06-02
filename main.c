#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sommet.h"
void readFile(FILE* f,int T[], int q[],int size,int** dist){
  for(int i=0;i<size;i++){
    int lecture;
    fscanf(f,"%d",&lecture);
    q[i]=lecture;
  }
  for(int i=0;i<size+1;i++){
    for(int j=0;j<size+1;j++){
      fscanf(f,"%d",&dist[i][j]);
    }
  }
}

int valeurMinLigne(int* ligne, int taille, bool mark[]){
  int idx=1;
  while(idx<taille+1 && (mark[idx]==true || ligne[idx]==0)){
    idx++;
  }
  int idxPremierNonMarque=idx;
  int min;
  int res=idxPremierNonMarque;
  for(int i=idxPremierNonMarque;i<taille+1;i++){
    if((min==0 && mark[i]==false) || (ligne[i]!=0 && min>ligne[i] && mark[i]==false)){
      min=ligne[i];
      res=i;
    }
  }
  return res;
}

void tourGeant(int T[], int q[],int N, int** dist){
  bool mark[N];
  for(int k=0;k<N;k++){
    mark[k]=false;
  }
  int i=0;
  for(int j=0;j<N;j++){
    if(mark[j]==false){
      i=valeurMinLigne(dist[i],N,mark);
      T[j]=i;
      mark[j]=true;
      printf("VALEUR %d\n",i);
      for(int k=0;k<N;k++){
	printf("%d\t",mark[k]);
      }
      printf("\n");
    }
  }
}

void split(struct sommet H[],int T[],int q[] ,int N, int Q,int **dist){
  for(int i=0;i<N;i++){
    int j=i;
    int load=0;
    int cost=0;
    while(j<N && load <Q){
      load+=q[T[j]];
      if(i==j){
	cost=dist[0][T[i]]+dist[T[i]][0];
      }else{
	cost-=dist[T[j]-1][0]+dist[T[j]-1][T[j]]+dist[T[j]][0];
      }
      if(load<=Q){
	printf("i= %d et j=%d\n",i,j+1);
	H[i].num=i;
	ajout_en_queue_arete(T[j],cost,H[i].liste);
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
  int* T=(int*)(malloc(nbSommets*sizeof(int)));
  int* q=(int*)(malloc(nbSommets*sizeof(int)));
  int** dist=(int**)(malloc((nbSommets+1)*sizeof(int*)));
  for(int i=0;i<nbSommets+1;i++){
    dist[i]=(int*)(malloc((nbSommets+1)*sizeof(int)));
  }
  readFile(f,T,q,nbSommets,dist);
  for(int i=0;i<nbSommets;i++){
    printf("Num: %d, Qte: %d\n",T[i],q[i]);
  }
  for(int i=0;i<nbSommets+1;i++){
    for(int j=0;j<nbSommets+1;j++){
      printf("%d\t",dist[i][j]);
    }
    printf("\n");
  }

  struct sommet* H=(struct sommet*)(malloc((nbSommets+1)*sizeof(struct sommet)));
  for(int i=0; i<nbSommets+1; i++){
    init_sommet(&H[i]);
  }
  tourGeant(T,q,nbSommets,dist);
  for(int i=0;i<nbSommets;i++){
    printf("Sommet %d\t",T[i]);
  }
  printf("\n");
  
  split(H,T,q,nbSommets,capaciteMax,dist);
  for(int i=0;i<nbSommets;i++){
    printf("Sommet %d\t",H[i].num);
    affiche_liste_arete(H[i].liste);
  }
  
  return 0;
}
