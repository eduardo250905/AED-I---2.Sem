// Eduardo Lopes Arrais de Oliveira      RA: 168804

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arvGen{ // Define a estrutura de um elemento da arvore
  char nome[20], indicou[20]; // nome e pessoa que indicou(ou fundador)
  int ano, mes, dia; // data da contratação
  struct arvGen *prim; // primeiro filho
  struct arvGen *prox; // proximo irmao
  struct arvGen *pai; // pai do elemento
}TArvGen;

typedef TArvGen *PArvGen; // Define o tipo para ponteiro de um elemento da arvore

typedef struct arvore { // Define a estrutura da arvore
  PArvGen raiz;
} TArvore;

TArvore criaArvore(){ // cria uma estrutura arvore que armazena a raiz
  TArvore a;
  a.raiz = NULL;
  return a;
}

PArvGen cria(char n[20], char i[20], int a, int m, int d){ // Inicializa o elemento
  PArvGen g = (PArvGen) malloc(sizeof(TArvGen));
  strcpy(g->nome, n); 
  strcpy(g->indicou, i);
  g->ano = a;
  g->mes = m;
  g->dia = d;
  g->prim = NULL;
  g->prox = NULL;
  g->pai = NULL;
  return g;
}

int conversao(PArvGen a){ // Função transforma a data em um número, quanto menor for esse número, mais antiga é a data
  int num;
  num = a->ano * 10000 + a->mes * 100 + a->dia;
  return num;
}

void insere(PArvGen pai, PArvGen filho) { // Função de incerir elementos na arvore
    PArvGen g = pai->prim; // g recebe o primeiro filho de pai
    PArvGen ant = NULL; // ant recebe valor nulo

    if (g == NULL || conversao(filho) < conversao(g)) { // Se pai não tiver nenhum filho ou se a data de filho é mais antiga do que a data de g
        filho->prox = g; // O próximo de filho vai ser igual a g
        pai->prim = filho; // O primeiro de pai vai ser igual ao filho
    } else {
        while (g != NULL && conversao(g) <= conversao(filho)) { // Enquanto existir um elemento e a data de g for mais antiga do que a data do filho
            ant = g; // ant recebe g
            g = g->prox; // g vai ser igual ao próximo
        }
        ant->prox = filho; // O proximo do anterior recebe filho
        filho->prox = g; // O próximo do filho recebe g
    }
    filho->pai = pai; // O pai de filho vai ser igual a pai
    if (g != NULL) { // Se g não for nulo
        g->pai = pai; // pai de g vai ser pai
    }
}

PArvGen busca(PArvGen a, char n[20]){ // Função simples de busca. Retorna o nó caso ache o nome, se não, retorna NULL
  PArvGen p;
  if(a == NULL) return NULL;
  if(strcmp(a->nome, n) == 0) return a;
  p = busca(a->prim, n);
  if(p == NULL) return busca(a->prox, n);
  return p;
}

void libera(PArvGen a){ // Função de liberação de memória recursiva
  if(a != NULL){
    libera(a->prim);
    libera(a->prox);
    free(a);
  }
}

void liberaArvore(TArvore *pa){ // Chama a função libera para desalocar a memória
  if(pa->raiz != NULL){
    libera(pa->raiz); 
  }
}

void exclui(PArvGen a, TArvore *pa) { // Função para excluir elementos da árvore
    if (a == NULL) {
        return; // Se a for null, retorna
    }
    libera(a->prim); // libera da memória todos os descendentes de a
    if (a->pai != NULL) { // Se não for a raiz
      PArvGen ant = a->pai->prim; // ant recebe o primeiro filho do pai de a
      if (ant == a) { 
          a->pai->prim = a->prox; // se a for o primeiro filho, o primeiro filho será agora o próximo de a
      } else {
          while (ant->prox != a) { // Caminha com ant até que o próximo de ant seja igual ao nó a
              ant = ant->prox; 
          }
          ant->prox = a->prox; // Próximo do ant vai ser igual ao próximo de a
      }
      free(a); // Libera a
    }
    else{ // Caso seja a raiz
      pa->raiz = NULL; // Desassocia a estrutura arvore com a raiz
      free(a); // libera a memória da raiz
    }
}


void imprime(PArvGen a){ // Função recursiva de imprimir a árvore
  if(a != NULL){
    printf("%s\n", a->nome);
    imprime(a->prim);
    imprime(a->prox);
  }
}

int main(void) {
  char nome[20], ind[20];
  int esc=0, dia, mes, ano;
  PArvGen folha, a;
  TArvore arvore = criaArvore();
  while(esc != 4){ // Enquanto esc for diferente de 4
    scanf("%d", &esc);
    switch(esc){ 
      case 1: // Adiciona um elemento
        scanf("%s %d %d %d %s", nome, &dia, &mes, &ano, ind);
        if(arvore.raiz == NULL){ // se a arvore não possui raiz
          if(strcmp(ind, "fundador") == 0){ // Se o usuário digitou o fundador
            arvore.raiz = cria(nome, ind, ano, mes, dia); // raíz vai ser criada
          }
        } 
        else{  // Caso já exista um valor de raiz
          if(busca(arvore.raiz, nome) != NULL) break; // Se já existe esse nome, ignora o resto do código e não adiciona esse elemento
          a = busca(arvore.raiz, ind); // Busca se o nome do indicador existe e guarda em a
          if(a != NULL){ // Se existir
            folha = cria(nome, ind, ano, mes, dia); // Cria uma folha
            insere(a, folha); // Incere a folha, atribuindo a como pai e folha como filho
          }
        } break;
      case 2: // Exclui
        scanf("%s", nome); // Variável nome recebe o nome do elemento que se deseja excluir
        a = busca(arvore.raiz, nome); // Busca se o nome existe e guarda em a
        if(a != NULL){
          exclui(a, &arvore); // Se existir, exclui a
        } break;
      case 3: // Imprime
        imprime(arvore.raiz); break;
    }
  }
  liberaArvore(&arvore); // Chama a função para liberar a árvore
  return 0;
}
