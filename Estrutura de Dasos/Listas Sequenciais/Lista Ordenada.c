#include <stdio.h>

#define MAX 50 //define o número máximo da lista
typedef int TIPOCHAVE;

typedef struct{
  TIPOCHAVE chave;
  //outros campos nescessários
} REGISTRO;

typedef struct{
  REGISTRO A[MAX + 1];//posição extra é criada para o sentinela
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

int buscarSentinela(LISTA* l, TIPOCHAVE ch){
  int i = 0;
  l->A[l->nroElem].chave = ch;
  for(; l->A[i].chave != ch; i++);
  return i == l->nroElem ? -1 : i;
}

int buscarBinaria(LISTA* l, TIPOCHAVE ch){
  int meio, esq = 0, dir = l->nroElem - 1;
  while(dir >= esq){
    meio = (dir + esq) / 2;
    if(l->A[meio].chave == ch)
      return meio;
    if(l->A[meio].chave < ch)
      esq = meio + 1;
    else
      dir = meio - 1;
  }
  return -1;
}

int inserir(LISTA* l, REGISTRO reg){
  if(l->nroElem == MAX)
    return 0;
  int pos = l->nroElem;
  while(pos > 0 && l->A[pos - 1].chave > reg.chave){
    l->A[pos] = l->A[pos - 1];
    pos--;
  }
  l->A[pos] = reg;
  l->nroElem++;
  return 1;
}

int exclui(LISTA* l, TIPOCHAVE ch){
  int i = buscarBinaria(l, ch);
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