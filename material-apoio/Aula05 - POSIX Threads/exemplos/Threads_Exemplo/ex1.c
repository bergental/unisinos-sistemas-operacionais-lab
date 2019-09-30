#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<errno.h>
#include<unistd.h>

#define NUM_THREADS 3
#define NUM_MSG 5
#define SLEEP_TIME 1

//Função a ser executada como Thread
void *PrintHello(void *param) {
	int i;			//contador local
	char *who; 		//ponteiro de char
	who = (char*) param;	//nome passado pelo argumento

	printf("Iniciando execução da thread (%s): \n", who);

	for (i=0; i<NUM_MSG; i++) {
		sleep(SLEEP_TIME);
		printf("Ola! Sou eu, %s! (id: %ld)\n", who, pthread_self());
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

	pthread_t tids[NUM_THREADS];	//array de threads id
	int n, te;			//contador local, retorno erro create thread
	char* names[NUM_THREADS] = { "Joao", "Maria", "Jose" };		//array de nomes

	for (n=0; n<NUM_THREADS; n++) {
		printf("Lançando thread (%s): %d \n",names[n], n);
		te = pthread_create(&tids[n],NULL, &PrintHello, (void *) names[n]); //criação da thread
		if (te) {
			errno = te;
			perror("Falha na criação da thread");
			exit(EXIT_FAILURE);
		}
	}
	pthread_exit(NULL);
}
