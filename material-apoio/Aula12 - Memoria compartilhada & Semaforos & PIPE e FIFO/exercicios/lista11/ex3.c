#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define MAXLINE 4096		//tamanho do buffer

int main(){
	int tam;		//tamanho do conteúdo lido
	char line[MAXLINE];	//declaração da variável de buffer
	int fd[2];		//declaração do descritor

	printf("Criando o PIPE\n");
	if (pipe(fd) != 0){	//execução do pipe
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	printf("PIPE criado\n");

	printf("Criando processo filho\n");
	switch (fork()){	//execução do fork
	case -1:
		perror("fork");
		exit(EXIT_FAILURE);
		break;
	case 0:					//processo filho
		//printf("Processo filho criado\n");
		//printf("Processo filho fechando a porta de entrada do pipe\n");
		close(fd[0]);			//fecha entrada do processo filho - filho vai "falar"
		printf("Processo filho duplicando saída padrão STDOUT_FILENO\n");
		dup2(fd[1], STDOUT_FILENO);	//duplica a saida do processo filho, atribuindo a saida padrão STDOUT_FILENO
		printf("Processo filho fechando a porta de sáida original do pipe\n");
		close(fd[1]);			//fecha a saida original
		printf("Processo filho executando date e jogando o resultado na saída STDOUT_FILENO\n");
		execlp("date", "date", NULL);	//executa o comando ls que gera o output
		perror("exec DATE");
		break;
	default:				//processo pai
		printf("Processo pai fechando a porta de sáida do pipe\n");
		close(fd[1]);			//fecha a saida do processo pai - pai vai "escutar"
		//printf("Processo pai duplicando entrada padrão STDIN_FILENO\n");
		//dup2(fd[0], STDIN_FILENO);	//duplica a entrada do processo pai, para entrada padrão - STDIN_FILENO
		//printf("Processo pai fechando a porta de entrada original do pipe\n");
		//close(fd[0]);			//fecha a entrada original para redirecionar para a entrada padrão
		printf("Processo pai pegando o tamanho do texto escrito na porta de saída do pipe\n");
		tam=read(fd[0],line,MAXLINE);	//leitura da porta de entrada - escrita para o buffer "line", contendo tamanho MAXLINE
		printf("Processo pai mostrando o retorno do date executado no processo filho\n");
		write(STDOUT_FILENO, line, tam);//pai escreve na saída padrão STDOUT_FILENO, texto "line" recebido pelo pipe
		//perror("exec ECHO");
		break;
	}
	exit(EXIT_SUCCESS);
}
