#include <stdio.h>

void imprime_caracteres(char c[]) {
 int i = 0;
 while (c[i] != '\0') {
  printf("%c\n", c[i++]);
 }
}

int main(){
 char caracteres[128] = {};
 printf("Digite seu texto: ");
 scanf("%[^\n]s", caracteres);
 
 imprime_caracteres(caracteres);

 return 0;
}
