#include<stdio.h>
#include<string.h>

void imprimir_caracter(char* palavraprint) {
  for(int i=0;i<strlen(palavraprint);i++){
    printf("%c\n", palavraprint[i]);
  }
}

int main(){
	char palavra[128];

	printf("Digite a palavra:");
	scanf("%[^\n]s", palavra);
	imprimir_caracter(palavra);

	return(0);
}
