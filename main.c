#include <stdio.h>
#include "sommet.h"

int main(int argc, char** argv){
  FILE* f;
  f=fopen(argv[1], "r");
  int nbSommets;
  int capaciteMax;
  fscanf(f,"%d",&nbSommets);
  fscanf(f,"%d",&capaciteMax);
  printf("N= %d, Q=%d\n",nbSommets,capaciteMax);
  return 0;
}