#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include "sommet.h"
void readFile(FILE* f,int T[], int q[],int size,double** dist){
  for(int i=1;i<size+1;i++){
    int lecture;
    fscanf(f,"%d",&lecture);
    q[i]=lecture;
  }
  for(int i=0;i<size+1;i++){
    for(int j=0;j<size+1;j++){
      fscanf(f,"%lf",&dist[i][j]);
    }
  }
}

int valeurMinLigne(double* ligne, int taille, bool mark[], int indice){
  double tmp=-1;
  int res;
  for(int i=1;i<taille+1;i++){
    if(mark[i]==false && i!=indice){
      if(tmp==-1){
	tmp=ligne[i];
	res=i;
      }else if(ligne[i]<tmp){
	res=i;
	tmp=ligne[i];
      }
    }
  }
  return res;
}

void tourGeant(int T[], int q[],int N, double** dist, int debut){
  bool* mark=(bool*)(malloc((N+1)*sizeof(bool)));
  for(int k=0;k<N+1;k++){
    mark[k]=false;
  }
  mark[0]=true;
  int i=debut;
  int tmp;
  mark[debut]=true;
  T[1]=debut;
  for(int j=2;j<N+1;j++){
    tmp=valeurMinLigne(dist[i],N,mark,i);
    T[j]=tmp;
    i=tmp;
    mark[i]=true;
  }
  for (int i=0;i<N+1; i++){
    if(mark[i] == false){
      T[N]=i+1;
    }
  }
}

void split(struct sommet H[],int T[],int q[] ,int N, int Q,double **dist){
  double cost;
  for(int i=1;i<N+1;i++){
    int j=i;
    int load=0;
    while(j<=N && load <Q){
      load+=q[T[j]];
      if(i==j){
	cost=dist[0][T[i]]+dist[T[i]][0];
      }else{
	cost=cost-dist[T[j-1]][0]+dist[T[j-1]][T[j]]+dist[T[j]][0];
      }
      if(load<=Q){
	printf("i= %d et j=%d\n",i-1,j);
	H[i-1].num=i-1;
	ajout_en_queue_arete(j,cost,H[i-1].liste);
      }
      j++;
    }
  }
  H[N].num=N;
}

double dijkstra(int N, struct sommet H[]){
  int* Pere=(int*)(malloc((N+1)*sizeof(int)));
  int* Mark=(int*)(malloc((N+1)*sizeof(int)));
  double* pi=(double*)(malloc((N+1)*sizeof(double)));;
  for(int i=0;i<N+1;i++){
    Pere[i]=-1;
    pi[i]=DBL_MAX;
    Mark[i]=0;
  }
  Mark[0]=0;
  pi[0]=0.0;
  Pere[0]=0;
  bool fini=false;
  while(!fini){
    fini=true;
    double min=DBL_MAX;
    int x=-1;
    for(int i=0;i<N+1;i++){
      //printf("Mark[%d]= %d, pi[%d]=%lf\n",i,Mark[i],i,pi[i]);
      if(Mark[i]==0 && pi[i]<=min){
	min=pi[i];
	x=i;
      }
    }
    if(x>=0){
      //printf("Sommet choisi: %d\n",x);
      //x=idxFalse;
      fini=false;
      Mark[x]=1;
      struct liste_arete* listeX=H[x].liste;
      if(listeX->tete!=NIL){
	struct maillon_arete* courant=listeX->tete;
	while(courant!=NIL){
	  if(pi[courant->idxSommet]>(pi[x]+courant->poids)){
	    pi[courant->idxSommet]=pi[x]+courant->poids;
	    Pere[courant->idxSommet]=x;
	  }
	  courant=courant->suivant;
	}
      }
    }
  }
  for(int i=0;i<N+1;i++){
    printf("%lf\n",pi[i]);
  }
  return pi[N];
}

int main(int argc, char** argv){
  FILE* f;
  f=fopen(argv[1], "r");
  int nbSommets;
  int capaciteMax;
  fscanf(f,"%d",&nbSommets);
  fscanf(f,"%d",&capaciteMax);
  printf("N= %d, Q=%d\n",nbSommets,capaciteMax);
  int* T=(int*)(malloc((nbSommets+1)*sizeof(int)));
  int* q=(int*)(malloc((nbSommets+1)*sizeof(int)));
  double** dist=(double**)(malloc((nbSommets+1)*sizeof(int*)));
  for(int i=0;i<nbSommets+1;i++){
    dist[i]=(double*)(malloc((nbSommets+1)*sizeof(double)));
  }
  readFile(f,T,q,nbSommets,dist);
  for(int i=0;i<nbSommets;i++){
    printf("Num: %d, Qte: %d\n",T[i],q[i]);
  }
  for(int i=0;i<nbSommets+1;i++){
    for(int j=0;j<nbSommets+1;j++){
      printf("%lf\t",dist[i][j]);
    }
    printf("\n");
  }

  struct sommet* H=(struct sommet*)(malloc((nbSommets+1)*sizeof(struct sommet)));
  for(int i=0; i<nbSommets+1; i++){
    init_sommet(&H[i]);
  }
  int debut;
  printf("Par quel client voulez-vous commencer ?\n");
  scanf("%d",&debut);
  tourGeant(T,q,nbSommets,dist, debut);
  for(int i=0;i<nbSommets+1;i++){
    printf("Sommet %d\t",T[i]);
  }
  printf("\n");
  
  split(H,T,q,nbSommets,capaciteMax,dist);
  for(int i=0;i<nbSommets+1;i++){
    printf("Sommet %d\t",H[i].num);
    affiche_liste_arete(H[i].liste);
  }

  printf("\nLe coût minimal est de %lf\n",dijkstra(nbSommets,H));
  
  return 0;
}
