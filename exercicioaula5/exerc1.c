// List 5 - exercicio 1

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<sys/types.h>

void tratador(int signum){
	printf("Recebido sinal %d\n", signum);
}

int main(){
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));

	sa.sa_handler = &tratador;

	printf("Meu PID = %d\n", getpid());

	if(sigaction(SIGTERM, &sa, NULL) != 0){
		perror("Falha ao instalar tratador de sinal");
		exit(-1);
	}

    /* Não é possivel capturar signal STOP */
	/*if(sigaction(SIGCONT, &sa, NULL) != 0){
		perror("Falha ao instalar tratador de sinal");
		exit(-1);
	}*/

	if(sigaction(SIGTERM, &sa, NULL) != 0){
		perror("Falha ao instalar tratador de sinal");
		exit(-1);
	}

	for(;;)	{}	//espera (busy-waiting) pelo sinal
	return 0;
}




