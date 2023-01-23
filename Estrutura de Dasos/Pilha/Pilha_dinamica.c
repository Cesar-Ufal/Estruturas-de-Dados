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
  //outros campos nescessários
} ELEMENTO;

typedef struct{
  ELEMENTO* topo;
} PILHA;

void inicializarLista(PILHA* p){
  p->topo = NULL;
}

int tamanho(PILHA* p){
  ELEMENTO* aux = p->topo;
  int tam = 0;
  while(aux != NULL){
    aux = aux->next;
    tam++;
  }
  return tam;
}

void exibirLista(PILHA* p){//o primeiro elemento printado não é o inicio
  printf("Pilha: \" ");
  for(ELEMENTO* aux = p->topo; aux != NULL; aux = aux->next)
    printf("%i ", aux->reg.chave);
  printf("\"\n");
}

int push(PILHA* p, REGISTRO reg){
  ELEMENTO* aux = (ELEMENTO*) malloc(sizeof(ELEMENTO));
  aux->reg = reg;
  aux->next = p->topo;
  p->topo = aux;
  return 1;
}

int pop(PILHA* p, REGISTRO* reg){
  if(p->topo == NULL)
    return 0;
  ELEMENTO* aux = p->topo;
  *reg = aux->reg;
  p->topo = p->topo->next;
  free(aux);
  return 1;
}

void reiniciarPilha(PILHA* p){
  ELEMENTO* aux = p->topo;
  while(aux != NULL){
    ELEMENTO* apagar = aux;
    aux = aux->next;
    free(apagar);
  }
  p->topo = NULL;
  return;
}

int main(void) {
  printf("Hello World\n");
  return 0;
}