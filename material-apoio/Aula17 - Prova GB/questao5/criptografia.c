#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decifrar(char* palavradecifrar){
	int tam=0;
	tam = strlen(palavradecifrar);

	printf("Palavra decifrada: ");	
	for(int i=0;i<tam-2;i++){
		printf("%c", palavradecifrar[i]+3);	
	}
	
}

int main(int argc, char* argv[]) {
	char cripto[20];

	printf("Digite a palavra a ser decifrada: ");
	scanf("%s",cripto);
	decifrar(cripto);

	return 0;
}
