#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<errno.h>
#include<unistd.h>

#define NUM_THREADS 10
#define NUM_MSG 10
#define SLEEP_TIME 2

struct ThreadAttributes
{
 char* name;
 pthread_t parent;
};


//Função a ser executada como Thread
void *PrintHello(void *param) {
	int i;			//contador local
	struct ThreadAttributes* who; 		//ponteiro de char
	who = (struct ThreadAttributes*) param;	//nome e thread pai passado pelo argumento

	printf("Iniciando execução da thread (%s): \n", who->name);

	for (i=0; i<NUM_MSG; i++) {
		sleep(SLEEP_TIME);
		printf("Ola! Sou eu, %s! (id: %ld | parentid: %ld)\n", who->name, pthread_self(), who->parent);
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

	pthread_t tids[NUM_THREADS];	//array de threads id
	struct ThreadAttributes tparents[NUM_THREADS];
	int n, te;			//contador local, retorno erro create thread
	char* names[NUM_THREADS] = { "Zoio", "Zeus", "Replay", "Meggie", "Margo", "Zangado", "Zica", "Pequeno", "Thor", "Bela" };		//array de nomes

	for (n=0; n<NUM_THREADS; n++) {
		tparents[n].name = names[n];
		tparents[n].parent = pthread_self();
		printf("Lançando thread (%s): %d \n",tparents[n].name, n);
		te = pthread_create(&tids[n],NULL, &PrintHello, (void *) &tparents[n]); //criação da thread
		if (te) {
			errno = te;
			perror("Falha na criação da thread");
			exit(EXIT_FAILURE);
		}
	}
	pthread_exit(NULL);
}
