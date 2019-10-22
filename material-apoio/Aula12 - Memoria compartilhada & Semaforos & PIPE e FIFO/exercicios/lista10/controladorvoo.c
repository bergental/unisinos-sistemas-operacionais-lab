#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//Declaração do nome da SHMEM
const char* CHAVE = "/controladorvoo";

//Declaração do tamanho a ser reservado 20KB
const int SIZE  = 20480;

//Declaração da estrutura de dados unitária a ser compartilhada
typedef struct EspacoAereo {
	int status;
} TEspacoAereo;

void printMenu(TEspacoAereo* espacoAereo) {
	//system("clear");
	printf("\n");
	if(espacoAereo->status == 0){
		printf("[0]");
	} else {
		printf(" 0 ");
	}
	printf(" - totalmente aberto\n");
	if(espacoAereo->status == 1){
		printf("[1]");
	} else {
		printf(" 1 ");	
	}
	printf(" - aberto para decolagens\n");
	if(espacoAereo->status == 2){
		printf("[2]");
	} else {
		printf(" 2 ");	
	}
	printf(" - aberto para pousos\n");
	if(espacoAereo->status == 3){
		printf("[3]");
	} else {
		printf(" 3 ");	
	}
	printf(" - fechado\n");
	if(espacoAereo->status == 4){
		printf("[4]");	
	} else {
		printf(" 4 ");	
	}
	printf(" - encerrar operações\n");
	printf("\n");
	printf("Escolha alguma das opções acima:\n");
}

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
	TEspacoAereo* v = (TEspacoAereo*) espacoAereo;
	
	//Alocação de valores no processo pai
	v->status = 3;

	// ler da memoria compartilhada antes fork
	//printf("Valores do objeto antes fork \nv: a=%d d=%f n[35]=%lx\n", v->a, v->d, v->n[35]);
	int opcao;
	while(v->status != 4) {
		printMenu(v);
		scanf("%d", &opcao);
		if(opcao > 4 || opcao < 0) {
			printf("Opção inválida!\n");
			continue;
		}
		v->status = opcao;
	}

	//Criação do processo filho
	/*switch (fork()) {
	case -1: 
		perror("fork"); exit(39);

	case 0: // no filho - escrever na memoria compartilhada
		printf("\nFilho iniciando...\n");
		sleep(2);
		v->a = 35;
		v->d = 3.14158192;
		v->n[35] = 0xFFFF;
		exit(EXIT_SUCCESS);

	default: // no pai
		printf("\nPai aguardando filho terminar...\n");

		wait(NULL); // esperar o filho terminar

		// ler da memoria compartilhada
		printf("\nValores do objeto depois fork \nv: a=%d d=%f n[35]=%lx\n", v->a, v->d, v->n[35]);
	}*/
	
	close(shfd);

	//Remover SHMEM
	shm_unlink(CHAVE);

	printf("\nO Processo terminou!\n");
	return EXIT_SUCCESS;
}
