#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define true 1
#define false 0
#define BRANCO 0
#define AMARELO 1
#define VERMELHO 2
#define INT_MAX 2147483647
typedef int bool;
typedef int TIPOPESO;
typedef int TIPOCHAVE;

typedef struct adjacent{
  int vertice;
  TIPOPESO peso;
  struct adjacent* prox;
} ADJACENCIA;

typedef struct vertice{
  TIPOCHAVE ch;
  ADJACENCIA *head;
}VERTICE;

typedef struct grafo{
  int vertices;
  int arestas;
  VERTICE *adj;
  //outros campos nescessários
} GRAFO;

typedef struct{
  TIPOCHAVE chave;
  int p;
  //outros campos nescessários
} REGISTRO;

typedef struct ELEMENTO{
  REGISTRO reg;
  struct ELEMENTO* next;
  //outros campos nescessários
} ELEMENTO;

typedef struct heapMinNode{
  int v;
  int d;
}HEAPMINNODE;

typedef struct heapMin{
  int size;
  int capacity;
  int *position;
  HEAPMINNODE** array;
}HEAPMIN;

typedef struct{
  ELEMENTO* topo;
  ELEMENTO* fim;
} FILA;

void inicializarLista(FILA* f){
  f->topo = NULL;
  f->fim = NULL;
}

int put(FILA* f, REGISTRO reg){
  ELEMENTO* aux = (ELEMENTO*) malloc(sizeof(ELEMENTO));
  aux->reg = reg;
  aux->next = NULL;
  if(f->topo == NULL){
    f->topo = aux;
  } else {
    f->fim->next = aux;
  }
  f->fim = aux;
  return 1;
}

int get(FILA* f, REGISTRO* reg){
  if(f->fim == NULL)
    return 0;
  ELEMENTO* aux = f->topo;
  *reg = aux->reg;
  f->topo = f->topo->next;
  free(aux);
  if(f->topo == NULL){
    f->fim = NULL;
  }
  return 1;
}

void reiniciarFila(FILA* f){
  ELEMENTO* aux = f->topo;
  while(aux != NULL){
    ELEMENTO* apagar = aux;
    aux = aux->next;
    free(apagar);
  }
  f->topo = NULL;
  f->fim = NULL;
  return;
}

void printNode(HEAPMIN* h, int i){
  if(i >= h->size)
    return;
  printf("v%d[%d](", h->array[i]->v, h->array[i]->d);
  printNode(h, (i<<1) + 1);
  printf(", ");
  printNode(h, (i<<1) + 2);
  printf(")");
}

void printHeap(HEAPMIN* h){
  printNode(h, 0);
  printf("\n");
}

HEAPMINNODE* createHeapMinNode(int v, int d){
  HEAPMINNODE* hmn = (HEAPMINNODE*) malloc(sizeof(HEAPMINNODE));
  hmn->v = v;
  hmn->d = d;
  return hmn;
}

HEAPMIN* createHeapMin(int n){
  HEAPMIN* hm = (HEAPMIN*) malloc(sizeof(HEAPMIN));
  hm->size = 0;
  hm->capacity = n;
  hm->position = (int*) malloc(n * sizeof(int));
  hm->array = (HEAPMINNODE**) malloc(n * sizeof(HEAPMINNODE*));
  return hm;
}

void swapMinHeapNode(HEAPMINNODE** a, HEAPMINNODE** b)
{
  HEAPMINNODE* temp = *a;
  *a = *b;
  *b = temp;
}

void heapfy(HEAPMIN* h, int v){
  int smallest = v;
  int left = (v<<1) + 1;
  int right = left + 1;
  if(left >= h->size)
    return;
  if(h->array[smallest]->d > h->array[left]->d)
    smallest = left;
  if(h->array[smallest]->d > h->array[right]->d)
    smallest = right;
  if(v != smallest){
    HEAPMINNODE* smallestNode = h->array[smallest];
    HEAPMINNODE* vNode = h->array[v];
    h->position[smallestNode->v] = v;
    h->position[vNode->v] = smallest;
    swapMinHeapNode(&h->array[smallest], &h->array[v]);
    heapfy(h, smallest);
  }
}

bool heapIsEmpty(HEAPMIN* h){
  return h->size == 0;
}

int pop(HEAPMIN* h){
  if(heapIsEmpty(h))
    return -1;
  HEAPMINNODE* min = h->array[0];
  HEAPMINNODE* last = h->array[h->size - 1];
  h->array[0] = last;
  h->position[min->v] = h->size - 1;
  h->position[last->v] = 0;
  h->size--;
  heapfy(h, 0);
  int v = min->v;
  free(min);
  return v;
}

bool isInHeapMin(HEAPMIN* h, int v){
  if(h->position[v] < h->size)
    return true;
  return false;
}

GRAFO *criaGrafo(int v){
  GRAFO* g = (GRAFO*) malloc(sizeof(GRAFO));
  g->vertices = v;
  g->arestas = 0;
  g->adj = (VERTICE*) malloc(v * sizeof(VERTICE));
  int i;
  for(i = 0; i < v; i++){
    g->adj[i].head = NULL;
    g->adj[i].ch = i;
  }
  return g;
}

ADJACENCIA* criarAdjacencia(int v, TIPOPESO peso){
  ADJACENCIA* a = (ADJACENCIA*) malloc(sizeof(ADJACENCIA));
  a->vertice = v;
  a->peso = peso;
  a->prox = NULL;
  return a;
}

