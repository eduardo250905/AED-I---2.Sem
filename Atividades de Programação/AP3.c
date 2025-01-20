#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 1024

typedef struct aux{
  int num;
  struct pilha* prox;
}ELEMENTO;

typedef ELEMENTO* POINT;

typedef struct {
  POINT topo;
}PILHA;

void inicializa(PILHA* p){
  p->topo = NULL;
}

int vazia(PILHA* p){
  if(p->topo == NULL){
    return 1;
  }
  return 0;
}

void push(PILHA* p, int n){
  POINT novo = (POINT) malloc(sizeof(ELEMENTO));
  novo->num = n;
  novo->prox = p->topo;
  p->topo = novo;
}

int pop(PILHA* p){
  int n;
  if(vazia(p) == 1) return -1;
  n = p->topo->num;
  POINT apagar = p->topo;
  p->topo = p->topo->prox;
  free(apagar);
  return n;
}

int main(void) {
  PILHA* minha_pilha = (PILHA*) malloc(sizeof(PILHA));
  if(minha_pilha == NULL){
    return -1;
  } else{
    inicializa(minha_pilha);
  }
  char str[TAM_MAX];
  int i, n, a1, a2, x, y;
  scanf("%[^\n]", str);
  if(strlen(str) < 3){
    printf("Invalid Expression"); return 0;
  }
  for(i=0; i<strlen(str); i++){
    if(str[i] >= '0' && str[i] <= '9'){
      n = (int) str[i]-'0';
      push(minha_pilha, n);
    }
    else{
      x=pop(minha_pilha); // Pega elemento do topo
      y=pop(minha_pilha); // Pega outro elemento do topo
      if(x != -1 && y != -1){
        switch (str[i]){ // Realiza a operação utilizando a pilha
          case '+': push(minha_pilha, y + x); break;
          case '-': push(minha_pilha, y - x); break;
          case '*': push(minha_pilha, y * x); break;
          case '/': push(minha_pilha, y / x); break;
          default: printf("Invalid Expression"); return 0;
        }
      } else{
        printf("Invalid Expression"); return 0;
      }
    }
  }
  printf("%d", minha_pilha->topo->num);
  free(minha_pilha);
  return 0;
}
