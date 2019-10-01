#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <memory.h>
#include <sys/types.h>
#include <sys/poll.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

float getSalarioAnual() {
    float salarioAnual;
    printf("Digite o salário anual do colaborador: ");
	scanf("%f", &salarioAnual);
    //getchar();
    if(salarioAnual < 0 || salarioAnual > 120000) {
        printf("Salário inválido! (Deve estar entre 0 e 120.000)\n");
        return getSalarioAnual();
    } else
        return salarioAnual;
}

static pid_t launch_process(const char* command, const char* name, const char* param1, const char* param2)
{
    name = name ? name : "undefined";
    param1 = param1 ? param1 : "";
    param1 = param1 ? param2 : "";

    pid_t pid = fork();

    if (pid > 0) {
        /* Processo Pai */
        return pid;
    }
    else {
        /* Processo Filho */
        int status = execlp(command, name, param1, param2, NULL);
        if (status == -1) {
            perror("Execução falhou");
            exit(127);
        }
    }
}

/**
 * \brief Trata os sinais SIGINT e SIGCHLD.
 * \param sig  Número do sinal.
 * \param info Informações sobre o sinal.
 * \param ucontext Contexto de usuário.
 */
void signal_handler(int sig, siginfo_t* info, void* ucontext)
{
    switch (sig) {
        case SIGINT: {
            printf("Sinal recebido. Obrigado por utilizar o Contabilidade!\n");
            exit(-1);
            break;
        }
        case SIGTERM: {
            printf("Sinal recebido. Obrigado por utilizar o Contabilidade!\n");
            exit(-1);
            break;
        }
        case SIGUSR1: {
            printf("Sinal recebido. Aguardar a conclusão do processo filho!\n");
            break;
        }
        case SIGUSR2: {
            printf("Sinal recebido. Ainda em processamento...\n");
            break;
        }
        default: {
            sleep(1);
        }
    }
}

/**
 * Registra todos os tratadores de sinais.
 */
void register_signal_handlers()
{
    struct sigaction sigact;
    memset(&sigact, 0, sizeof(struct sigaction));
    sigact.sa_sigaction = signal_handler;
    sigact.sa_flags = SA_SIGINFO;

    sigaction(SIGINT, &sigact, NULL);   // Sinal de Ctrl+C
    sigaction(SIGTERM, &sigact, NULL);  // Recebe o sinal de terminação
    sigaction(SIGUSR1, &sigact, NULL);
    sigaction(SIGUSR2, &sigact, NULL);
}

int main(int argc, char *argv[]){
    register_signal_handlers();
    float salarioAnual = getSalarioAnual();
    float salarioMedio = salarioAnual / 12;
    float base = 3000;
	pid_t pid;		
	int status;

    if(salarioMedio < base) {
            launch_process("./simplificado", "simplificado", NULL, NULL);
            //execlp("./simplificado", "simplificado", NULL);
    } else {
        /* Verifica se há um browser configurado em variável de ambiente */
        char* browser = getenv("BROWSER");
        if (browser == NULL) {
            /* Volta para browser default */
            browser = "firefox";
        }

        launch_process(browser, "BROWSER", "--new-window", "www.receita.fazenda.gov.br");
    }
    while (1)
    {
        sleep(1);
    }
    //exit(-1);
}