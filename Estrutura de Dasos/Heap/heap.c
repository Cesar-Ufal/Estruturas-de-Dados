#include <stdio.h>
#include <limits.h>

typedef struct{
  int *heap;
  int *pos;
  int n;
} HEAP;

void swap(HEAP* h, int a, int b){
  int temp = h->heap[a];
  h->heap[a] = h->heap[b];
  h->heap[b] = temp;
  temp = h->pos[h->heap[a]];
  h->pos[h->heap[a]] = h->pos[h->heap[b]];
  h->pos[h->heap[b]] = temp;
}

HEAP *inicHEAP(int n, int first){
  int i = -1, temp = first;
  HEAP *h = (HEAP*) malloc(sizeof(HEAP));
  h->n = n;
  h->pos = (int*) malloc(n * sizeof(int));
  h->heap = (int*) malloc(n * sizeof(int));
  while(++i < n){
    h->pos[i] = i;
    h->heap[i] = i;
  }
  swap(h, 0, first);
  return h;
}

int notEmpty(HEAP* h){
  return h->n;
}

void exibirLista(HEAP* h){
  int i;
  printf("Heap: \" ");
  for(i = 0; i < h->n; i++){
    printf("%i ", h->heap[i]);
  }
  printf("\"\n");
}

int buscar(HEAP* h, int i){
  return h->pos[i];
}

int pop(HEAP* h, int *prio){
  int filhoD, filho = 1, index = 0;
  swap(h, 0, --(h->n));
  while(filho < h->n){
    filhoD = filho|1;
    if(filhoD < h->n && prio[h->heap[filhoD]] < prio[h->heap[filho]])
      filho = filhoD;
    if(prio[h->heap[index]] <= prio[h->heap[filho]])
      break;
    swap(h, index, filho);
    index = filho;
    filho = (index<<1);
  }
  return h->heap[h->n];
}

void update(HEAP* h, int index, int *prio){
  int pai = index>>1;
  while(index && prio[h->heap[index]] < prio[h->heap[pai]]){
    swap(h, index, pai);
    index = pai;
    pai = index>>1;;
  }
}

int main(void) {
  int tam = 2, temp = 8;
  while(temp >>= 1){
    tam <<= 1;
  }
  printf("%d\n", tam);
  return 0;
}