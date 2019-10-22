#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){

	int fd[2];		//declaração do descritor

	if (pipe(fd) != 0){	//execução do pipe
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	switch (fork()){	//execução do fork
	case -1:
		perror("fork");
		exit(EXIT_FAILURE);
		break;
	case 0:					//processo filho
		close(fd[0]);			//fecha entrada do processo filho - filho vai "falar"
		dup2(fd[1], STDOUT_FILENO);	//duplica a saida do processo filho, atribuindo a saida padrão STDOUT_FILENO
		close(fd[1]);			//fecha a saida original
		execlp("ls", "ls", NULL);	//executa o comando ls que gera o output
		perror("exec LS");
		break;
	default:				//processo pai
		close(fd[1]);			//fecha a saida do processo pai - pai vai "escutar"
		dup2(fd[0], STDIN_FILENO);	//duplica a entrada do processo pai, para entrada padrão - STDIN_FILENO
		close(fd[0]);			//fecha a entrada original para redirecionar para a entrada padrão
		execlp("wc", "wc", NULL);	//executa o comando wc com entrada para STDIN
		perror("exec WC");
		break;
	}
	exit(EXIT_SUCCESS);
}
