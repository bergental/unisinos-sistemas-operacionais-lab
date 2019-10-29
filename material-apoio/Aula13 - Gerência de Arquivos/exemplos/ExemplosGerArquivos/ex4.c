#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(void) {

	int fd;
	char nome[50];
	char buf1[10] = "Ola Mundo!";
	
	printf("Nome do arquivo a criar:");
	scanf("%49s",nome);

	fd = open(nome, O_CREAT | O_RDWR, S_IRGRP | S_IWGRP | S_IRUSR | S_IWUSR); //0660

	if (fd == -1) {
		perror("Problema na criação!");
		exit(EXIT_FAILURE);
	}

	if (write(fd, buf1, 10) != 10) perror("escrita buf1");

	printf("Arquivo Criado.\n");

	close (fd);

	return (0);
}
