#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void load_firefox(int argc, char *argv[])
{
	if (!argv[1] || strlen(argv[1]) == 0) {
		printf("URL não informada.\n");
		exit(-1);
	}
	pid_t p = fork();
	int status = 0;

	if (p < 0) {
		fprintf(stderr, "Criação de novo processo falhou! \n");
		exit(-1);
	} else if (p == 0) {
		printf("Iniciando a execução do filho... \n"); 
		printf("Sou o filho - PPID = %d PID = %d \n", getppid(), getpid());
		printf("PID do filho (no filho): %d \n", p);						
		for (int i = 1; i < argc; i++) {
			execlp("/usr/bin/firefox", "--new-window", argv[i], NULL);
		}
	} else {
		printf("Pai aguardando o filho terminar... \n"); 
		printf("Sou o pai - PPID = %d PID = %d \n", getppid(), getpid());
		printf("PID do filho (no pai): %d \n", p);						
		wait(&status);	
		printf("Pai terminou! PID: %d PPID (PID do Pai): %d. \nStatus de terminação do filho = %s \n", getpid(), getppid(), (WEXITSTATUS(status) == 0 ? "Sucesso" : "Falha"));
		printf("Filho completou a execução! \n");	
		exit(0);
	}	
}

void start_browser(int argc, char *argv[])
{
	load_firefox(argc, argv);
}

int main(int argc, char *argv[])
{ 
	start_browser(argc, argv);
}

