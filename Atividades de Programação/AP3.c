#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 1024

struct pilha {
  int topo;
  int itens[TAM_MAX];
};

struct pilha* criar_pilha(){
  struct pilha* nova_pilha = (struct pilha*) malloc(sizeof(struct pilha));
  if(nova_pilha == NULL){
    exit(-1);
  }
  nova_pilha->topo = -1;
  return nova_pilha;
}

int push(struct pilha* p, int val){
  if(p->topo>=TAM_MAX-1){ //Verifica se a pilha está cheia
    return -1;
  }
  (p->topo)++;
  p->itens[p->topo] = val;
  return 0;
}

int pop(struct pilha* p){
  if(p->topo == -1){ //Verifica se a pilha está vazia
    return -1;
  }
  else{
    int val = p->itens[p->topo];
    (p->topo)--;
    return val;
  }
}

struct pilha *remover(struct pilha* p){
  free(p);
  return (NULL);
}

int main(void) {
  int i, n, x, y;
  char str[TAM_MAX];
  struct pilha* minha_pilha = criar_pilha();
  
  scanf("%[^\n]", str);
  for(i=0; i<strlen(str); i++){
    if(str[i]>='0' && str[i]<='9'){
      n = (int) str[i]-'0';
      push(minha_pilha, n);
    }
    else{
      x = pop(minha_pilha);
      y = pop(minha_pilha);
      if(x != -1 && y != -1){
        switch (str[i]){
          case '+': push(minha_pilha, y + x); break;
          case '-': push(minha_pilha, y - x); break;
          case '*': push(minha_pilha, y * x); break;
          case '/': push(minha_pilha, y / x); break;
          default: printf("Invalid Expression"); return -1;
        }
      } else{
        printf("Invalid Expression"); return -1;
      }
    }
  }
  printf("%d", minha_pilha->itens[minha_pilha->topo]);
  remover(minha_pilha);
  return 0;
}
