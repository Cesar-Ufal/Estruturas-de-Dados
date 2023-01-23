#include <stdio.h>
#include <malloc.h>

typedef int TIPOCHAVE;

typedef struct{
  TIPOCHAVE chave;
  //outros campos nescessários
} REGISTRO;

typedef struct ELEMENTO{
  REGISTRO reg;
  struct ELEMENTO* primFilho;
  struct ELEMENTO* proxIrmao;
  //outros campos nescessários
} ELEMENTO;

typedef struct{
  ELEMENTO* raiz;
} ARVORE;

ELEMENTO* criaNovoNo(TIPOCHAVE ch) {
  ELEMENTO* novo = (ELEMENTO*) malloc(sizeof(ELEMENTO));
  novo->reg.chave = ch;
  novo->primFilho = NULL;
  novo->proxIrmao = NULL;
  return novo;
}

ELEMENTO* inicializa(TIPOCHAVE ch) {
  return criaNovoNo(ch);
}

void exibirArvore(ELEMENTO* raiz){
  if(raiz == NULL) return;
  printf("%d(", raiz->reg.chave);
  ELEMENTO* aux = raiz->primFilho;
  while(aux){
    exibirArvore(aux);
    aux = aux->proxIrmao;
  }
  printf(")");
}

ELEMENTO* buscaChave(int ch, ELEMENTO* raiz){
  if(!raiz) return NULL;
  if(raiz->reg.chave == ch) return raiz;
  ELEMENTO* aux = raiz->primFilho;
  while(aux){
    ELEMENTO* res = buscaChave(ch, aux);
    if(res) return res;
    aux = aux->proxIrmao;
  }
  return NULL;
}

int inserir(ELEMENTO* raiz, TIPOCHAVE novaChave, TIPOCHAVE chavePai){
  ELEMENTO* pai = buscaChave(chavePai, raiz);
  if(!pai) return 0;
  ELEMENTO* filho = criaNovoNo(novaChave);
  ELEMENTO* aux = pai->primFilho;
  if(!aux) pai->primFilho = filho;
  else{
    while(aux->proxIrmao){
      aux = aux->proxIrmao;
    }
    aux->proxIrmao = filho;
  }
  return 1;
}

int main() {
  ELEMENTO* r = inicializa(8);
}