#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<sys/types.h>

char* palavra = "";

void contarDigito(){
	int i, contador = 0;

	printf("\nSinal USR2 recebido! \n");

	for (i=0;palavra[i]!='\0';i++) 
	{
		if (palavra[i] == '0' || palavra[i] == '1' || palavra[i] == '2' || palavra[i] == '3' || palavra[i] == '4' || palavra[i] == '5' || palavra[i] == '6' || palavra[i] == '7' || palavra[i] == '8' || palavra[i] == '9')
			contador++;
	}
	printf("A quantidade de digitos é: %d \n", contador);
}

void contarVogal(){
	int i, contador = 0;

	printf("\nSinal USR1 recebido! \n");

	for (i=0;palavra[i]!='\0';i++) 
	{
		if (palavra[i] == 'a' || palavra[i] == 'e' || palavra[i] == 'i' || palavra[i] == 'o' || palavra[i] == 'u')
			contador++;
	}
	printf("A quantidade de vogais é: %d \n", contador);
}

void exibirMensagem(){
	printf("\nSinal INT recebido! Para encerrar envie o sinal TERM \n");
}

void encerrarPrograma(){
	printf("\nEncerrando o programa... \n");
	sleep(5);
	exit(0);
}

void tratador(int signum){
	switch(signum){
		case SIGUSR1: contarVogal(); break;
		case SIGUSR2: contarDigito(); break;
		case SIGINT: exibirMensagem(); break;
		case SIGTERM: encerrarPrograma(); break;
	}
}

int main(int argc, char *argv[])
{
	sigset_t mask;

	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));

	sa.sa_handler = &tratador;

	if(sigaction(SIGUSR1, &sa, NULL) != 0){
		perror("Falha ao instalar tratador de sinal SIGUSR1");
		exit(-1);
	}
	if(sigaction(SIGUSR2, &sa, NULL) != 0){
		perror("Falha ao instalar tratador de sinal SIGUSR2");
		exit(-1);
	}
	if(sigaction(SIGINT, &sa, NULL) != 0){
		perror("Falha ao instalar tratador de sinal SIGINT");
		exit(-1);
	}
	if(sigaction(SIGTERM, &sa, NULL) != 0){
		perror("Falha ao instalar tratador de sinal SIGTERM");
		exit(-1);
	}

	sigfillset(&mask);
	sigdelset(&mask,SIGUSR1);
	sigdelset(&mask,SIGUSR2);
	sigdelset(&mask,SIGINT);
	sigdelset(&mask,SIGTERM);

	if (argc > 0){
		palavra = argv[1];
		printf("Meu PID = %d\n", getpid());
		printf("Palavra informada: %s \n", palavra);

		while(1){	
			printf("Envio o sinal SIGUSR1, SIGUSR2 ou SIGINT: ");
			fflush(stdout);
			sigsuspend(&mask);
		}
	}
	else{
		printf("A palavra não foi informada por linha de comando!\n");	
	}

	return 0;
}
