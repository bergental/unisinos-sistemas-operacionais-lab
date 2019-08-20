#include <stdio.h>

int main(){
 char caracteres[128];
 int i = 0;
 printf("Digite seu texto: ");
 scanf("%[^\n]s", caracteres);
 
 while (caracteres[i] != '\0' && i < 128) {
  printf("%c\n", caracteres[i++]);
 }

 return 0;
}
