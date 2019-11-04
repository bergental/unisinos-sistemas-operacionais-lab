#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <unistd.h>

enum MensagemTipo {
	ENTRAR = 0,
	ENTROU = 1,
	NOME_JA_USADO = 2
};

enum SalaStatus {
	VAZIA = 0,
	AGUARDANDO_JOGADOR = 1,
	CHEIA = 2,
	FECHADA = 3
};

//Nome da fila
const char* NOME_FILA_JOGADOR1 = "/jogador1";
const char* NOME_FILA_JOGADOR2 = "/jogador2";
const char* NOME_FILA_SERVER = "/server";
const char* CHAVE_SALA = "/sala";

// Fila de Mensagem
typedef struct Jogador {
	int jogadorId;
	char nome[30];
	int ganhador;
} TJogador;

// Memoria compartilhada
typedef struct Sala {
	TJogador jogador1;
	TJogador jogador2;
	enum SalaStatus status;
} TSala;

// Fila de Mensagem
typedef struct Mensagem {
	int jogadorId;//jogadorId = 0 SERVER
	enum MensagemTipo tipo;
	TJogador jogador;
} TMensagem;

//Declaração do tamanho a ser reservado 20KB
const int SIZE  = 20480;

//Declarações das funções
ssize_t get_msg_buffer_size(mqd_t queue);
//void print_msg(TDispacho* dispacho, float pesoTotal, float valorTotal);

int main(void) {
	//Declaração da fila
	mqd_t queueServer;
	mqd_t queueJogador1;
	mqd_t queueJogador2;
	//Declaração do buffer
	char* buffer = NULL;
	//Declaração do tamanho do buffer
	ssize_t tam_buffer;
	ssize_t nbytes;
	int count;

	//Obter descritor (mq_open+O_RDONLY)
	queueServer = mq_open(NOME_FILA_SERVER, O_RDONLY);
	if (queueServer == (mqd_t) -1) {
		perror("mq_open");
		exit(2);
	}

	//Criação da SHMEM
	int shfd = shm_open(CHAVE_SALA, O_RDWR | O_CREAT , 0770);

	//Validação de callback da criação da SHMEM
	if (shfd < 0) { perror("shm_open"); exit(1); }

	//Print do descritor da SHMEM
	printf("Descritor shfd =  %d\n", shfd);

	//Reserva da espaço para a SHMEM
	if (ftruncate(shfd, SIZE) != 0) { perror("ftruncate"); exit(1); }

	//Mapeamento da memória e link com o espaço de edereçamento do processo
	void* salaSHFD = mmap(NULL, SIZE, PROT_WRITE, MAP_SHARED, shfd, 0);

	//Validação de callback do mapeamento
	if (salaSHFD == (void*) -1) { perror("mmap"); exit(1); }

	//Declaração e endereçamento do ponteiro da área comum
	TSala* sala = (TSala*) salaSHFD;
	sala->status = VAZIA;

	while(1){
		//Alocar buffer para receber msg
		tam_buffer = get_msg_buffer_size(queueServer);
		buffer = calloc(tam_buffer, 1);

		//Receber (mq_recv)
		nbytes = mq_receive(queueServer, buffer, tam_buffer, NULL);
		if (nbytes == -1) {
			perror("receive");
			exit(4);
		}

		//Print da mensagem recebida
		//printf("bytes recebidos: %d\n", nbytes);
		TMensagem* mensagem = (TMensagem*) buffer;

		if(mensagem->tipo == ENTRAR) {
			int jogadorID = ++count;
			if(jogadorID < 3) {

			} else {
				--count;
			}
		}
	
		//mq_close(queue);
		//mq_unlink(NOME_FILA);
	}

	//Liberar descritor (mq_close)
	
	printf("Fim!\n");

	exit(EXIT_SUCCESS);
}

/* void print_msg(TDispacho* dispacho, float pesoTotal, float valorTotal) {
	printf("produtoId=%d, peso=%.2f KG, valor=R$ %.2f\n", dispacho->produtoId, dispacho->peso, dispacho->valor);
	printf("peso total=%.2f KG, valor total=R$ %.2f\n", pesoTotal, valorTotal);
}*/

ssize_t get_msg_buffer_size(mqd_t queue) {
	struct mq_attr attr;

	/*Determina max. msg size; allocate buffer to receive msg */
	if (mq_getattr(queue, &attr) != -1) {
		//printf("max msg size: %ld\n", attr.mq_msgsize);
		return attr.mq_msgsize;
	}

	perror("aloca_msg_buffer");
	exit(3);
}
