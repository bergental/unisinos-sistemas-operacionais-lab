#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(){

	int fd;

	//fd = open("arquivo1.txt", O_RDWR);
	//fd = open("arquivo1.txt", O_CREAT, S_IRUSR|S_IWUSR);
	//fd = open("arquivo1.txt", O_CREAT | O_RDWR, S_IRUSR|S_IWUSR);
	fd = open("arquivo1.txt", O_CREAT | O_RDWR, 0600);
	if (fd == -1) perror("Falha no open()");	
	return(0);
}

