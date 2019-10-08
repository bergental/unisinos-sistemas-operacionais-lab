#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

//Nome da fila
const char* NOME_FILA = "/despachos1";

//Estrutura de dados para o produto
typedef struct Dispacho {
	int produtoId;
	float peso;
	float valor;
} TDispacho;

//Declarações das funções
ssize_t get_msg_buffer_size(mqd_t queue);
void print_msg(TDispacho* dispacho, float pesoTotal, float valorTotal);

int main(void) {
	//Declaração da fila
	mqd_t queue;
	float pesoTotal = 0;
	float valorTotal = 0;
	//Declaração do buffer
	char* buffer = NULL;
	//Declaração do tamanho do buffer
	ssize_t tam_buffer;
	ssize_t nbytes;

	//Obter descritor (mq_open+O_RDONLY)
	queue = mq_open(NOME_FILA, O_RDONLY);
	if (queue == (mqd_t) -1) {
		perror("mq_open");
		exit(2);
	}
	int ultimoProdutoId = 0;

	while(ultimoProdutoId != -1){
		//Alocar buffer para receber msg
		tam_buffer = get_msg_buffer_size(queue);
		buffer = calloc(tam_buffer, 1);

		//Receber (mq_recv)
		nbytes = mq_receive(queue, buffer, tam_buffer, NULL);
		if (nbytes == -1) {
			perror("receive");
			exit(4);
		}

		//Print da mensagem recebida
		//printf("bytes recebidos: %d\n", nbytes);
		TDispacho* dispacho = (TDispacho*) buffer;
		ultimoProdutoId = dispacho->produtoId;
		if(ultimoProdutoId != -1){
			pesoTotal = pesoTotal + dispacho->peso;
			valorTotal = valorTotal + dispacho->valor;
			print_msg(dispacho, pesoTotal, valorTotal);
		} else {
			printf("Recebido o código para encerramento da fila!\n");
			mq_close(queue);
			mq_unlink(NOME_FILA);
		}
	}

	//Liberar descritor (mq_close)
	
	printf("Fim!\n");

	exit(EXIT_SUCCESS);
}

void print_msg(TDispacho* dispacho, float pesoTotal, float valorTotal) {
	printf("produtoId=%d, peso=%.2f KG, valor=R$ %.2f\n", dispacho->produtoId, dispacho->peso, dispacho->valor);
	printf("peso total=%.2f KG, valor total=R$ %.2f\n", pesoTotal, valorTotal);
}

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
