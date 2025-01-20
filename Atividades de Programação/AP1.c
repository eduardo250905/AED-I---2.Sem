#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define Tam 256

void cont_letras(char *frase, int *letras){
  for(int i=0; i < strlen(frase); i++){
    char l = frase[i];
    if(isalpha(l)){
      l = toupper(l);
      letras[l - 'A']++;
    }
  }
}

int main(){
  char frase[256];
  int letras[26] = {0};
  printf("Digite o string: ");
  scanf("%[^\n]", frase);
  cont_letras(frase, letras);
  for(int i=0; i < 26; i++){
    if(letras[i] != 0){
      printf("%c  %d\n", 'A' + i, letras[i]);
    }
  }
}
