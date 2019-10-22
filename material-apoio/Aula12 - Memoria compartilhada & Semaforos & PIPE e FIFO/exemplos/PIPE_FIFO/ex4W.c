#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(){

	int fd;					//declaração do descritor
	char buf1[] = "texto escrito no FIFO\n";	//buffer 1

	if(mkfifo("meuFIFO2", 0777) != 0) perror("Erro FIFO");	//criação do FIFO (0==sucesso)

	fd = open("meuFIFO2", O_RDWR, S_IRUSR|S_IWUSR);		//abertura do FIFO
	if (fd == -1) perror("Falha no open()");	

	if (write(fd, buf1, 22) != 22) perror("erro escrita buf1");	//escrita no FIFO

	close(fd);			//fechar descritor - desalocar recurso SO

	return(0);
}
