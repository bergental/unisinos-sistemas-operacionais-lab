#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void load_firefox(char url[])
{
	if (!url || strlen(url) == 0) {
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
		execlp("/usr/bin/firefox", "--new-window", url, NULL);
		printf("Filho com parada de execução forçada! \n"); 
		exit(-1);
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

int main()
{   
	char url[] = "https://www.google.com/";
	load_firefox(url);
	return 0;
}

