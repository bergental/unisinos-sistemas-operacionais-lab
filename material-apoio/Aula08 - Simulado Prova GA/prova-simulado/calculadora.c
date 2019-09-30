#include <stdio.h>

void soma() {
 int value1, value2;
 printf("Primeiro valor:\n");
 scanf("%d", &value1);
 getchar();
 printf("Segundo valor:\n");
 scanf("%d", &value2);
 getchar();
 int resultato = value1 + value2;

 printf("O resuldado da soma foi: %d\n", resultato);
}

void subtracao() {
 int value1, value2;
 printf("Primeiro valor:\n");
 scanf("%d", &value1);
 getchar();
 printf("Segundo valor:\n");
 scanf("%d", &value2);
 getchar();
 int resultato = value1 - value2;

 printf("O resuldado da subtração foi: %d\n", resultato);
}

void produto() {
 int value1, value2;
 printf("Primeiro valor:\n");
 scanf("%d", &value1);
 getchar();
 printf("Segundo valor:\n");
 scanf("%d", &value2);
 getchar();
 int resultato = value1 * value2;

 printf("O resuldado do produto foi: %d\n", resultato);
}

void divisao() {
 int value1, value2;
 printf("Primeiro valor:\n");
 scanf("%d", &value1);
 getchar();
 printf("Segundo valor:\n");
 scanf("%d", &value2);
 getchar();
 double resultato = (double) value1 / value2;

 printf("O resuldado do divisão foi: %.2f\n", resultato);
}

int opcoes() {
 char opcao;
 while (opcao != 'S' && opcao != 's') {
 //sprintf(&opcao, "%c", ' ');
 printf("A - Soma\n");
 printf("B - Subtração\n");
 printf("C - Produto\n");
 printf("D - Divisão\n");
 printf("S - Sair\n");
 //scanf("%[^\n]s", opcao);
 scanf("%[^\n]c", &opcao);
 //fflush(stdin);
 getchar();

 if(opcao == 'S' || opcao == 's') {
  return 0;
 } else if (opcao == 'A' || opcao == 'a') {
  soma();
 } else if (opcao == 'B' || opcao == 'b') {
  subtracao();
 } else if (opcao == 'C' || opcao == 'c') {
  produto();
 } else if (opcao == 'D' || opcao == 'd') {
  divisao();
 } else {
  printf("Opção inválida![%c]\n", opcao);
 }
 }
 return 0; 
}

int main(){
 
 return opcoes();
}
