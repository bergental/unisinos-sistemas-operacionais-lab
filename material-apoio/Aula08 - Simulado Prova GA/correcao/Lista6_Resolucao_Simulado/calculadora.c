#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void soma(int val1, int val2){
	printf("Resultado: %d\n", val1 + val2);
}

void subtracao(int val1, int val2){
	printf("Resultado: %d\n", val1 - val2);
}

void multiplicacao(int val1, int val2){
	printf("Resultado: %d\n", val1 * val2);
}

void divisao(int val1, int val2){
	printf("Resultado: %d\n", val1 / val2);
}

int main() 
{
	int valor1, valor2;
	char opcao;

	while(opcao!=101){
		printf("\n****** MENU ******\n");
		printf("a - Adição\n");
		printf("b - Subtração\n");
		printf("c - Multiplicação\n");
		printf("d - Divisão\n");
		printf("e - Sair\n");

		printf("Escolha a operação:");
		scanf("%c", &opcao);
		getchar();

		if (opcao > 96 && opcao < 101){
			printf("Digite o primeiro valor: ");
			scanf("%d", &valor1);
			getchar();
			printf("Digite o segundo valor: ");
			scanf("%d", &valor2);
			getchar();
		}else if(opcao == 101){
			printf("Saindo da calculadora...\n");			
			return 1;
		}

		switch (opcao)
		{
			case 97:
				soma(valor1, valor2);
			break;

			case 98:
				subtracao(valor1, valor2);
			break;

			case 99:
				multiplicacao(valor1, valor2);
			break;

			case 100:
				divisao(valor1, valor2);
			break;

			default:
				printf("Valor inválido, digite A, B, C, D ou E!\n");
		}
	}
	return 0;
}

