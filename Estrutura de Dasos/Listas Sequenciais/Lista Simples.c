#include <stdio.h>

#define MAX 50 //define o número máximo da lista
typedef int TIPOCHAVE;

typedef struct{
  TIPOCHAVE chave;
  //outros campos nescessários
} REGISTRO;

typedef struct{
  REGISTRO A[MAX];
  int nroElem;
} LISTA;

void inicializarLista(LISTA* l){
  l->nroElem = 0;
}

int tamanho(LISTA* l){
  return l->nroElem;
}

void exibirLista(LISTA* l){
  printf("Lista: \" ");
  for(int i = 0; i < l->nroElem;i++){
    printf("%i ", l->A[i].chave);
  }
  printf("\"\n");
}

int buscar(LISTA* l, TIPOCHAVE ch){
  for(int i = 0; i < l->nroElem; i++){
    if(l->A[i].chave == ch)
      return i;
  }
  return -1;
}

int inserir(LISTA* l, REGISTRO reg, int i){
  if(l->nroElem == MAX || i < 0 || i > l->nroElem){
    return 0;
  }
  for(int j = l->nroElem; j > i; j--)
    l->A[j] = l->A[j - 1];
  l->A[i] = reg;
  l->nroElem++;
  return 1;
}

int exclui(LISTA* l, TIPOCHAVE ch){
  int i = buscar(l, ch);
  if(i == -1)
    return 0;
  for(int j = i; j < l->nroElem - 1; j++)
    l->A[j] = l->A[j + 1];
  l->nroElem--;
  return 1;
}

int main(void) {
  printf("Hello World\n");
  return 0;
}