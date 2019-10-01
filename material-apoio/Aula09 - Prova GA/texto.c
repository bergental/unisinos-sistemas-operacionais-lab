#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){

    int vogais = 0, consoantes = 0;
    for(int i=1;i<argc;i++){
        char *palavra = argv[i];
		//printf("argv[%d]: %s\n", i, palavra);
        for (int j=0;palavra[j]!='\0';j++) 
        {
            char p = palavra[j];
            if (p == 'a' || p == 'e' || p == 'i' || p == 'o' || p == 'u')
                vogais++;
            else 
                consoantes++;
        }
    }

    printf("A quantidade de palavras é: %d \n", argc-1);
    printf("A quantidade de vogais é: %d \n", vogais);
    printf("A quantidade de consoantes é: %d \n", consoantes);

	exit(0);
	
}