#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int status;
	int valor = 0;
	pid_t pid;

	switch(fork()){
	case -1:
		perror("Erro no fork\n");
		exit(-1);
		break;
	case 0:
		printf("Filho: Meu PID = %d, PPID = %d\n", getpid(), getppid());
		printf("Digite um valor inteiro: ");
		scanf("%d",&valor);
		if(valor<0 || valor> 10) exit(10);
		else if (valor >=0 || valor <= 10) exit(0);
		break;
	default:
		printf("Pai: Meu PID = %d, PPID = %d\n", getpid(), getppid());
		pid = wait(&status);
		printf("Pai: Filho (PID = %d) terminou. \nStatus de terminação do filho = %s \n", pid, (WEXITSTATUS(status)==0 ? "Sucesso!" : "Falha!"));
	}
	printf("PID %d terminando...\n", getpid());
	sleep(5);

	return 0;
}
