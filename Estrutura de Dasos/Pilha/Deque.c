#include <stdio.h>
#include <malloc.h>

typedef int TIPOCHAVE;

typedef struct{
  TIPOCHAVE chave;
  //outros campos nescessários
} REGISTRO;

typedef struct ELEMENTO{
  REGISTRO reg;
  struct ELEMENTO* next;
  struct ELEMENTO* prev;
  //outros campos nescessários
} ELEMENTO;

typedef struct{
  ELEMENTO* head;
}DEQUE;

void inicializarLista(DEQUE* d){
  d->head = (ELEMENTO*) malloc(sizeof(ELEMENTO));
  d->head->next = d->head;
  d->head->prev = d->head;
}

int tamanho(DEQUE* d){
  ELEMENTO* aux = d->head->next;
  int tam = 0;
  while(aux != d->head){
    aux = aux->next;
    tam++;
  }
  return tam;
}

void exibirLista(DEQUE* d){//o primeiro elemento printado não é o inicio
  printf("DEQUE: \" ");
  for(ELEMENTO* aux = d->head->next; aux != d->head; aux = aux->next)
    printf("%i ", aux->reg.chave);
  printf("\"\n");
}

int put(DEQUE* d, REGISTRO reg){
  ELEMENTO* aux = (ELEMENTO*) malloc(sizeof(ELEMENTO));
  aux->reg = reg;
  aux->prev = d->head;
  aux->next = d->head->next;
  d->head->next = aux;
  aux->next->prev = aux;
  return 1;
}

int push(DEQUE* d, REGISTRO reg){
  ELEMENTO* aux = (ELEMENTO*) malloc(sizeof(ELEMENTO));
  aux->reg = reg;
  aux->next = d->head;
  aux->prev = d->head->prev;
  d->head->prev = aux;
  aux->prev->next = aux;
  return 1;
}

int pop(DEQUE* d, REGISTRO* reg){
  if(d->head->next == d->head)
    return 0;
  ELEMENTO* aux = d->head->prev;
  *reg = aux->reg;
  d->head->prev = aux->prev;
  aux->prev->next = d->head;
  free(aux);
  return 1;
}

int get(DEQUE* d, REGISTRO* reg){
  if(d->head->next == d->head)
    return 0;
  ELEMENTO* aux = d->head->next;
  *reg = aux->reg;
  d->head->next = aux->next;
  aux->next->prev = d->head;
  free(aux);
  return 1;
}

void reiniciarPilha(DEQUE* d){
  ELEMENTO* aux = d->head->next;
  while(aux != d->head){
    ELEMENTO* apagar = aux;
    aux = aux->next;
    free(apagar);
  }
  d->head->next = d->head;
  d->head->prev = d->head;
  return;
}

int main(void) {
  printf("Hello World\n");
  return 0;
}