#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

//Declaração do nome da SHMEM
const char* CHAVE = "/controladorvoo";

//Declaração do tamanho a ser reservado 20KB
const int SIZE  = 20480;

//Declaração das funções das threads
void* pousos(void* p);
void* decolagens(void* p);

//Declaração da variável de semáforo em área de memório compart.
sem_t tela_lock;

//Declaração da estrutura de dados unitária a ser compartilhada
typedef struct EspacoAereo {
	int status;
} TEspacoAereo;

void printStatusEspacoAereo(TEspacoAereo* espacoAereo) {
	//system("clear");
	switch (espacoAereo->status)
	{
	case 0:
		printf("[0] - totalmente aberto\n");
		break;
	case 1:
		printf("[1] - aberto para decolagens\n");
		break;
	case 2:
		printf("[2] - aberto para pousos\n");
		break;
	case 3:
		printf("[3] - fechado\n");
		break;
	default:
		printf("[4] - encerrar operações\n");
		break;
	}
}

TEspacoAereo* v;

int main(void) {
	
	//Criação da SHMEM
	int shfd = shm_open(CHAVE, O_RDWR | O_CREAT , 0770);

	//Validação de callback da criação da SHMEM
	if (shfd < 0) { perror("shm_open"); exit(1); }

	//Print do descritor da SHMEM
	printf("Descritor shfd =  %d\n", shfd);

	//Reserva da espaço para a SHMEM
	if (ftruncate(shfd, SIZE) != 0) { perror("ftruncate"); exit(1); }

	//Mapeamento da memória e link com o espaço de edereçamento do processo
	void* espacoAereo = mmap(NULL, SIZE, PROT_WRITE, MAP_SHARED, shfd, 0);

	//Validação de callback do mapeamento
	if (espacoAereo == (void*) -1) { perror("mmap"); exit(1); }

	//Declaração e endereçamento do ponteiro da área comum
	v = (TEspacoAereo*) espacoAereo;

	//Declaração thread
	pthread_t t[2];
	
	//Declaração/inicialização semáforo
	sem_init(&tela_lock, 0, 1);

	//Disparo das threads
	pthread_create(&t[0], NULL, &pousos, NULL);
	pthread_create(&t[1], NULL, &decolagens, NULL);
	
	//Aguarda finalização das threads para poder liberar o semáforo.
	sem_destroy(&tela_lock);

	//Encerramento e liberação recursos das threads
	pthread_exit(NULL);
	
	close(shfd);

	//Remover SHMEM
	shm_unlink(CHAVE);

	printf("\nO Processo terminou!\n");
	return EXIT_SUCCESS;
}

void* pousos(void* p) {
	//Laço para simulação
	while (v->status != 4)
	{
		printf("Thread pousos\n");
		//Se callback sem_wait !=0 = erro
		//sem_wait coloca thread em suspensão se contador retornado = 0
		//SO desperta a thread quando contador > 0
		if (sem_wait(&tela_lock) != 0) exit(85);
		if(v->status == 1 || v->status == 3) {
			printStatusEspacoAereo(v);
		} else {
			printf("Pousando\n");
			sleep(10);
			
		}
		//Add no contador do semáforo
		if (sem_post(&tela_lock) != 0) exit(85);
	}
	//Encerramento função
	return NULL;
}
void* decolagens(void* p) {
	//Laço para simulação
	while (v->status != 4)
	{
		printf("Thread decolagens\n");

		//Se callback sem_wait !=0 = erro
		//sem_wait coloca thread em suspensão se contador retornado = 0
		//SO desperta a thread quando contador > 0
		if (sem_wait(&tela_lock) != 0) exit(85);
		if(v->status == 2 || v->status == 3) {
			printStatusEspacoAereo(v);
		} else {
			printf("Decolando\n");
			sleep(20);
		}
		//Add no contador do semáforo
		if (sem_post(&tela_lock) != 0) exit(85);
	}
	//Encerramento função
	return NULL;
}
