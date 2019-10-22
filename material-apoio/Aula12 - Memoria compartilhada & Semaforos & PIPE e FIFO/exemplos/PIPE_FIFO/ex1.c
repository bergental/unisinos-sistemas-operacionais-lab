#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define MAXLINE 4096		//tamanho do buffer

int main(){
	int tam;		//tamanho do conteúdo lido
	int fd[2];		//declaração dos descritores
	char line[MAXLINE];	//declaração da variável de buffer

	if (pipe(fd) != 0){	//execução do pipe (sucesso==0 / insucesso !=0)
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	switch (fork()){	//fork para criação do processo filho
	case -1:		//erro de fork
		perror("fork");
		exit(EXIT_FAILURE);
		break;
	case 0:			//processo filho - fork
		close(fd[0]);	//fechamento da porta de entrada do pipe (filho vai "falar")
		write(fd[1],"Hello World\n",12);	//escrita do texto para porta de saida do pipe
		break;
	default:		//processo pai
		close(fd[1]);	//fechamento da porta de escrita (pai vai "escutar")
		tam=read(fd[0],line,MAXLINE);	//leitura da porta de entrada - escrita para o buffer "line", contendo tamanho MAXLINE
						//tam tem o real tamanho do texto recebido
		write(STDOUT_FILENO, line, tam);//pai escreve na saída padrão STDOUT_FILENO, texto "line" recebido pelo pipe
		break;
	}
	exit(EXIT_SUCCESS);
}
