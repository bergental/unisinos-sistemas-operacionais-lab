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
#include <semaphore.h>

#define CHAVE_SALA "/sala"
#define NOME_FILA_JOGADOR1 "/jogador1"
#define NOME_FILA_JOGADOR2 "/jogador2"
#define NOME_FILA_SERVER1 "/server1"
#define NOME_FILA_SERVER2 "/server2"

enum MensagemTipo {
    ENTRAR = 0,
    JOGADA = 1,
    VEZ = 2,
    FIM = 3,
};

enum SalaStatus {
    AGUARDANDO_JOGADOR = 1,
    JOGANDO = 3,
    TERMINOU = 4
};

// Fila de Mensagem
typedef struct Jogador {
    int id;
    char nome[30];
} TJogador;

// Fila de Mensagem
typedef struct Mensagem {
    enum MensagemTipo tipo;
    TJogador jogador;
    int i;
    int j;
} TMensagem;

typedef struct Sala {
    char times[4][4][20];
    int mostrar[4][4];
    enum SalaStatus status;
    int jogadorGanhador;
    int jogadorVez;
    int jogador1acertos;
    int jogador2acertos;
} TSala;

char oculto[20];

//Declaração do tamanho a ser reservado 20KB
const int SIZE  = 20480;
static TSala* sala;
static mqd_t filas_rd[2];  // filas de leitura
static mqd_t filas_wt[2];  // filas de escrita

static TJogador jogador1;
static TJogador jogador2;


void openMemoryShared(){
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
	sala = (TSala*) salaSHFD;
}

void printTabuleiro(int showAll) {
    for(int i = 0; i < 4; i++) {
            int ll = 0;
            while (ll++ < 85)
            {
                printf("-");
            }
            printf("\n");
            
            for (int j = 0; j < 4; j++)
                if(showAll == 1 || sala->mostrar[i][j] == 1)
                    printf("|%-20s",sala->times[i][j]);
                else
                    printf("|%-20s",oculto);
            printf("|\n");
        }
        int ll = 0;
        while (ll++ < 85)
        {
            printf("-");
        }
        printf("\n");
}

void populateTabuleiroMod1(char* conteudo) {
    const char s[2] = ";";
    const char l[2] = "\n";
    char *token;
    char *line;

    /* retorna o primeiro token */
    line = strtok(conteudo, l);
    
    int i=0, j=0, lPos=0;
    int count = 0;
    /* navega nos proximos tokens */
    char lines[4][84] ={"", "", "", ""};
    while ( line != NULL) {
        //token = strtok(line, s);
        if(lPos == 4) break;
        //printf("line=%d\n", lPos);
        strcpy(lines[lPos++], line);
        line = strtok(NULL, l);
    }
    
    for (int ll = 0; ll < 4; ll++)
    {
        //printf("line=%d\n", ll);
        /* retorna o primeiro token */
        token = strtok(lines[ll], s);
        while( token != NULL ) {
            count++;
            strcpy(sala->times[i][j],token);
            j++;
            if(j == 4) { i++; j = 0; }
            //printf("%s\n", token );
            
            token = strtok(NULL, s);
        }
        if(j == 4) { i++; j = 0; }
    }

    //printf("count=%d\n", count);
    if(count != 16) {
        printf("Número de opções diferente de 16\n");
        exit(-1);
    }
}

void populateTabuleiroMod2(char* conteudo) {
    const char s[2] = ";";
    char *token;

    /* retorna o primeiro token */
    token = strtok(conteudo, s);
    
    int i=0, j=0, count = 0;
    
    while( token != NULL ) {
        if(token[0] == '\n') token += 1;
        count++;
        strcpy(sala->times[i][j],token);
        j++;
        if(j == 4) { i++; j = 0; }
        //printf("%s\n", token );
        
        token = strtok(NULL, s);
    }

    //printf("count=%d\n", count);
    if(count != 16) {
        printf("Número de opções diferente de 16\n");
        exit(-1);
    }
}