bool criarAresta(GRAFO* g, int vi, int vf, TIPOPESO peso){
  if(g == NULL || vi < 0 || vf < 0 || vi >= g->vertices || vf >= g->vertices) return false;
  ADJACENCIA* novo = g->adj[vi].head;
  while(novo != NULL){
    if(novo->vertice == vf){
      novo->peso = peso;
      return true;
    }
    novo = novo->prox;
  }
  novo = criarAdjacencia(vf, peso);
  novo->prox = g->adj[vi].head;
  g->adj[vi].head = novo;
  g->arestas++;
  return true;
}

void imprimirGrafo(GRAFO *g){
  printf("Vértices: %d, Arestas: %d\n", g->vertices, g->arestas);
  int i;
  for(i = 0; i < g->vertices; i++){
    printf("v%d: ", i);
    ADJACENCIA* a = g->adj[i].head;
    while(a != NULL){
      printf("v%d(%d) ", a->vertice, a->peso);
      a = a->prox;
    }
    printf("\n");
  }
}

void visitaDFS(GRAFO* g, int i, int* cor){
  cor[i] = AMARELO;
  ADJACENCIA* a = g->adj[i].head;
  while(a != NULL){
    if(cor[a->vertice] == BRANCO)
      visitaDFS(g, a->vertice, cor);
    a = a->prox;
  }
  cor[i] = VERMELHO;
}

void DFS(GRAFO* g){
  int cor[g->vertices];
  int i;
  for(i = 0; i < g->vertices; i++){
    cor[i] = BRANCO;
  }
  for(i = 0; i < g->vertices; i++){
    if(cor[i] == BRANCO){
      visitaDFS(g, i, cor);
    }
  }
}

int visitaBFS(GRAFO* g, int i, bool* exp, TIPOCHAVE ch){
  FILA f;
  inicializarLista(&f);
  exp[i] = true;
  REGISTRO* u = (REGISTRO*) malloc(sizeof(REGISTRO));
  u->chave = i;
  u->p = 0;
  put(&f, *u);
  VERTICE* v;
  while(f.topo != NULL){
    get(&f, u);
    int p = u->p;
    if(u->chave == ch){
      reiniciarFila(&f);
      free(u);
      return p;
    }
    ADJACENCIA* a = g->adj[u->chave].head;
    while(a != NULL){
      if(!exp[a->vertice]){
        exp[a->vertice] = true;
        u->chave = a->vertice;
        u->p = p + 1;
        put(&f, *u);
      }
      a = a->prox;
    }
  }
  free(u);
  return -1;
}

bool BFS(GRAFO* g, TIPOCHAVE ch){
  bool exp[g->vertices];
  int i;
  for(i = 0; i < g->vertices; i++){
    exp[i] = false;
  }
  for(i = 0; i < g->vertices; i++){
    if(exp[i] == false){
      if(visitaBFS(g, i, exp, ch) >= 0) return true;
    }
  }
  return false;
}

void decreaseKey(HEAPMIN* h, int v, int d){
  int i = h->position[v];
  int pai = (i - 1)>>1;
  h->array[i]->d = d;
  while(i > 0 && h->array[i]->d < h->array[pai]->d){
    h->position[h->array[i]->v] = pai;
    h->position[h->array[pai]->v] = i;
    swapMinHeapNode(&h->array[i], &h->array[pai]);
    i = pai;
    pai = (i - 1)>>1;
  }
}

HEAPMIN* inicializaD(GRAFO* g, int* d, int* p, int s){
  HEAPMIN* h = createHeapMin(g->vertices);
  int i;
  for(i = 0; i < g->vertices; i++){
    d[i] = INT_MAX;
    h->array[i] = createHeapMinNode(i, d[i]);
    h->position[i] = i;
    p[i] = -1;
  }
  d[s] = 0;
  decreaseKey(h, s, 0);
  h->size = g->vertices;
  return h;
}

int* djikstra(GRAFO* g, int s, int** p){
  int* d = (int*) malloc(g->vertices * sizeof(int));
  *p = (int*) malloc(g->vertices * sizeof(int));
  HEAPMIN* h = inicializaD(g, d, *p, s);
  while(!heapIsEmpty(h)){
    int u = pop(h);
    ADJACENCIA* a = g->adj[u].head;
    while(a != NULL){
      int v = a->vertice;
      if(isInHeapMin(h, v) && d[u] != INT_MAX && d[u] + a->peso < d[v]){
        d[v] = d[u] + a->peso;
        (*p)[v] = u;
        decreaseKey(h, v, d[v]);
      }
      a = a->prox;
    }
  }
  return d;
}

int main(){
  GRAFO *g = criaGrafo(13);
  criarAresta(g, 0, 1, 10);
  criarAresta(g, 0, 2, 5);
  criarAresta(g, 2, 1, 3);
  criarAresta(g, 1, 3, 1);
  criarAresta(g, 2, 3, 8);
  criarAresta(g, 2, 4, 2);
  criarAresta(g, 4, 5, 6);
  criarAresta(g, 3, 5, 4);
  criarAresta(g, 3, 4, 4);
  criarAresta(g, 3, 7, 4);
  criarAresta(g, 7, 8, 4);
  criarAresta(g, 8, 0, 4);
  imprimirGrafo(g);
  int* p;
  int* r = djikstra(g, 7, &p);
  int i;
  for(i = 0; i < g->vertices; i++)
    printf("D(v0 -> v%d) = %d; p(v%d) = %d\n", i, r[i], i, p[i]);
  return 0;
}
