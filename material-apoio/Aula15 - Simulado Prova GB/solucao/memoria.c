#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <mqueue.h>

#define FILE_MAX_LENGTH 512
#define MATRIX_ROW 4
#define MATRIX_COL 4

const char* nomefila = "/jogomemoria";		//Nome da fila IPC
char nomearq[256] = "memoria.txt";		//Nome do arquivo do jogo
char jogo_times[MATRIX_ROW][MATRIX_COL][50];	//Matriz nomes times
int jogo_acertos[MATRIX_ROW][MATRIX_COL];	//Matriz acertos 0-não 1-sim
int jogador1_pontos = 0;			//Controle de pontuação do jogador1
int jogador2_pontos = 0;			//Controle de pontuação do jogador2
int proximo_jogador = 1;			//Controle do próximo jogador habilitado
int terminado = 0;				//Controlador de fim de jogo

//***************Estrutura da mensagem**********************
typedef struct Mensagem {
	int jogador;
	int r1;
	int c1;
	int r2;
	int c2;
} TMensagem;

//Funcao para exibicao do pacote recebido
void imprimir_mensagem(TMensagem* j) {
	printf("Jogador: %d - [%d][%d] [%d][%d]", j->jogador, j->r1, j->c1, j->r2, j->c2);
}

//Funcao para obter tamanho da mensagem
ssize_t get_msg_buffer_size(mqd_t queue) {
	struct mq_attr attr;

	/* Determine max. msg size; allocate buffer to receive msg */
	if (mq_getattr(queue, &attr) != -1) {
		//printf("Tamanho max da mensagem: %ld\n", attr.mq_msgsize);
		return attr.mq_msgsize;
	}

	perror("Erro na alocacao de buffer!");
	exit(3);
}
//***************************

void tratador(int signum){
    switch(signum){
	case SIGUSR2: 
	    printf("O jogo foi cancelado por conta da notificação da CBF! Obrigado\n"); 
	    exit(0);
            break;
    }
}

void carregar_matriz(int fd)
{
    int row=0, col=0, posicao = 0, controle = 0;
    char texto[FILE_MAX_LENGTH];
    const char delim[2] = ";";			//Delimitador ;
    char *token;				//Palavras tokenizadas

    lseek(fd, 0, SEEK_SET);			//Posição 0 do arquivo
    read(fd, texto, FILE_MAX_LENGTH);		//Leitura do arquivo e armazenamento em var local "texto"

    while (texto[posicao] != '\0') if (texto[posicao++]==';') controle++;	//Valida se arquivo de entrada possui 16 times

    if (controle != (MATRIX_ROW*MATRIX_COL)) {
	printf("\nArquivo inválido! O jogo deve conter %d times!\n",MATRIX_ROW*MATRIX_COL);
	exit(0);
    }
	
    token = strtok(texto, delim);		/* retorna o primeiro token */
   
    while(token != NULL) {			/* navega nos proximos tokens */
      strcpy(jogo_times[row][col],token);	//Popula a matriz
      jogo_acertos[row][col]=0;			//Inicializa a matriz de acertos
   
      if (++col==MATRIX_COL){			//Controle das posições do array
	col=0;
	if (++row==MATRIX_ROW) break;
      }
      token = strtok(NULL, delim);		//Movimenta para próximo item tokenizado
    }
}

void exibir_matriz(){				//Atualiza a matriz do jogo a cada lance
    int cont_acerto = 0;

    printf("\n======= TABULEIRO ATUAL =======\n");
    for(int i=0;i<MATRIX_ROW;i++){
        for(int j=0;j<MATRIX_COL;j++){
	    if (jogo_acertos[i][j] == 1){
                printf("%s\t",jogo_times[i][j]);
		cont_acerto++;		
	    }
	    else  printf("X\t");
	}
	printf("\n");
    }
    if (cont_acerto == 16) terminado = -1;	//Atualiza o contador de acertos a cada refresh

    printf("\n======= PONTUAÇÃO ATUAL =======\n JOGADOR1: %d \n JOGADOR2: %d\n\n",jogador1_pontos,jogador2_pontos);
}

int terminar_jogo(){				//Controlador de fim do jogo
    return terminado;
}

void declarar_vencedor(){			//Controlador do vencedor do jogo
    if (jogador1_pontos > jogador2_pontos) printf("JOGADOR 1 VENCEU!!!\n");
    else if (jogador2_pontos > jogador1_pontos) printf("JOGADOR 2 VENCEU!!!\n");
    else printf("JOGO EMPATADO!\n");
}

int validar_jogador(int jogador){		//Validador do jogador habilitado a efetuar a jogada
    if (proximo_jogador == jogador) return -1;
    return 0;
}

