// Eduardo Lopes Arrais de Oliveira       RA: 168804

#include <stdio.h>
#include <stdlib.h>

typedef struct strNO{
  int valor;
  int coluna;
  struct strNO* prox;
}NO; // Define struct NO, com o valor e a coluna em que o nó se localiza, além de um ponteiro para a própria struct no

typedef NO* PNO; 

typedef struct {
  PNO* A;
  int linhas;
  int colunas;
}MATRIZ; // Define struct matriz, com o numero de linhas, de colunas e um ponteiro de um ponteiro de no

typedef MATRIZ* PM;

void InicializaMatriz(PM m, int l, int c){ // Função de incializar a matriz
  int i;
  m->linhas = l; // Atribui o número de linhas
  m->colunas = c; // Atribui o número de colunas
  m->A = (PNO*) malloc(l * sizeof(PNO)); // Aloca espaço para todas as listas que representarão cada linha
  for(i=0; i<l; i++){
    m->A[i] = NULL; // Inicializa a lista(linha) nula
  }
}

int AtualizaMatriz(PM m, int l, int c, int v){ // Função para adicionar as bombas e atualizar os números da matriz
  if(l < 0 || l >= m->linhas || c < 0 || c >= m->colunas){ // Se o valor das linhas ou colunas for inválido
    return 0; // retorna 0
  }
  PNO ant = NULL; // Ponteiro ant que apontará para o anterior de um outro elemento
  PNO atual = m->A[l]; // Ponteiro atual apontando para o primeiro elemento da linha
  while(atual != NULL && atual->coluna < c){ // Enquanto existem elementos na lista e a coluna atual é menor do que a coluna desejada
    ant = atual; // Atualiza o valor do anterior para o atual
    atual = atual->prox; // Atualiza o valor do atual para o próximo
  }
  if(atual != NULL && atual->coluna == c){ // Se existe um elemento no local
      if(atual->valor != -1){ // Se não existir uma bomba naquele local
        if(v == -1){ // Se queremos adicionar uma bomba
          atual->valor = -1; // Adiciona a bomba
        }
        else{
          atual->valor += 1; // Senão, o valor sofre incrementação de uma unidade
        }
      } 
      else{ 
        return 0; // Se já tiver uma bomba no local, retorna 0
      }
    }
  else{
    PNO novo = (PNO) malloc(sizeof(NO)); // Se não existe um elemento no espaço desejado, cria um novo no
    novo->coluna = c;  // Atribui o valor da coluna
    if(v == -1){ // Se queremos adicionar uma bomba
      novo->valor = -1; // Adiciona a bomba no novo nó
    } else{ 
      novo->valor = 1; // Senão, o valor será igual a 1
    }
    novo->prox = atual; // Proximo do novo recebe o atual
    if(ant == NULL){ // Se não existir um elemento anterior
      m->A[l] = novo; // Arranjo da linha aponta para o novo
    } else{
      ant->prox = novo; // Se não, o próximo do anterior será o novo
    }
  }
  return 1; // retorna 1 em caso de sucesso
}

void libera(PM m){
  PNO p; 
  int i;
  for(i=0; i<m->linhas; i++){ // Para cada linha
    for(p=m->A[i]; p!=NULL; ){ // Em todo elemento da linha
      m->A[i] = p->prox; // Arranjo da linha aponta para o próximo elemento
      free(p); // Libera a memória do elemento
      p = m->A[i]; // Reseta o valor de p para o próximo elemento
    }
  }
}

void Imprime(PM m){
  int l, c;
  PNO p;
  for(l=0; l<m->linhas; l++){ // Para cada linha
    p = m->A[l];
    for(c=0; c<m->colunas; c++){ // Para cada coluna
      if(p == NULL || p->coluna != c){ // Se não existir nada naquela posição
        printf("0 "); // Imprime 0
      }
      else{ // Se existir
        if(p->valor == -1){ // Se for uma bomba
          printf("X "); // Imprime 'X'
        }
        else{
          printf("%d ", p->valor); // Se não, imprime o valor
        }
        p = p->prox; 
      }
    }
    printf("\n");
  }
}

int main(void) {
  int lin, col, B, i, l, c, aux, j, k, linha, coluna;
  PM matriz;
  scanf("%d %d", &lin, &col); // Lê o tamanho da matriz
  if(lin < 0 || lin > 100 || col < 0 || col > 100){
    return -1; // Se o valor da linha ou coluna for inválido, sai do programa
  }
  scanf("%d", &B); // Lê o número de bombas
  if(B<0 || B>60){
    return -1; // Se o valor for inválido, sai do programa
  }
  matriz = (PM) malloc(sizeof(MATRIZ));
  InicializaMatriz(matriz, lin, col); // Inicializa a matriz
  for(i=0; i<B; i++){ // Repete B vezes
    scanf("%d %d", &l, &c); // Lê a localização das bombas
    aux = AtualizaMatriz(matriz, l, c, -1); // Tenta adicionar a bomba naquela localização e atribui a variavel aux se foi possível ou não
    if(aux == 1){ // Se a bomba foi adicionada
      linha = l-1; // Volta para a linha anterior
      coluna = c-1; // Volta para a coluna anterior
      for(j=0; j<3; j++){
        for(k=0; k<3; k++){
          AtualizaMatriz(matriz, linha, coluna, 1); // Atualiza os números ao redor da bomba
          coluna += 1; // Passa para a próxima coluna
        }
        linha += 1; // Passa para a próxima linha
        coluna = c-1; // Reseta o valor da coluna
      }
    }
  }
  Imprime(matriz);
  libera(matriz);
  return 0;
}
