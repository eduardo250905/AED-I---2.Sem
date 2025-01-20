#include <stdio.h>
#include <stdlib.h>

struct Scorredores{
  int num_carro;
  char nome[20];
};

typedef struct Scorredores *Pcorredor;

void troca_valores(Pcorredor a, Pcorredor b){
  struct Scorredores x;
  x = *a;
  *a = *b;
  *b = x;
}

int main(void) {
  int N, i, esc, c;
  scanf("%d", &N);
  if(N<3 || N>1000){
    exit(1);
  }
  
  Pcorredor corredores[N];

  // Cria N corredores com respectivos nomes e numeros do carro
  for(i=0; i<N; i++){         
    corredores[i] = (Pcorredor)malloc(sizeof(struct Scorredores));
    if(corredores[i] == NULL){
      exit(1);
    }
    scanf("%d", &corredores[i]->num_carro);
    scanf("%s", &corredores[i]->nome);
  }
  
  int v[N];
  
  for(i=0; i<N; i++){
    scanf("%d", &v[i]);
  }

  // Define a ordem de partida dos competidores
  for(i=0; i<N; i++){
    for(c=0; c<N; c++){
      if(v[i] == corredores[c]->num_carro){
        troca_valores(corredores[c], corredores[i]);
        break;
      }
    }
  }

  // Realiza possíveis ultrapasagens até que esc = -1
  do{
    scanf("%d", &esc);
    for(i=1; i<N; i++){
      if(esc == corredores[i]->num_carro){
        troca_valores(corredores[i], corredores[i-1]); 
      }
    }
  }while(esc != -1);

  for(i=0; i < 3; i++){
    printf("%d %s\n", corredores[i]->num_carro, corredores[i]->nome);
  }
  
  for(i=0; i<N; i++){
    free(corredores[i]);
  }
  return 0;
}
