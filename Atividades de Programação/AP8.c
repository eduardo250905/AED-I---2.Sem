// Eduardo Lopes Arrais de Oliveira  RA: 168804

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef struct arv{
  float area;
  char tipo;
  struct arv* esq;
  struct arv* dir;
}TArv;

typedef TArv *PArv;

int Busca_Arv(PArv arv, char c) { // Função para buscar caractere na arvore
  if (arv == NULL) {
    return 0; // Se não achar retorna 0
  }
  if (arv->tipo == c) {
    return 1; // Se achar retorna 1
  }
  int esq = Busca_Arv(arv->esq, c);
  int dir = Busca_Arv(arv->dir, c);
  return esq || dir; // Recursividade
}

PArv maximo(PArv arv){ // Dado um nó pega a subarvore de maior elemento
  PArv aux=arv;
  while(aux->dir != NULL){
    aux = aux->dir;
  }
  return aux;
}

void inserir(PArv* arv, float area, char tipo) { // Função para adicionar um novo elemento
  if (*arv == NULL) { // Se a arvore está vazia, cria o primeiro elemento
    *arv = (PArv)malloc(sizeof(TArv));
    (*arv)->area = area;
    (*arv)->tipo = tipo;
    (*arv)->esq = NULL;
    (*arv)->dir = NULL;
  } else {
    if (area == (*arv)->area) {
      return; // Ignora valores duplicados
    } else if (area < (*arv)->area) { // Se o valor é menor
      inserir(&((*arv)->esq), area, tipo); // Insere na subárvore esquerda
    } else { // Se é maior
      inserir(&((*arv)->dir), area, tipo); // Insere na subárvore direita
    }
  }
}

PArv removerMaximo(PArv arv) { // Remove o maior elemento de uma arvore
  if (arv == NULL)
    return NULL;

  if (arv->dir == NULL) {
    PArv aux = arv->esq;
    free(arv);
    return aux;
  }

  arv->dir = removerMaximo(arv->dir);

  return arv;
}


void remover(PArv* arv, float n, char c) {
  if (*arv != NULL) {
    remover(&((*arv)->esq), n, c);
    remover(&((*arv)->dir), n, c);
    while (*arv != NULL && (*arv)->tipo == c && (*arv)->area < n) {
      PArv aux = *arv;
      if (aux->esq != NULL && aux->dir != NULL) { // Se o nó tiver dois filhos, encontrar o maior nó à esquerda
        PArv maxEsq = maximo(aux->esq); // Substituir os dados do nó atual pelos do maior nó à esquerda
        aux->area = maxEsq->area;
        aux->tipo = maxEsq->tipo; // Remover o nó encontrado (que agora está duplicado)
        aux->esq = removerMaximo(aux->esq);
      } else {
        if (aux->esq != NULL) { // Se o nó possui o nó da esquerda, substitui arv por ele
          *arv = aux->esq;
        } else {
          *arv = aux->dir; // Ao contrário, substitui à direita
        }
        free(aux); // Libera a memória do elemento removido
      }
    }
  }
}


void imprimirPorTipo(PArv arv, char tipo) { // Dado um tipo(caractere), imprime todos os elementos em ordem crescente
  if (arv != NULL) {
    imprimirPorTipo(arv->esq, tipo);
    if (arv->tipo == tipo) {
      printf("%.1f ", arv->area);
    }
    imprimirPorTipo(arv->dir, tipo);
  }
}

void liberar(PArv arv){ // Libera a memória alocada
  if(arv == NULL){
    return;
  }
  liberar(arv->esq);
  liberar(arv->dir);
  free(arv);
}

int main(void) {
  char c, c1;
  float n1, n2;
  PArv arv = NULL;
  while(c != 'F'){ // Enquanto c for diferente de F
    scanf(" %c", &c);
    c = toupper(c); // Torna c maiúsculo
    switch(c){
      case 'R':
        scanf("%f %f", &n1, &n2);
        inserir(&arv, n1*n2, 'R'); // Insere retângulo
        break;
      case 'T':
        scanf("%f %f", &n1, &n2);
        inserir(&arv, (n1*n2)/2, 'T'); // Insere triângulo
        break;
      case 'C':
        scanf("%f", &n1);
        inserir(&arv, M_PI*n1*n1, 'C'); // Incere círculo
        break;
      case 'E':
        scanf(" %c %f", &c1, &n1); // Define o elemento e o tamanho máximo da área que deseja apagar
        c1 = toupper(c1); // Torna c1 maiúsculo
        remover(&arv, n1, c1); // Remove o(s) elemento(s)
        break;
      case 'I':
        if(Busca_Arv(arv, 'C') == 1){ // Se tiver círculo, imprime
          printf("circulo\n");
          imprimirPorTipo(arv, 'C');
          printf("\n");
        }
        if(Busca_Arv(arv, 'R') == 1){ // Se tiver retângulo, imprime
          printf("retangulo\n");
          imprimirPorTipo(arv, 'R');
          printf("\n");
        }
        if(Busca_Arv(arv, 'T') == 1){ // Se tiver triângulo, imprime
          printf("triangulo\n");
          imprimirPorTipo(arv, 'T');
          printf("\n");
        }
        printf("\n");
        break;
      }
  }
  return 0;
}
