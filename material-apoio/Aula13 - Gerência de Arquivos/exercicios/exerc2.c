#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
 
#define MAX 255 

/*int getCountLines(char *string) {
    int count = 0;
    for (size_t i = 0; i < sizeof(string); i++)
        if(string[i] == '\n') count++;
    return count;
    
}*/

int main(void) {

	int fd;
	char nome[50];
    //char buf1[10];
	char buff[MAX];

	printf("Nome do arquivo:");
	scanf("%49s",nome);

    fd= open(nome, O_RDONLY);

    if(fd == -1) {
        printf("Arquivo não existe!\nCriando o arquivo...\n");
        fd = open(nome, O_CREAT | O_RDWR, S_IRGRP | S_IWGRP | S_IRUSR | S_IWUSR); //0660
        printf("Digite o texto a ser salvo no arquivo(Max 255):");
        fgets(buff, MAX, stdin);//limpa o stdin
        fgets(buff, MAX, stdin); 
        //scanf("%254s",buff);
        if (write(fd, buff, strlen(buff)) != strlen(buff)){
            perror("escrita buff");
            close(fd);
            return -1;
        }
        printf("Arquivo criado!\n");
    } else {
        printf("Arquivo já existe!\n");
        /*
        fseek(fd, 0L, SEEK_END);
        int sz = ftell(fd);
        */
        int sz = lseek(fd, 0L, SEEK_END);
        char conteudo[sz];
        lseek(fd, 0L, SEEK_SET);
        read(fd, conteudo, sizeof(conteudo));

        int countLines = 1;
        for (size_t i = 0; i < sizeof(conteudo); i++)
            if(conteudo[i] == '\n') countLines++;

        printf("Dados do Arquivo:%s\n", nome);
        printf("Tamanho:%d\n", sz);
        printf("Conteudo:%s\n", conteudo);
        printf("Número de Linhas:%d\n", countLines);
    }

	/*fd = open(nome, O_CREAT | O_RDWR, S_IRGRP | S_IWGRP | S_IRUSR | S_IWUSR); //0660

	if (fd == -1) {
		perror("Problema na criação!");
		exit(EXIT_FAILURE);
	}

	if (write(fd, buf1, sizeof(buf1)) != 10) perror("escrita buf1");

	printf("Arquivo Criado.\n");*/

	close (fd);

	return (0);
}
