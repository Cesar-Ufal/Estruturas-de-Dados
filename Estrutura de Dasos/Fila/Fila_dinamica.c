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
  ELEMENTO* fim;
} FILA;

void inicializarLista(FILA* f){
  f->topo = NULL;
  f->fim = NULL;
}

int tamanho(FILA* f){
  ELEMENTO* aux = f->topo;
  int tam = 0;
  while(aux != NULL){
    aux = aux->next;
    tam++;
  }
  return tam;
}

void exibirLista(FILA* f){//o primeiro elemento printado não é o inicio
  printf("Pilha: \" ");
  for(ELEMENTO* aux = f->topo; aux != NULL; aux = aux->next)
    printf("%i ", aux->reg.chave);
  printf("\"\n");
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

void reiniciarPilha(FILA* f){
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

int main(void) {
  printf("Hello World\n");
  return 0;
}