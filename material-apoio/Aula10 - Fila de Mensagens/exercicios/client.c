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

int main(int argc, char* argv[]) {
	//Declaração da fila
	mqd_t queue;
	//Declaração da Dispacho
	TDispacho dispacho;
	//Texto a ser enviado na Dispacho - entrada por linha de comando
	//char* texto = argv[1];

	if(argc < 4 && argc != 2){
		perror("Parâmetros inválidos!");
		exit(2);
	}

	//Obter descritor (mq_open+O_WRONLY+O_CREAT)
	queue = mq_open(NOME_FILA, O_WRONLY | O_CREAT, 0770, NULL);
	if (queue == (mqd_t) -1) {
		perror("mq_open");
		exit(2);
	}
	int productId = 0;
	float peso = 0;
	float valor = 0;

	//Montar a Dispacho
	sscanf(argv[1], "%d", &productId);
	dispacho.produtoId = productId;
	if(dispacho.produtoId != -1){
		sscanf(argv[2], "%f", &peso);
		sscanf(argv[3], "%f", &valor);
	}
	dispacho.peso = peso;
	dispacho.valor = valor;

	//Enviar (mq_send)
	if (mq_send(queue, (const char*) &dispacho, sizeof(TDispacho), 29) != 0) {
		perror("send #29");
	}

	//Liberar descritor (mq_close)
	mq_close(queue);

	printf("Dispacho enviado!\n");
	exit(EXIT_SUCCESS);
}
