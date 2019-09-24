#include<stdio.h>
int main(){

	typedef struct Retangulo {
		int l1, l2;
	} forma_retangulo;

	forma_retangulo meuRetangulo;
	meuRetangulo.l1 = 10;
	meuRetangulo.l2 = 10;

	printf("Lado 1 do retângulo: %.d \n", meuRetangulo.l1);
	printf("Lado 2 do retângulo: %.d \n", meuRetangulo.l1);
	printf("Área do retângulo: %.d \n", meuRetangulo.l1 * meuRetangulo.l2);

	return(0);
}
