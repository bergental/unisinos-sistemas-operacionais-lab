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
     if(c[i] != '\0') {
        /*int a = c[i] - '0';
        char hex[5];
        sprintf(hex, "%x", a);
        printf("%d:%s\n", a, hex);*/
        printf("%c:%x\n", c[i], to_int(c[i]));
     }
 }
}

void imprime_bytes_bin(int num) {
    printf("%d:", num);
    int bits = 8;
    int vetor[bits];
    int i = bits -1;
    int j = i;
    if(num < 0) {
        printf("Não definido\n");
        return;
    }else if(num >= 2) {
        while(num/2 > 0) {
            vetor[i] = num % 2;
            num /= 2;
            --i;
            --j;
        }

        for(i = 0; i < j; i++){
            vetor[i] = 0;
        }

        vetor[j] = 1;
    } else if(num == 1) {
        for(i = 0; i < j; i++){
            vetor[i] = 0;
        }
        vetor[i] = 1;
    } else {
        for(i = 0; i < bits; i++){
            vetor[i] = 0;
        }
    }
    for(i = 0; i < bits; i++){
        printf("%d", vetor[i]);
    }
    printf("\n");
}

void imprime_bytes_bin_loop(int num) {
 char c[10] = {};
 sprintf(c, "%d", num);
 for(int i = sizeof(c); i >= 0; --i) {
     if(c[i] != '\0') {
         int a = c[i] - '0';
         imprime_bytes_bin(a);
     }
 }
}

int main(){
 int caracteres;
 printf("Digite seu inteiro: ");
 scanf("%d", &caracteres);
 
 imprime_bytes_bin_loop(caracteres);

 return 0;
}