void readTabuleiro() {
    int file;
    file = open("./jogo.txt", O_RDONLY);

    if(file == -1) {
        printf("O arquivo 'jogo.txt' não existe!\n");
        exit(-1);
    } else {

        int sz = lseek(file, 0L, SEEK_END);
        char conteudo[sz];
        lseek(file, 0L, SEEK_SET);
        read(file, conteudo, sizeof(conteudo));
        //printf("conteudo=%s\n", conteudo);

        char empty[20] = "";
        for(int i = 0; i < 20; i++)
            oculto[i] = 'x';
        for(int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                sscanf(sala->times[i][j], "%s", empty);
        
        //printf("conteudo=%s\n", conteudo);
        populateTabuleiroMod1(conteudo);
        //populateTabuleiroMod2(conteudo);

        close(file);
    }
}

static TJogador aguarda_jogador_entrar(mqd_t fila)
{
    while(1) {
        TMensagem msg;
        ssize_t nbytes = mq_receive(fila, (char*)&msg, sizeof(TMensagem), NULL);
        if (nbytes == -1) {
            perror("mq_receive");
            exit(4);
        }
        if (msg.tipo == ENTRAR) {
            return msg.jogador;
        }
    }
}

static void ganhou(TJogador jogador, int i, int j) {
    printf("Jogador %s ganhou\n", jogador.nome);
    log_jogada(jogador.nome, i, j, "Jogador ganhou");
    sala->jogadorGanhador = jogador.id;
}

static int aguarda_jogada(mqd_t fila)
{
    while(1) {
        TMensagem msg;
        ssize_t nbytes = mq_receive(fila, (char*)&msg, sizeof(TMensagem), NULL);
        if (nbytes == -1) {
            perror("mq_receive");
            exit(4);
        }
        if (msg.tipo == JOGADA) {
            if (realiza_jogada(msg.i, msg.j, msg.jogador) == xo) {
                ganhou(msg.jogador, msg.i, msg.j);
                return 0;
            }
            break;
        }
    }

    return 1;
}

static void envia_msg(TMensagem msg, mqd_t fila) {
    if (mq_send(fila, (const char*) &msg, sizeof(TMensagem), 29) != 0) {
        perror("mq_send");
    }
}

int main(int argc, char const *argv[])
{
    shm_unlink(CHAVE_SALA);
    mq_unlink(NOME_FILA_JOGADOR2);
    mq_unlink(NOME_FILA_JOGADOR1);
    mq_unlink(NOME_FILA_SERVER2);
    mq_unlink(NOME_FILA_SERVER1);
    
    openMemoryShared();
    sala->status = AGUARDANDO_JOGADOR;

    readTabuleiro();

    filas_rd[0] = create_queue(NOME_FILA_JOGADOR1);
    filas_rd[1] = create_queue(NOME_FILA_JOGADOR2);
    filas_wt[0] = create_queue(NOME_FILA_SERVER1);
    filas_wt[1] = create_queue(NOME_FILA_SERVER2);

    sala->status = AGUARDANDO_JOGADOR;
    sala->jogadorVez = 1; // numero do jogador da vez que deve entrar
    jogador1 = aguarda_jogador_entrar(filas_rd[0]);
    printf("Jogador '%s' entrou\n", jogador1.nome);

    sala->jogadorVez = 2;
    jogador2 = aguarda_jogador_entrar(filas_rd[1]);
    printf("Jogador '%s' entrou\n", jogador2.nome);

    sala->jogadorVez = 1;
    sala->status = JOGANDO;
    printf("Partida começou\n");
    
    printTabuleiro(1);
    sleep(4);
    system("clear");
    printTabuleiro(0);

    TMensagem msg;
    msg.tipo = VEZ;

    while (sala->status == JOGANDO)
    {
        sala->jogadorVez = (i % 2) + 1;
        envia_msg(msg, filas_wt[i % 2]);
        if (!aguarda_jogada(filas_rd[i % 2])) {
            break;
        }
    }
    

    msg.tipo = FIM;
    envia_msg(msg, filas_wt[0]);
    envia_msg(msg, filas_wt[1]);

    sala->status = TERMINOU;
    printf("Partida terminou\n");

    destroy_queue(filas_rd[1], NOME_FILA_JOGADOR2);
    destroy_queue(filas_rd[0], NOME_FILA_JOGADOR1);
    destroy_queue(filas_rd[1], NOME_FILA_SERVER2);
    destroy_queue(filas_rd[0], NOME_FILA_SERVER1);
    destroy_shm();

    return 0;
}
