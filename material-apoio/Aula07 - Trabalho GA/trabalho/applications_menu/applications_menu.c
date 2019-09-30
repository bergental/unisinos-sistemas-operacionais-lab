/**
 * \file    applications_menu.c
 * \author  Natanael Rabello
 * \author  Pedro Bergental
 * \brief   Trabalho GA - Laboratório de Sistemas Operacionais
 */

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

/** Número máximo de aplicativos */
#define APPS_NUM 3

/**
 * Estado do aplicativo
 */
enum state {
    NONE = 0,  //!< Não iniciado
    RUNNING,   //!< Rodando
    FAILED,    //!< Falhou, aplicativo retornou erro
    ABORTING,  //!< Processo está sendo terminado forçadamente
    ABORTED,   //!< Processo foi terminado forçadamente
    FINISHED,  //!< Processo finalizou execução com sucesso
};

/**
 * Estrutura contexto do applicativo
 */
struct app {
    enum state state;  //!< Estado atual
    int exit_status;   //!< Código de retorno do processo
    char msg[30];      //!< Messagem de status do applicativo no menu
    pid_t pid;         //!< PID do processo do applicativo
};

/*! Armazena contexto dos aplicativos */
static struct app apps[APPS_NUM];

/*! Armazena messagem de finalização do processo */
static char kill_msg[30];

/**
 * \brief Verifica se usuário digitou alguma coisa na entrada padrão
 * dentro de um tempo máximo.
 * \param timeout_ms Tempo de verificação.
 * \return 1 se há alguma entrada em STDIN, 0 caso contrário.
 */
static int stdin_available(const int timeout_ms)
{
    struct pollfd pollfd = {
        .fd = STDIN_FILENO,
        .events = POLLIN,
        .revents = 0,
    };

    /* Espera STDIN até timeout */
    int poll_ret = poll(&pollfd, 1, timeout_ms);
    if (poll_ret == -1) {
        /* Caso polling for interrompido por um sinal, apenas retorna */
        if (errno == EINTR) {
            return 0;
        }
        else {
            perror("polling stdin falhou");
            exit(1);
        }
    }

    return (poll_ret > 0) && (pollfd.revents & POLLIN);
}

/**
 * Imprimi o menu de aplicativos na tela.
 */
static void print_menu()
{
    /* Limpa a tela do terminal */
    system("clear");
    printf(
        "<<< Applications Menu >>>\n\
    1) Web Browser              %s\n\
    2) Text Editor              %s\n\
    3) Terminal                 %s\n\
    4) Finalizar processo       %s\n\
    5) Quit\n\
Opção: ",
        apps[0].msg, apps[1].msg, apps[2].msg, kill_msg);
    fflush(stdout);
}

/**
 * \brief Le numero da entrada padrão e verifica se é uma opção válida.
 * \return Opção digitada caso válida, ou 0 se opção inválida.
 */
static int read_option()
{
    int option;
    if (scanf("%d", &option) != 1 || option < 1 || option > 5) {
        return 0;
    }
    return option;
}

/**
 * \brief Inicializa um aplicativo em um processo filho.
 * \param command Comando do aplicativo.
 * \param params0 Parametro opcional
 * \param params1 Parametro opcional
 * \return PID do processo filho.
 */
static pid_t launch_process(const char* command, const char* param0, const char* param1)
{
    param0 = param0 ? param0 : "";
    param1 = param1 ? param1 : "";

    pid_t pid = fork();
    assert(pid >= 0);

    if (pid > 0) {
        /* Processo Pai */
        return pid;
    }
    else {
        /* Processo Filho */
        int status = execlp(command, param0, param1, NULL);
        if (status == -1) {
            perror("Execução falhou");
            exit(127);
        }
    }
}

/**
 * Inicializa o Navegador em um novo processo.
 */
static void launch_web_browser()
{
    struct app* app = &apps[0];

    if (app->state != RUNNING) {
        /* Verifica se há um browser configurado em variável de ambiente */
        char* browser = getenv("BROWSER");
        if (browser == NULL) {
            /* Volta para browser default */
            browser = "firefox";
        }

        /* Solicita URL ao usuário */
        char url[256] = { 0 };
        printf("Digite a url a ser aberta (max: 256):\n");
        scanf("%s", url);

        printf("Iniciando Web Browser: %s\n", browser);
        fflush(stdout);
        app->state = RUNNING;
        app->pid = launch_process(browser, "--new-window", url);
    }

    sleep(1);
}

/**
 * Inicializa o Editor de Texto em um novo processo.
 */
static void launch_text_editor()
{
    printf("Iniciando Text Editor\n");

    struct app* app = &apps[1];
    if (app->state != RUNNING) {
        /* Verifica se há um editor configurado em variável de ambiente */
        char* editor = getenv("EDITOR");
        if (editor == NULL) {
            /* Volta para editor default */
            editor = "gedit";
        }

        printf("Iniciando Text Editor: %s\n", editor);
        fflush(stdout);
        app->state = RUNNING;
        app->pid = launch_process(editor, NULL, NULL);
    }

    sleep(1);
}

/**
 * Inicializa o terminal em um novo processo.
 */
