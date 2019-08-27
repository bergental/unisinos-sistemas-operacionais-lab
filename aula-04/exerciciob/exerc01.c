#include<stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void load_firefox(char url[]) {
 execlp("firefox", "firefox", "--new-window ", NULL);			/* atribui novo programa ao filho */
}

int main(int argc, char *argv[]){

 pid_t p = fork();					/* cria novo processo */
	int status = 0;

	if (p < 0) { 						/* ocorrencia de erro */
		fprintf(stderr, "Criação de novo processo falhou! \n");
		exit(-1);					/* terminacao de erro */
	} else if (p == 0) {	 				/* processo filho */
		printf("Iniciando a execução do filho... \n"); 
		printf("Sou o filho - PPID = %d PID = %d \n", getppid(), getpid());
		printf("PID do filho (no filho): %d \n", p);
		char params[] = {"firefox","--new-window","http://www.google.com"};					
		execv("firefox", params);			/* atribui novo programa ao filho */
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
