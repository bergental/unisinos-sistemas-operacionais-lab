#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

//Declaração variáveis globais
struct sigaction sa;
sigset_t newmask, oldmask;

struct processoAtributos
{
	pid_t webBrowserPID;
	char webBrowserSTATUS[100];
	pid_t textEditorPID;
	char textEditorSTATUS[100];
	pid_t terminalPID;
	char terminalSTATUS[100];
	char finalizarSTATUS[100];
} processoControle;

int opcao_menu=0;

//Menu principal
void menu(void)
{
	system("clear\n");
	printf("<<<< Aplications Menu >>>>\n");
	printf("1 - Web Browser (%s)\n", processoControle.webBrowserSTATUS);
	printf("2 - Text Editor (%s)\n", processoControle.textEditorSTATUS);
	printf("3 - Terminal (%s)\n", processoControle.terminalSTATUS);
	printf("4 - Finalizar Processo (%s)\n", processoControle.finalizarSTATUS);
	printf("5 - Quit\n");
}

//Tratador de sinais capturados
void tratador_sinal(int signum){
        pid_t pid = 0;
        int statusProcesso;
	char *statusControle = "Concluído";

	if(signum == SIGINT || signum == SIGALRM || signum == SIGCHLD){
                pid = waitpid(-1, &statusProcesso, WNOHANG);
                if(pid == processoControle.webBrowserPID && pid != 0 && ((strcmp(processoControle.webBrowserSTATUS, statusControle)) != 0)){
			processoControle.webBrowserPID = 0;
                        strcpy(processoControle.webBrowserSTATUS, "Abortado");
                } 
		else if(pid == processoControle.textEditorPID && pid != 0 && ((strcmp(processoControle.textEditorSTATUS, statusControle)) != 0)){
                        processoControle.textEditorPID = 0;
                        strcpy(processoControle.textEditorSTATUS, "Abortado");
                } 
		else if(pid == processoControle.terminalPID && pid != 0 && ((strcmp(processoControle.terminalSTATUS, statusControle)) != 0)){
                        processoControle.terminalPID = 0;
                        strcpy(processoControle.terminalSTATUS, "Abortado");
                }
	}		 
}

//Instalador de sinais a serem capturados e encaminhados para o tratador
void instalador_sinal(){
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);
	sigaddset(&newmask, SIGCHLD);
	sigaddset(&newmask, SIGALRM);

  	memset(&sa, 0, sizeof(sa));
  	sa.sa_handler = &tratador_sinal;

	if(sigaction(SIGCHLD, &sa, NULL) != 0){
		perror("Falha ao instalar tratador de sinal SIGCHLD");
		exit(-1);
	}

	if(sigaction(SIGINT, &sa, NULL) != 0){
		perror("Falha ao instalar tratador de sinal SIGINT");
		exit(-1);
	}

	if(sigaction(SIGALRM, &sa, NULL) != 0){
		perror("Falha ao instalar tratador de sinal SIGALRM");
		exit(-1);
	}
}

//Execução dos processos filhos
void executar_programa(char *base, char *programa, char status[100], char *URL)
{
	pid_t pid;

	if((pid = fork()) < 0){
		perror("Erro no fork!");
	}
	else if(pid == 0){
		sigprocmask(SIG_BLOCK, &newmask, &oldmask);
		if(URL != NULL){
			execlp(base, programa, URL, NULL);
		}
		else{
			execlp(base, programa, NULL);
		}
	}
	else{
		switch(opcao_menu){
		case 1:
			processoControle.webBrowserPID = pid;
			sprintf(status, "Executando, PID=%d", processoControle.webBrowserPID);
			break;
		case 2:
			processoControle.textEditorPID = pid;
			sprintf(status, "Executando, PID=%d", processoControle.textEditorPID);
			break;
		case 3:
			processoControle.terminalPID = pid;
			sprintf(status, "Executando, PID=%d", processoControle.terminalPID);
			break;
		}
	}
}

//Encerramento dos processos filhos
void encerrar_processo(int processoPID, char status[100])
{
	int statusEncerrar = kill(processoPID, SIGTERM);

	if (statusEncerrar == 0) strcpy(processoControle.finalizarSTATUS, "Concluído");
	else if(statusEncerrar == -1) strcpy(processoControle.finalizarSTATUS, "Falhou");
}

//Leitura de entrada do menu e submenu
int entrada_menu()
{
	char URL[100];
	int opcao_codigo = 0;
	opcao_menu=0;

	printf("Opção: ");
	scanf("%d",&opcao_menu);

	switch(opcao_menu)
	{
	case 1:
		printf("Digite a URL: \n");
		scanf("%s", URL);
		executar_programa("/usr/bin/firefox", "firefox", processoControle.webBrowserSTATUS, URL);
		break;
	case 2:
		executar_programa("/usr/bin/gedit", "gedit", processoControle.textEditorSTATUS, NULL);
	        break;
	case 3:
	        executar_programa("/usr/bin/xterm", "xterm", processoControle.terminalSTATUS, NULL);
	        break;
	case 4:
	        printf("Digite o número da aplicação a ser finalizada: ");
	        scanf("%d",&opcao_codigo);
		getchar();

	        switch(opcao_codigo)
	        {
	        case 1:
			if(processoControle.webBrowserPID != 0) encerrar_processo(processoControle.webBrowserPID, processoControle.webBrowserSTATUS);
	   		else printf("Não há aplicação de WebBrowser executando.\n");

           		break;

	        case 2:
	   		if(processoControle.textEditorPID != 0) encerrar_processo(processoControle.textEditorPID, processoControle.textEditorSTATUS);
	   		else printf("Não há aplicação de TextEditor executando\n");

           		break;
          
		case 3:
	   		if(processoControle.terminalPID != 0) encerrar_processo(processoControle.terminalPID, processoControle.terminalSTATUS);
	   		else printf("Não há aplicação de Terminal executando.\n");
            		break;
          
		default:
            		printf("Opção inválida! Digite um número entre 1 e 3.\n");
            		break;
        	}
        	break;

	case 5:
       		printf("Encerrando o programa....\n");
       		break;

	default:
		if ((!SIGALRM && !SIGINT && !SIGCHLD) && (opcao_menu < 1 || opcao_menu > 5)){
        		printf("Dado inválido! Digite uma opção entre 1 e 5.\n");
    			break;
		}
  	}

	sleep(1);
	return opcao_menu;
}

//Módulo principal
int main()
{
	//Captura e tratamento de sinais	
	instalador_sinal();

	//Loop de controle do processo principal
	do{  	
		//Agendador de alarm a cada 5 segundos		
		if (alarm(5) < 0){
			perror("Falha no alarm.");
		}
		//Menu principal
		menu();
		opcao_menu = entrada_menu();
	} while (opcao_menu != 5);

	sleep(1);
	return 0;
}
