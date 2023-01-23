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
  ELEMENTO* inicio;
} LISTA;

void inicializarLista(LISTA* l){
  l->inicio = NULL;
}

int tamanho(LISTA* l){
  ELEMENTO* aux = l->inicio;
  int tam = 0;
  while(aux->next != NULL){
    aux = aux->next;
    tam++;
  }
  return tam;
}

void exibirLista(LISTA* l){
  printf("Lista: \" ");
  for(ELEMENTO* aux = l->inicio; aux->next != NULL; aux = aux->next){
    printf("%i ", aux->reg.chave);
  }
  printf("\"\n");
}

ELEMENTO* buscar(LISTA* l, TIPOCHAVE ch){
  for(ELEMENTO* aux = l->inicio; aux->next != NULL; aux = aux->next){
    if(aux->reg.chave == ch)
      return aux;
  }
  return NULL;
}

ELEMENTO* buscarOrdPrev(LISTA* l, TIPOCHAVE ch, ELEMENTO** prev){
  *prev = NULL;
  ELEMENTO* aux = l->inicio;
  while(aux != NULL && aux->reg.chave < ch){
    *prev = aux;
    aux = aux->next;
  }
  if(aux != NULL && aux->reg.chave == ch)
    return aux;
  return NULL;
}

ELEMENTO* buscarOrd(LISTA* l, TIPOCHAVE ch){
  ELEMENTO* aux;
  return buscarOrdPrev(l, ch, &aux);
}

int inserirOrd(LISTA* l, REGISTRO reg){
  ELEMENTO *prev;
  ELEMENTO* aux = buscarOrdPrev(l, reg.chave, &prev);
  if(aux != NULL){//mesma chave encontrada, não substitui
    return 0;
  }
  aux = (ELEMENTO*) malloc(sizeof(ELEMENTO));
  aux->reg = reg;
  if(prev == NULL){
    aux->next = l->inicio;
    l->inicio = aux;
  }else{
    aux->next = prev->next;
    prev->next = aux;
  }
  return 1;
}

int exclui(LISTA* l, TIPOCHAVE ch){
  ELEMENTO* prev;
  ELEMENTO* aux = buscarOrdPrev(l, ch, &prev);
  if(aux == NULL)
    return 0;
  if(prev == NULL) 
    l->inicio = aux->next;
  else 
    prev->next = aux->next;
  free(aux);
  return 1;
}

void reiniciarLista(LISTA* l){
  ELEMENTO* aux;
  while(l->inicio != NULL){
    aux = l->inicio;
    l->inicio = l->inicio->next;
    free(aux);
  }
  return;
}

int main(void) {
  printf("Hello World\n");
  return 0;
}