static void launch_terminal()
{
    struct app* app = &apps[2];

    if (app->state != RUNNING) {
        /* Verifica se há um terminal configurado em variável de ambiente */
        char* terminal = getenv("TERMINAL");
        if (terminal == NULL) {
            /* Volta para terminal default */
            terminal = "gnome-terminal";
        }

        printf("Iniciando Terminal: %s\n", terminal);
        fflush(stdout);
        app->state = RUNNING;
        app->pid = launch_process(terminal, NULL, NULL);
    }
    else {
        fprintf(stderr, "Já existe uma instancia deste applicativo em execução\n");
    }

    sleep(1);
}

/**
 * \brief Finaliza um aplicativo em processo filho.
 */
static void terminate_app()
{
    int app_option;
    printf("Digite o número da aplicação: \n");
    scanf("%d", &app_option);

    /* Verific se número corresponde a uma aplicação no menu */
    if (app_option < 1 || app_option > 3) {
        printf("Opção inválida!\n");
        sleep(1);
        return;
    }

    struct app* app = &apps[app_option - 1];
    if (app->state == RUNNING) {
        //app->state = ABORTED;
        kill(app->pid, SIGTERM);
        
    }
    else {
        printf("Aplicação não tem uma instancia rodando!\n");
    }

    sleep(1);
}

/**
 * \brief Trata uma opção do menu, encaminhando para a função correspondente a opção.
 * \param option Opção de entrada.
 */
static void handle_option(int option)
{
    switch (option) {
        case 1: {
            launch_web_browser();
            break;
        }
        case 2: {
            launch_text_editor();
            break;
        }
        case 3: {
            launch_terminal();
            break;
        }
        case 4: {
            terminate_app();
            break;
        }
        case 5: {
            printf("Saindo..\n");
            exit(0);
        }
        default: {
            fprintf(stderr, "%s:%d: opção inesperada!\n", __func__, __LINE__);
            fflush(stderr);
            abort();
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
            /* Apenas captura para interromper o polling do STDIN que causará o menu ser
             * atualizado novamente */
            break;
        }
        case SIGCHLD: {
            /* Apenas trata se é uma terminação de filho */
            /* if (info->si_code != CLD_EXITED) {
                return;
            } */

            /* Procura o aplicativo correspondente ao PID filho recebido */
            int app_idx;
            for (app_idx = 0; app_idx < APPS_NUM; app_idx++) {
                if (apps[app_idx].pid == info->si_pid) {
                    break;
                }
            }
            if (app_idx == APPS_NUM) {
                return;
            }
            printf("Received SIGCHD for process %d\n", info->si_pid);
            fflush(stdout);

            /* Atualiza contexto do aplicativo */
            struct app* app = &apps[app_idx];
            app->exit_status = info->si_status;

            /*if (app->state == RUNNING) {
                if (app->exit_status == 127) {
                    app->state = FAILED;
                }
                else {
                    app->state = FINISHED;
                }
            }
            else {
                fprintf(stderr, "%s:%d: Algo deu errado aqui!\n", __func__, __LINE__);
                exit(5);
            }

            break;*/
            app->exit_status = info->si_status;
            //if(info->si_code != CLD_EXITED) return;
            if(app->exit_status == 0) {
                //printf("info->si_code: %d\n", info->si_code);
                //printf("CLD_EXITED: %d\n", CLD_EXITED);
                if(app->state == RUNNING) {
                    app->state = FINISHED;
                    app->pid = NULL;
                }/* else {
                    app->state = RUNNING;
                    app->exit_status = NULL;
                }*/
            } else if(app->exit_status == SIGTERM) {
                app->state = ABORTED;
                app->pid = NULL;
                //kill_msg = "(concluído)";
                snprintf(kill_msg, sizeof(kill_msg), "(concluído)");
            } else if(app->exit_status == 127){
                app->state = FAILED;
                app->pid = NULL;
            }
            break;
        }
        default: {
            printf("Recebido signal inesperado não tratado: %s\n", sig);
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
    sigaction(SIGCHLD, &sigact, NULL);  // Atualização em Processos Filhos
    sigaction(SIGTERM, &sigact, NULL);  // Recebe o sinal de terminação
}

/**
 * Atualiza o contexto as aplicações.
 */
static void update_apps()
{
    for (int i = 0; i < APPS_NUM; i++) {
        struct app* app = &apps[i];
        switch (app->state) {
            case RUNNING: {
                snprintf(app->msg, sizeof(app->msg), "(executando, pid=%d)", app->pid);
                break;
            }
            case FAILED: {
                snprintf(app->msg, sizeof(app->msg), "(falhou)");
                break;
            }
            case ABORTING: {
                snprintf(app->msg, sizeof(app->msg), "(abortando)");
                break;
            }
            case ABORTED: {
                snprintf(app->msg, sizeof(app->msg), "(abortado)");
                break;
            }
            case FINISHED: {
                snprintf(app->msg, sizeof(app->msg), "(concluído)");
                break;
            }
        }
    }
}

/**
 * Ponto de entrada principal do programa.
 */
int main()
{
    /* Registra tratadores de sinal */
    register_signal_handlers();

    while (1) {
        /* Atualiza status das aplicações */
        update_apps();

        /* Apresenta o menu de aplicações */
        print_menu();

        /* Espera entrada com timeout de 5 segundos */
        if (!stdin_available(5000)) {
            continue;
        }

        /* Lê a opção digitada */
        int option = read_option();
        if (!option) {
            fprintf(stderr, "Opção Inválida!\n");
            sleep(1);
            continue;
        }

        /* Realiza as ações do menu */
        handle_option(option);
    }
}
