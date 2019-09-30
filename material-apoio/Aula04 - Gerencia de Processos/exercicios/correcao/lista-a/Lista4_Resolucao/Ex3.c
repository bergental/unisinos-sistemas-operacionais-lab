#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void repeat(int n, char *word) {
  int pp = getppid();
  int p = getpid();

  for(int i=0; i<n; i++) {
    printf("#%d PPID = %d PID = %d '%s' \n", i+1, pp, p, word);
  }
}

int main(int argc, char *argv[]) {
	int nro;

 	if(argc == 2) {
		printf("Digite o número de repetições: \n");
    		scanf("%d", &nro);
		switch(fork()) {
			case -1:
				perror("Erro no fork! \n");
				exit(-1);
				break;
			case 0:
				printf("Filho executando... \n");
				repeat(nro, argv[1]);
				exit(0);
				break;
			default:
				printf("Pai executando... \n");
				printf("Pai terminou! PID: %d PPID (PID do Pai): %d. \n", getpid(), getppid());
			}
    	} else {
		printf("Número de argumentos inválido! Deve ser digitado um parâmetro na linha de comando!\n");
	}
  return 0;
}
