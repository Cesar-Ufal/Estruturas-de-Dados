#include <stdio.h>
#include <malloc.h>

#define MAX 50
typedef int TIPOCHAVE;

typedef struct{
  TIPOCHAVE chave;
  //outros campos nescessários
} REGISTRO;

typedef struct PILHA{
  REGISTRO reg[MAX];
  //outros campos nescessários
  int topo;
} PILHA;

void inicializarLista(PILHA* p){
  p->topo = -1;
}

int tamanho(PILHA* p){
  return p->topo + 1;
}

void exibirPilha(PILHA* p){//o primeiro elemento printado não é o inicio
  printf("Pilha: \" ");
  for(int i = p->topo; i >= 0; i--)
    printf("%i ", p->reg[i].chave);
  printf("\"\n");
}

int push(PILHA* p, REGISTRO reg){
  if(p->topo == MAX - 1){
    return 0;
  }
  p->topo = p->topo +1;
  p->reg[p->topo] = reg;
  return 1;
}

int pop(PILHA* p, REGISTRO* reg){
  if(p->topo == -1){
    return 0;
  }
  *reg = p->reg[p->topo];
  p->topo = p->topo - 1;
  return 1;
}

void reiniciarPilha(PILHA* p){
  p->topo = -1;
  return;
}

int main(void) {
  printf("Hello World\n");
  return 0;
}