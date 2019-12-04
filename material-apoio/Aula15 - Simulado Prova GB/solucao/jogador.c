#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

//Nome da fila
const char* nomefila = "/jogomemoria";

//***************Estrutura da mensagem*********
typedef struct Mensagem {
	int jogador;
	int r1;
	int c1;
	int r2;
	int c2;
} TMensagem;
//*********************************************

int main(int argc, char* argv[]) {
	mqd_t queue;				//Alocacao da fila
	TMensagem jogada;			//Alocacao do objeto pacote (mensagem)
	int jogador = 0, sair = 0; 
	int r1 = 0, c1 = 0, r2 = 0, c2 = 0;	//Variaveis de apoio

	queue = mq_open(nomefila, O_WRONLY | O_CREAT, 0777 , NULL);
	if (queue == (mqd_t) -1) {
		perror("Erro na abertura da fila!");
		exit(2);
	}

	//Loop para envio de mensagens
	while(sair==0){
		printf("Digite o id do jogador (1 ou 2): ");
		scanf("%d",&jogador);
		printf("Digite a posição Linha 1 (R1): ");
		scanf("%d",&r1);
		printf("Digite a posição Coluna 1 (C1): ");
		scanf("%d",&c1);
		printf("Digite a posição Linha 2 (R2): ");
		scanf("%d",&r2);
		printf("Digite a posição Coluna 2 (C2): ");
		scanf("%d",&c2);

		printf("Enviando mensagem para o tabuleiro... \n");

		//Montar pacote a ser enviado por mensagem
		jogada.jogador = jogador;
		jogada.r1 = r1;
		jogada.c1 = c1;
		jogada.r2 = r2;
		jogada.c2 = c2;

		//Enviar (mq_send)
		if (mq_send(queue, (const char*) &jogada, sizeof(TMensagem), 0) != 0) {
			perror("Erro no envio do pacote!");
		}

		printf("Pacote enviado para o tabuleiro!\n");

		printf("Deseja continuar despachando pacotes (0=SIM) (1=NÃO)? ");
		scanf("%d",&sair);
	}

	//Liberar descritor (mq_close)
	mq_close(queue);

	printf("Programa encerrado com sucesso!\n");
	exit(EXIT_SUCCESS);
}
