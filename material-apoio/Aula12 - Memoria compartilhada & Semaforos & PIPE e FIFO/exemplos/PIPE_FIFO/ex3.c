#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(){

	int fd;				//declaração do descritor
	char buf1[] = "abcdefghij";	//buffer 1
	char buf2[] = "";		//buffer 2

	if(mkfifo("meuFIFO", 0777) != 0) perror("Erro FIFO");	//criação do FIFO (0==sucesso)

	fd = open("meuFIFO", O_RDWR, S_IRUSR|S_IWUSR);		//abertura do FIFO
	if (fd == -1) perror("Falha no open()");	

	if (write(fd, buf1, 10) != 10) perror("erro escrita buf1");	//escrita no FIFO
	if (read(fd, buf2, 10) != 10) perror("erro leitura buf2");	//leitura do FIFO
	
	printf("%s\n",buf2);		//escrita na saída padrão do texto lido do FIFO

	close(fd);			//fechar descritor - desalocar recurso SO

	return(0);
}
