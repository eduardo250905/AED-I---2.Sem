#include <stdio.h>
#include <stdlib.h>

typedef struct NO{
  int tempo;
  int num;
  struct NO* prox;
}NO;

typedef NO* PNO;

typedef struct FILA{
  PNO ini;
  PNO fim;
}FILA;

typedef FILA* PFILA;

PFILA inicializa(){
  PFILA f = (PFILA) malloc(sizeof(FILA));
  f->ini = NULL;
  f->fim = NULL;
  return f;
}

void incrementa(PFILA f, int t, int n){
  PNO ptr = (PNO) malloc(sizeof(NO));
  if(ptr == NULL){
    printf("Erro de alocação.\n");
    return;
  }else{
    ptr->tempo = t;
    ptr->num = n;
    ptr->prox = NULL;
    if(f->ini == NULL){
      f->ini = ptr;
    } else{
      f->fim->prox = ptr;
    }
    f->fim = ptr;
  }
}

PNO retira(PFILA f){
  PNO ptr = f->ini;
  if(ptr != NULL){
    f->ini = ptr->prox;
    ptr->prox = NULL;
    return ptr;
    free(ptr);
    if(f->ini == NULL){
      f->fim = NULL;
    }
  }else{
    return NULL;
  }
}

int main(void) {
  PFILA fila = inicializa();
  int N, A, T, i;
  scanf("%d %d", &N, &A);
  if((N < 1 || N > 1023) || (A < 1 || A > 25)){
    return -1;
  }
  for(i=0; i<N; i++){
    scanf("%d", &T);
    incrementa(fila, T, i+1);
  }
  PNO pNO[A], pNOini[A];
  for(i=0; i<A; i++){
    pNO[i] = pNOini[i] = retira(fila);
    
  }
  if(fila->ini != NULL){
    while(fila->ini != NULL){
      for(i=0; i<A; i++){
        pNO[i]->tempo--;
        if(pNO[i]->tempo <= 0){
          pNO[i]->prox = retira(fila);
          pNO[i] = pNO[i]->prox;
        }
      }
    }
  }
  for(i=0; i<A; i++){
    pNO[i] = pNOini[i];
    printf("%d: ", i+1);
    if(pNO[i]!=NULL){
      while(pNO[i]!=NULL){
        printf("%d ", pNO[i]->num);
        pNO[i] = pNO[i]->prox;
      }
    }
    printf("\n");
  }
  free(fila);
  return 0;
}
