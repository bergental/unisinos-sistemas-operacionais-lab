

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<sys/types.h>

void tratador(int signum){
	printf("Alarme gerado!\n");
    fflush(stdout);
}

int main(){
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &tratador;
	if(sigaction(SIGALRM, &sa, NULL) != 0){
		perror("Falha ao instalar tratador de sinal");
		exit(-1);
	}

	//agenda SIGALRM para daqui a 5 segundos
	if (alarm(5) < 0){
		perror("Falha ao agendar alarme");
	}	

	printf("O processo é eterno, enquanto dura...\n");

	//espera ocupada (busy-waiting) pelo alarme
	while(1);
	
	printf("Linha que nunca aparece...\n");

	return 0;
}




