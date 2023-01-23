#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#define true 1
#define false 0
#define N_ALFABETO 26

typedef int bool;
typedef bool TIPORET;

typedef struct ELEMENTO{
  TIPORET fim;
  struct ELEMENTO* filhos[N_ALFABETO];
  //outros campos nescessários
} ELEMENTO;

typedef ELEMENTO* PONT;

ELEMENTO* criaNo() {
  PONT p;
  p = (PONT) malloc(sizeof(ELEMENTO));
  if(p){
    p->fim = false;
    int i;
    for(i = 0; i < N_ALFABETO; i++)
      p->filhos[i] = NULL;
  }
  return p;
}

PONT inicializa(){
  return criaNo();
}

int mapearIndice(char c) {
  return ((int) c - (int)'a');
}

void insere(PONT raiz, char* chave){
  int nivel;
  int compr = strlen(chave);
  int i;
  PONT aux = raiz;
  for(nivel = 0; nivel < compr; nivel++){
    i = mapearIndice(chave[i]);
    if(!aux->filhos[i]){
      aux->filhos[i] = criaNo();
    }
    aux = aux->filhos[i];
  }
  aux->fim = true;
}

bool busca(PONT raiz, char* chave){
  int nivel;
  int compr = strlen(chave);
  int i;
  PONT aux = raiz;
  for(nivel = 0; nivel < compr; nivel++){
    i = mapearIndice(chave[i]);
    if(!aux->filhos[i]) return false;
    aux = aux->filhos[i];
  }
  return aux->fim;
}

int main() {
  ELEMENTO* r = inicializa();
}