int validar_jogada(int row1, int col1, int row2, int col2){	//Valida a jogada dentro dos parâmetros válidos
    if ((row1<MATRIX_ROW && row1>=0) && (row2<MATRIX_ROW && row2>=0) && (col1<MATRIX_COL && col1>=0) && (col2<MATRIX_COL && col2>=0) && (jogo_acertos[row1][col1] == 0) && (jogo_acertos[row2][col2] == 0) && ((row1 != row2) || (col1 != col2))) return -1;
    return 0;
}

int acertar_jogada(int jogador, int row1, int col1, int row2, int col2){	//Valida se ocorre o match das posições
    printf("\nJOGADA: [%d][%d]: %s \t [%d][%d]: %s \n",row1,col1,jogo_times[row1][col1],row2,col2,jogo_times[row2][col2]);
    if (strcmp (jogo_times[row1][col1], jogo_times[row2][col2]) == 0) {
	jogo_acertos[row1][col1] = 1;
	jogo_acertos[row2][col2] = 1;

	if (jogador == 1) jogador1_pontos++;		//Credita o ponto ao respectivo jogador
	else jogador2_pontos++;

	return -1;
    }
    
    if (proximo_jogador == 1) proximo_jogador = 2;	//Atualiza o controlador de proximo jogador habilitado
    else proximo_jogador = 1;				//Troca o contexto do jogador somente em caso de erro de jogada

    return 0;
}

int main()
{
    int fd;
    int r1 = 0, c1 =0, r2 = 0, c2 = 0, jogador = 1;			//Vars auxiliares
    TMensagem jogada_recebida;

    //############ FILA DE MENSAGENS ################
    mqd_t queue;		//Alocacao da fila
    char* buffer = NULL;	//Buffer para armazenar o pacote da fila
    ssize_t tam_buffer;		//Tamanho do buffer da fila
    ssize_t nbytes;		//Quantidade de bytes recebidos da mensagem da fila

    //Obter descritor (mq_open+O_RDONLY)
    //queue = mq_open(nomefila, O_WRONLY | O_CREAT, 0777, NULL);
    queue = mq_open(nomefila, O_RDONLY);
    if (queue == (mqd_t) -1) {	//Tratamento de erro
	perror("Erro na abertura da fila!");
	exit(2);
    }

    //Alocar buffer para receber pacote
    tam_buffer = get_msg_buffer_size(queue);
    buffer = calloc(tam_buffer, 1);
    //############################

    //############## ARQUIVOS ############################
    fd = open(nomearq, O_RDONLY);			//Abertura do arquivo do jogo

    if (fd == -1){					//Validacao da existencia do arquivo
        printf("\nO arquivo não existe.\n");
	return 99;
    }
    //############################
 
    //################ Tratador de sinais #####################
    struct sigaction sa;				
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &tratador;

    if(sigaction(SIGUSR2, &sa, NULL) != 0){
        perror("Falha ao instalar tratador de sinal SIGUSR1");
	return 0;
    }
    //############################

    carregar_matriz(fd);				//Carrega os times do arquivo para a matriz do jogo

    while(1){						//Executa continuamente enquanto jogo ativo
        exibir_matriz();
		
        if(terminar_jogo()) {				//A cada iteração verifica se eh fim de jogo
	    printf("\n****** JOGO TERMINADO ******\n");
            declarar_vencedor();
	    break;
	}

	printf("\nAguardando a jogada (mensagem) chegar ... \n");

	//Receber a mensagem, quando ela estiver na fila
	nbytes = mq_receive(queue, buffer, tam_buffer, NULL);
	if (nbytes == -1) {
		perror("receive");
		exit(4);
	}

	//Tamanho do pacote recebido
	printf("Mensagem recebida (%ld) Bytes: \n", nbytes);
	imprimir_mensagem((TMensagem*) buffer);

	//Transferência dos dados recebidos na mensagem para as variaveis locais
	jogada_recebida = *(TMensagem*) buffer;

	jogador = jogada_recebida.jogador;
	r1 = jogada_recebida.r1;
	c1 = jogada_recebida.c1;
	r2 = jogada_recebida.r2;
	c2 = jogada_recebida.c2;

        if(!validar_jogador(jogador)) printf("\n\nJOGADOR INVÁLIDO!\n");	//Validacao de jogador
	else {
	    if(!validar_jogada(r1,c1,r2,c2)) printf("\n\nJOGADA INVÁLIDA!\n");	//Validacao de jogada
	    else if (acertar_jogada(jogador, r1,c1,r2,c2)) printf("\n\nACERTOU A JOGADA!!!\n");	//Match da jogada e feedback
	    else printf("\n\nERROU A JOGADA!!!\n");
	}
    }
    close(fd);						//Fechamento do descritor de arquivo
    
    mq_close(queue);					//Liberar descritor (mq_close)

    return 0;
}

