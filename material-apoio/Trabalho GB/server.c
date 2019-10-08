#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

enum MensagemTipo {
	ENTRAR = 0,
	ENTROU = 1,
	CHEIO = 2,
	NOME_JA_USADO = 3
};

//Nome da fila
const char* NOME_FILA_JOGADOR1 = "/jogador1";
const char* NOME_FILA_JOGADOR2 = "/jogador2";
char* NOME_FILA_SERVER = "/server";

typedef struct Jogador {
	int jogadorId;
	char nome[30];
	int ganhador;
} TJogador;

typedef struct Mensagem {
	int jogadorId;//jogadorId = 0 SERVER
	enum MensagemTipo tipo;
	TJogador jogador;
} TMensagem;



//Declarações das funções
ssize_t get_msg_buffer_size(mqd_t queue);
//void print_msg(TDispacho* dispacho, float pesoTotal, float valorTotal);

int main(void) {
	//Declaração da fila
	mqd_t queueServer;
	mqd_t queueJogador1;
	mqd_t queueJogador2;
	float pesoTotal = 0;
	float valorTotal = 0;
	//Declaração do buffer
	char* buffer = NULL;
	//Declaração do tamanho do buffer
	ssize_t tam_buffer;
	ssize_t nbytes;

	//Obter descritor (mq_open+O_RDONLY)
	queueServer = mq_open(NOME_FILA_SERVER, O_RDONLY);
	if (queueServer == (mqd_t) -1) {
		perror("mq_open");
		exit(2);
	}
	
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
