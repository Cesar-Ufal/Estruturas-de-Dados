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
  l->inicio = (ELEMENTO*) malloc(sizeof(ELEMENTO));
  l->inicio->next = l->inicio;
}

int tamanho(LISTA* l){
  ELEMENTO* aux = l->inicio->next;
  int tam = 0;
  while(aux != l->inicio){
    aux = aux->next;
    tam++;
  }
  return tam;
}

void exibirLista(LISTA* l){//o primeiro elemento printado não é o inicio
  printf("Lista: \" ");
  for(ELEMENTO* aux = l->inicio->next; aux != l->inicio; aux = aux->next)
    printf("%i ", aux->reg.chave);
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
  *prev = l->inicio;
  ELEMENTO* aux = l->inicio->next;
  while(aux->reg.chave < ch){
    *prev = aux;
    aux = aux->next;
  }
  if(aux != l->inicio && aux->reg.chave == ch)
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
  aux->next = prev->next;
  prev->next = aux;
  return 1;
}

int exclui(LISTA* l, TIPOCHAVE ch){
  ELEMENTO* prev;
  ELEMENTO* aux = buscarOrdPrev(l, ch, &prev);
  if(aux == NULL)
    return 0;
  prev->next = aux->next;
  free(aux);
  return 1;
}

void reiniciarLista(LISTA* l){
  ELEMENTO* aux = l->inicio->next;
  while(aux != l->inicio){
    ELEMENTO* apagar = aux;
    aux = aux->next;
    free(apagar);
  }
  l->inicio->next = l->inicio;
  return;
}

int main(void) {
  printf("Hello World\n");
  return 0;
}