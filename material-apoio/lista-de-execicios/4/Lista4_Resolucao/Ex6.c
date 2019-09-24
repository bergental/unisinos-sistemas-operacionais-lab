#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void repeat(int n, char *word) {
  int pp = getppid();
  int p = getpid();

  for(int i=0; i<n; i++) {
    printf("#%d PPID = %d PID = %d '%s' \n", i+1, pp, p, word);
    sleep(1);
  }
}

int main(int argc, char *argv[]) {
	int nro;
	int status;

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
				if(nro<=10 && nro>0){ 
					repeat(nro, argv[1]);
					exit(0);
				}
				exit(13);
				break;
			default:
				printf("Pai executando... \n");
				wait(&status);							
				printf("Pai terminou! PID: %d PPID (PID do Pai): %d. \nStatus de terminação do filho = %s \n", getpid(), getppid(), (WEXITSTATUS(status) == 0 ? "Sucesso" : "Falha"));
			}
    	} else {
		printf("Número de argumentos inválido! Deve ser digitado um parâmetro na linha de comando!\n");
	}
  return 0;
}
