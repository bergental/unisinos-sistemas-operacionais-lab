#include <stdio.h>
#include <string.h>

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

int to_int(char c) { return c; }

void imprime_bytes_hex(int num) {
 char c[10] = {};
 sprintf(c, "%d", num);
 for(int i = sizeof(c); i >= 0; --i) {
  printf("%x\n", to_int(c[i]));
 }
}

int main(){
 int caracteres;
 printf("Digite seu inteiro: ");
 scanf("%d", &caracteres);
 
 imprime_bytes_hex(caracteres);

 return 0;
}
