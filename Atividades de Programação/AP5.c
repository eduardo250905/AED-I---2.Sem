#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista2{
  char letra;
  int tam;
  struct lista2 *prox;
  struct lista2 *ant;
}TLista2;

typedef TLista2 *PLista2;

PLista2 inicializa_lista(){
  return NULL;
}

PLista2 inserir(PLista2 p, char l, int t){
  PLista2 novo = (PLista2)malloc(sizeof(TLista2));
  novo->letra = l;
  novo->tam = t;
  novo->prox = NULL;
  if(p == NULL){
    novo->ant = NULL;
    return novo;
  }
  PLista2 temp=p;
  while(temp->prox != NULL){
    temp = temp->prox;
  }
  temp->prox = novo;
  novo->ant = temp;
  return p;
}

PLista2 retirar(PLista2 p){
  PLista2 t=p;
  while(t!=NULL){
    if(t->tam == 1){
      PLista2 aux = t;
      if(t->ant == NULL && t->prox->tam >= 2){
        p = t->prox;
        t->prox->tam += 1;
        t->prox->ant = NULL;
        t = t->prox;
        free(aux);
      } else if(t->prox == NULL && t->ant->tam >= 2){
        t->ant->tam += 1;
        t->ant->prox = NULL;
        t = t->prox;
        free(aux);
      } else if(t->ant->tam > 1 && t->prox->tam >= 2){
        if(t->ant->tam >= t->prox->tam){
          t->ant->tam += 1;
        } else{
          t->prox->tam += 1;
        }
        t->ant->prox = t->prox;
        t->prox->ant = t->ant;
        t = t->prox;
        free(aux);
      } else{
        t = t->prox;
      }
    }
    else{
      t=t->prox;
    }
  }
  return p;
}

void conta_caracteres(PLista2 p){
  int ContDig=0, ContAlg=0;
  PLista2 aux=p;
  while(aux != NULL){
    int n = aux->tam;
    do{
      ContDig++;
      n = n / 10;
    } while(n != 0);
    ContAlg++;
    aux = aux->prox;
  }
  printf("%d\n", ContDig+ContAlg);
}

void imprime(PLista2 p){
  PLista2 aux = p;
  while(aux != NULL){
    printf("%d%c", aux->tam, aux->letra);
    aux = aux->prox;
  }
  printf("\n");
}

void libera(PLista2 p){
  PLista2 aux;
  while(p!=NULL){
    aux = p;
    p = p->prox;
    free(aux);
  }
}

int main(void) {
  char str[1023];
  PLista2 lista = inicializa_lista();
  int i, t=1;
  scanf("%s", str);
  for(i=1; i<strlen(str); i++){
    if(str[i] == str[i-1]){
      t++;
    }
    else{
      lista = inserir(lista, str[i-1], t);
      t=1;
    }
    if(i==(strlen(str)-1)){
      lista = inserir(lista, str[i], t);
    }
  }
  conta_caracteres(lista);
  imprime(lista);
  lista = retirar(lista);
  conta_caracteres(lista);
  imprime(lista);
  libera(lista);
  return 0;
}
