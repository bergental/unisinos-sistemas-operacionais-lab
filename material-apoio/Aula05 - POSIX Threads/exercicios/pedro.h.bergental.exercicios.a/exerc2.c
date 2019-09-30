#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<errno.h>
#include<unistd.h>

#define NUM_THREADS 4

struct Operation {
 int id;
 int value1;
 int value2;
 int operationCode;
 double result;
};

char* operantionName(int operationCode) {
	switch (operationCode)
        {
   	 case 0:
     	  return "soma";
         case 1:
     	  return "subtração";
         case 2:
     	  return "divisão";
         default:
     	  return "multiplicação";
        }
	return "";
}

void *BusyWork(void *param) {	//função base para execução da thread
	struct Operation *wu = param;	//recebimento do parametro
	char* operName = operantionName(wu->operationCode);
	printf("Iniciando a thread #%d operação de %s\n", wu->id, operName);
	wu->result = 0.0;

	switch (wu->operationCode)
        {
   	 case 0:
     	  wu->result = wu->value1 + wu->value2;
   	  break;
         case 1:
     	  wu->result = wu->value1 - wu->value2;
          break;
         case 2:
     	  wu->result = (float) wu->value1 / wu->value2;
          break;
         default:
     	  wu->result = wu->value1 * wu->value2;
        }
	pthread_exit((void *) wu);
}

int main(int argc, char *argv[]) {
	pthread_t thread[NUM_THREADS];		//declaracao das threads
	struct Operation wunits[NUM_THREADS];	//declaracao estruturas de dados
	struct Operation *w;			//estutura auxiliar
	struct Operation *status;		//estrutura auxiliar
	pthread_attr_t attr;			//declaracao do attr
	int rc, t;				//vars de controle/aux

	pthread_attr_init(&attr);		//inicializa attr
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);	//define como joinable
	
	for(t=0;t<NUM_THREADS;t++) {
		w = &wunits[t];			//inicializa w
		w->id = t; 
		w->value1 = atoi(argv[1]);
		w->value2 = atoi(argv[2]);
		w->operationCode = t;

		printf("Lançando a thread #%d\n", t);	
		rc = pthread_create(&thread[t], &attr, &BusyWork, w); 	//criação da thread
		if (rc) {
			errno = rc; 
			perror("pthread_create()");
			exit(EXIT_FAILURE);
		}
	}

	pthread_attr_destroy(&attr);		//libera recursos attr
	
	float sum = 0;
	for(t=NUM_THREADS - 1;t> -1;t--) {					//aguarda fim processamento na ordem
		rc = pthread_join(thread[t], (void *) &status);		//realiza o join
		if (rc) {
			errno = rc; 
			perror("pthread_join()");
			exit(EXIT_FAILURE);
		}
                sum += status->result;
		char* operName = operantionName(status->operationCode);
		printf("A Thread #%d da operação de %s gerou resultado = %.2f\n", t, operName, status->result);
	}	
        printf("A soma de todas operações da o resultado = %.2f\n", sum);
	pthread_exit(NULL);
}

