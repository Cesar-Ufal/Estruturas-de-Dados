#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define true 1
#define false 0
typedef int bool;
typedef int TIPOPESO;

typedef struct grafo{
  int vertice;
  int arestas;
  TIPOPESO** adj;
  //outros campos nescessários
} GRAFO;