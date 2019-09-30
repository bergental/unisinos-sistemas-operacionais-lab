#include<stdio.h>
#include<string.h>

void imprimir_decimal(char *palavra) {
  for(int i=0;i<strlen(palavra);i++){
    printf("%d ", (int) palavra[i]);
  }
}

int main(){
	char palavra[128];
	
	printf("Digite a palavra:");
	scanf("%[^\n]s", palavra);
	imprimir_decimal(palavra);

	return(0);
}
