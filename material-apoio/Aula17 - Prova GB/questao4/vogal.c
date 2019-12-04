#include <stdio.h>
#include <stdlib.h>
#include<fcntl.h>
#include<unistd.h>

void gravararquivo(char* palavragravar){
	int fd;

	fd = open("texto_armazenado.txt", O_CREAT | O_RDWR, 0777); 

	if (fd == -1) {
		perror("Problema na criação do arquivo!");
		exit(EXIT_FAILURE);
	}

	if (write(fd, palavragravar, 1) != 5) perror("Erro na escrita do arquivo!");

	printf("Arquivo criado e gravado!\n");

	close (fd);
}

void filtrarvogal(char* palavrafiltrar){
	gravararquivo(palavrafiltrar);
}

int main(int argc, char* argv[]) {
	if (argc < 2){
		printf("Não recebido o parâmetro esperado\n");
		exit(-1);
	}

	filtrarvogal(argv[1]);

	return 0;
}
