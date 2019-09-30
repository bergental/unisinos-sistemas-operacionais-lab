#include <stdio.h>

void imprime_caracteres(char c[]) {
 int i = 0;
 while (c[i] != '\0') {
  printf("%c\n", c[i++]);
 }
}

void imprime_bytes_dec(char c[]) {
 int i = 0;
 while (c[i] != '\0') {
  char tmp = c[i++];
  printf("%c:%d\n", tmp, tmp);
 }
}

int main(){
 char caracteres[128] = {};
 printf("Digite seu texto: ");
 scanf("%[^\n]s", caracteres);
 
 imprime_bytes_dec(caracteres);

 return 0;
}
