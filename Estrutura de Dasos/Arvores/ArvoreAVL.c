#include <stdio.h>
#include <malloc.h>

typedef int TIPOCHAVE;

typedef struct{
  TIPOCHAVE chave;
  //outros campos nescessários
} REGISTRO;

typedef struct ELEMENTO{
  REGISTRO reg;
  struct ELEMENTO* r;
  struct ELEMENTO* l;
  int h;
  //outros campos nescessários
} ELEMENTO;

typedef ELEMENTO* PONT;

PONT criaNo(REGISTRO* reg){
  PONT novo = (PONT) malloc(sizeof(ELEMENTO));
  novo->l = NULL;
  novo->r = NULL;
  novo->h = 0;
  novo->reg.chave = reg->chave;
  return novo;
}

PONT inicializa(){
  return criaNo(NULL);
}

int max(int a, int b){
  return a > b ? a : b;
}

int altura(PONT r){
  if(!r) return -1;
  return r->h;
}

PONT direita(PONT r){
  PONT aux = r->l;
  r->l = aux->r;
  aux->r = r;
  r->h = max(altura(r->l), altura(r->r)) + 1;
  aux->h = max(altura(aux->l), r->h) + 1;
  return aux;
}

PONT esquerda(PONT r){
  PONT aux = r->r;
  r->r = aux->l;
  aux->l = r;
  r->h = max(altura(r->l), altura(r->r)) + 1;
  aux->h = max(altura(aux->r), r->h) + 1;
  return aux;
}

PONT esquerdaDireita(PONT r){
  r->l = esquerda(r->l);
  return direita(r);
}

PONT direitaEsquerda(PONT r){
  r->r = direita(r->r);
  return esquerda(r);
}

PONT insere(PONT r, REGISTRO* reg){
  if(!r) return criaNo(reg);
  if(reg->chave < r->reg.chave){
    r->l = insere(r->l, reg);
    if(altura(r->l) - altura(r->r) == 2){
      if(reg->chave < r->l->reg.chave){
        r = direita(r);
      }else{
        r = esquerdaDireita(r);
      }
    }
  } else {
    if(reg->chave > r->reg.chave) {
      r->r = insere(r->r, reg);
      if(altura(r->r) - altura(r->l) == 2){
        if(reg->chave > r->r->reg.chave){
          r = esquerda(r);
        } else {
          r = esquerdaDireita(r);
        }
      }
    }
  }
  r->h = max(altura(r->l), altura(r->r)) + 1;
  return r;
}

ELEMENTO* busca(ELEMENTO* raiz, TIPOCHAVE ch){
  if(raiz == NULL) return NULL;
  if(raiz->reg.chave == ch) return raiz;
  if(raiz->reg.chave > ch) return busca(raiz->l, ch);
  return busca(raiz->r, ch);
}

int contagem(ELEMENTO* raiz){
  if(raiz == NULL) return 0;
  return contagem(raiz->l) + 1 + contagem(raiz->r);
}

void exibir(ELEMENTO* raiz){
  if(raiz != NULL){
    printf("%d", raiz->reg.chave);
    printf("(");
    exibir(raiz->l);
    exibir(raiz->r);
    printf(")");
  }
}

ELEMENTO* buscaPai(ELEMENTO* raiz, TIPOCHAVE ch, ELEMENTO** pai){
  ELEMENTO* atual = raiz;
  *pai = NULL;
  while(atual){
    if(atual->reg.chave == ch) return atual;
    *pai = atual;
    if(atual->reg.chave > ch) atual = atual->l;
    else atual = atual->r;
  }
  return NULL;
}

ELEMENTO* tira(ELEMENTO* raiz, TIPOCHAVE ch){
  ELEMENTO *pai, *no, *p, *q;
  no = buscaPai(raiz, ch, &pai);
  if(no == NULL) return raiz;
  if(no->l == NULL || no->r == NULL){
    if(no->l == NULL) q = no->r;
    else q = no->l;
  } else {
    p = no;
    q = no->l;
    while(q->r != NULL){
      p = q;
      q = q->r;
    }
    if(p != no){
      p->r = q->l;
      q->l = no->l;
    }
    q->r = no->r;
  }
  if(ch < pai->reg.chave) pai->l =q;
  else pai->r = q;
  free(no);
  return raiz;
}