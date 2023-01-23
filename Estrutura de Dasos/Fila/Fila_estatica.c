#include <stdio.h>
#include <malloc.h>

#define MAX 50
typedef int TIPOCHAVE;

typedef struct{
  TIPOCHAVE chave;
  //outros campos nescessários
} REGISTRO;

typedef struct FILA{
  REGISTRO reg[MAX];
  //outros campos nescessários
  int inicio, tam;
} FILA;

void inicializarLista(FILA* f){
  f->inicio = 0;
  f->tam = 0;
}

int tamanho(FILA* f){
  return f->tam;
}

void exibirPilha(FILA* f){//o primeiro elemento printado não é o inicio
  printf("FILA: \" ");
  for(int i = 0; i < f->tam; i++)
    printf("%i ", f->reg[(f->inicio + i) % MAX].chave);
  printf("\"\n");
}

int put(FILA* f, REGISTRO reg){
  if(f->tam == MAX){
    return 0;
  }
  f->reg[(f->inicio + f->tam) % MAX] = reg;
  f->tam = f->tam + 1;
  return 1;
}

int get(FILA* f, REGISTRO* reg){
  if(f->tam == 0){
    return 0;
  }
  *reg = f->reg[f->inicio];
  f->inicio = (f->inicio + 1) % MAX;
  return 1;
}

void reiniciarPilha(FILA* f){
  f->inicio = 0;
  f->tam = 0;
  return;
}

int main(void) {
  printf("Hello World\n");
  return 0;
}