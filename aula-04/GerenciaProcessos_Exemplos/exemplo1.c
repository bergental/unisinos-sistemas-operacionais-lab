#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){

	int minhaVar = 100;

	for(int i=0;i<argc;i++){
		printf("argv[%d]: %s\n", i, argv[i]);
	}

	printf("\nMinha var: %d", minhaVar);

	exit(0);
	
}
