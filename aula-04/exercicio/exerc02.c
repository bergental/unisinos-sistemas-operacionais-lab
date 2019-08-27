#include<stdio.h>

void repete(char *palavra, int count) {
 for(int i = 1; i <= count; i++) {
  printf("#%d '%s'\n", i, palavra);
 }
}

int main(int argc, char *argv[]){
 int count = 0;
 char *palavra = argv[1]; 
 printf("\nInforme quantas vezes quer que repita a palavra: ");
 scanf("%d", &count);
 repete(palavra, count);
}
