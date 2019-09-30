#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){   
	pid_t p = fork();					/* cria novo processo */
	int status = 0;

	if (p < 0) { 						/* ocorrencia de erro */
		fprintf(stderr, "Criação de novo processo falhou! \n");
		exit(-1);					/* terminacao de erro */
	} else if (p == 0) {	 				/* processo filho */
		printf("Iniciando a execução do filho... \n"); 
		printf("Sou o filho - PPID = %d PID = %d \n", getppid(), getpid());
		printf("PID do filho (no filho): %d \n", p);						
		execlp("/bin/ls", "ls", "-l", NULL);			/* atribui novo programa ao filho */
		printf("Filho com parada de execução forçada! \n"); 
		exit(-1);
	} else { 						/* processo pai */
		printf("Pai aguardando o filho terminar... \n"); 
		printf("Sou o pai - PPID = %d PID = %d \n", getppid(), getpid());
		printf("PID do filho (no pai): %d \n", p);						
		wait(&status);	
		printf("Pai terminou! PID: %d PPID (PID do Pai): %d. \nStatus de terminação do filho = %s \n", getpid(), getppid(), (WEXITSTATUS(status) == 0 ? "Sucesso" : "Falha"));
		printf("Filho completou a execução! \n");	
		exit(0);					/* terminacao de sucesso */
	}	
}
