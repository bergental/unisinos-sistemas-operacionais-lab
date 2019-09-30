#include<stdio.h>

int main(int argc, char *argv[]){
 int count = 0;
 char *palavra = argv[1]; 
 printf("\nInforme quantas vezes quer que repita a palavra: ");
 scanf("%d", &count);
 for(int i = 1; i <= count; i++) {
  printf("#%d '%s'\n", i, palavra);
 }
}
