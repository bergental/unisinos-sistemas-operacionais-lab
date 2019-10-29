#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char *argv[]) {

	int file1;
	int file2;
    char *file1Name = (char*)argv[1];
    char *file2Name = (char*)argv[2];

    file1 = open(file1Name, O_RDONLY);

    if(file1 == -1) {
        perror("O primeiro arquivo não existe!");
        return -1;
    } else {
        printf("Arquivo(%s) existe!\n", file1Name);
        int sz = lseek(file1, 0L, SEEK_END);
        char conteudo[sz];
        lseek(file1, 0L, SEEK_SET);
        read(file1, conteudo, sizeof(conteudo));
        file2  = open(file2Name, O_CREAT | O_RDWR, S_IRGRP | S_IWGRP | S_IRUSR | S_IWUSR); //0660
        if(file2 == -1) {
            perror("Não conseguir abrir ou criar o segundo arquivo!");
            close(file1);
            return -1;
        }
        lseek(file2, 0L, SEEK_END);
        int count = 0;
        char tmp[20] = {};
        for (size_t i = 0; i < sizeof(conteudo); i++) {
            if(conteudo[i] != '\n' && conteudo[i] != ' ' && conteudo[i] != '\0') {
                tmp[count++] = conteudo[i];
            }
            if(count == 20) {
                if (write(file2, tmp, count) != count) {
                    perror("Erro ao escrever no segundo arquivo");
                    close(file1);
                    close(file2);
                }
                count = 0;
                memset(tmp, 0, 20);
            }
        }
        if(count > 0) {
            if (write(file2, tmp, count) != count) {
                perror("Erro ao escrever no segundo arquivo");
                close(file1);
                close(file2);
            }
            count = 0;
            memset(tmp, 0, 20);
        }
        memset(conteudo, 0, sz);
        sz = lseek(file2, 0L, SEEK_END);
        memset(conteudo, 0, sz);
        lseek(file2, 0L, SEEK_SET);
        read(file2, conteudo, sizeof(conteudo));
        printf("Foi grava no arquivo(%s) o conteudo:%s\n", file2Name, conteudo);
    }

	/*fd = open(nome, O_CREAT | O_RDWR, S_IRGRP | S_IWGRP | S_IRUSR | S_IWUSR); //0660

	if (fd == -1) {
		perror("Problema na criação!");
		exit(EXIT_FAILURE);
	}

	if (write(fd, buf1, sizeof(buf1)) != 10) perror("escrita buf1");

	printf("Arquivo Criado.\n");*/

	close (file1);
	close (file2);

	return (0);
}
