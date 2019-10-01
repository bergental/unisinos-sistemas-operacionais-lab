#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t pid;		
	int status;
    switch(fork()) {
        case -1:
            perror("Erro no fork\n"); 
            exit(-1);
            break;
        case 0:
            execlp("date", "date", NULL);
            exit(0);
            break;
        default:
            pid = wait(&status); /* Espera filho terminar.*/
            printf("Isento do imposto de renda!\n");
            exit(0);
            
        }
}