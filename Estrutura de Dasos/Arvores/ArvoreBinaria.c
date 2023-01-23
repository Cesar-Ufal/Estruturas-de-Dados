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
  //outros campos nescessários
} ELEMENTO;

typedef struct{
  ELEMENTO* raiz;
} ARVORE;

void inicializarLista(ARVORE* a){
  a->raiz = NULL;
}
//sem duplicação
ELEMENTO* put(ELEMENTO* raiz, ELEMENTO* folha){
  if(raiz == NULL){
    return folha;
  } 
  if(folha->reg.chave < raiz->reg.chave){
    raiz->l = put(raiz->l, folha);
  } else {
    raiz->r = put(raiz->r, folha);
  }
  return raiz;
}

int insert(ARVORE* a, REGISTRO reg){
  ELEMENTO* aux = (ELEMENTO*) malloc(sizeof(ELEMENTO));
  aux->reg = reg;
  aux->r = NULL;
  aux->l = NULL;
  a->raiz = put(a->raiz, aux);
  return 1;
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