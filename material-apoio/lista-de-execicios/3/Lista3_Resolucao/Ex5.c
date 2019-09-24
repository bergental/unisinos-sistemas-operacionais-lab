#include<stdio.h>
#include<string.h>

void imprimir_hex(char *palavra) {
  for(int i=strlen(palavra)-1;i>=0;i--){
    printf("%x ", (int) palavra[i]);
  }
}

int main(){
	char palavra[128];

	printf("Digite a palavra:");
	scanf("%[^\n]s", palavra);
	imprimir_hex(palavra);

	return(0);
}
