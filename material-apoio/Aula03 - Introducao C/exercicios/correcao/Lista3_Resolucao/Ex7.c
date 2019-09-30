#include<stdio.h>
int main(){

	char *minhaString1 = "Exemplo de String inicializada em C";
	char minhaString2 [100] = "Exemplo de String inicializada em C";
	char minhaString3 [100] = {'E','x','e','m','p','l','o'};
	char minhaString4 [] = "Exemplo de String inicializada em C";
	char minhaString5 [100] = "Exemplo de String cortada\0 String inicializada em C";

	printf("String 1: %s \n", minhaString1);
	printf("String 2: %s \n", minhaString2);
	printf("String 3: %s \n", minhaString3);
	printf("String 4: %s \n", minhaString4);
	printf("String 5: %s \n", minhaString5);

	return(0);
}
