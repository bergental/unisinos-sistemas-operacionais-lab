#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<errno.h>
#include<unistd.h>

#define NUM_THREADS 3
#define ROUNDS 10000000;

struct WorkUnit {		//objeto base da computação em threads
	int id;
	int n_runs;
	double result;
};

void *BusyWork(void *param) {	//função base para execução da thread
	int i;
	struct WorkUnit *wu = param;	//recebimento do parametro

	printf("Iniciando a thread #%d\n", wu->id);
	wu->result = 0.0;

	for (i=0; i<wu->n_runs; i++) wu->result += random();	//executa o processamento e armazena na mem compartilhada

	pthread_exit((void *) wu);
}

int main(int argc, char *argv[]) {
	pthread_t thread[NUM_THREADS];		//declaracao das threads
	struct WorkUnit wunits[NUM_THREADS];	//declaracao estruturas de dados
	struct WorkUnit *w;			//estutura auxiliar
	struct WorkUnit *status;		//estrutura auxiliar
	pthread_attr_t attr;			//declaracao do attr
	int rc, t;				//vars de controle/aux

	pthread_attr_init(&attr);		//inicializa attr
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);	//define como joinable
	
	for(t=0;t<NUM_THREADS;t++) {
		w = &wunits[t];			//inicializa w
		w->id = t; 
		w->n_runs = ROUNDS;

		printf("Lançando a thread #%d\n", t);	
		rc = pthread_create(&thread[t], &attr, &BusyWork, w); 	//criação da thread
		if (rc) {
			errno = rc; 
			perror("pthread_create()");
			exit(EXIT_FAILURE);
		}
	}

	pthread_attr_destroy(&attr);		//libera recursos attr
	
	for(t=0;t<NUM_THREADS;t++) {					//aguarda fim processamento na ordem
		rc = pthread_join(thread[t], (void *) &status);		//realiza o join
		if (rc) {
			errno = rc; 
			perror("pthread_join()");
			exit(EXIT_FAILURE);
		}

		printf("A Thread #%d gerou resultado = %f\n", t, status->result);
	}	

	pthread_exit(NULL);
}

