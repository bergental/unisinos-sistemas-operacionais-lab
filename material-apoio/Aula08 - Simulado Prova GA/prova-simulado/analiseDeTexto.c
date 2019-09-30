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


static void signal_handler(int sig, siginfo_t* info, void* ucontext)
{
    switch (sig) {
        case SIGINT: {
            fprintf(stderr, "Envie um sinal de SIGTERM para encerrar o processo!\n");
            break;
        }
        case SIGUSR1: {

            break;
        }
        case SIGUSR2: {

            break;
        }
        default: {
            fprintf(stderr, "Recebido signal inesperado não tratado: %d\n", sig);
            fflush(stderr);
            sleep(1);
        }
    }
}

static void register_signal_handlers()
{
    struct sigaction sigact;
    memset(&sigact, 0, sizeof(struct sigaction));
    sigact.sa_sigaction = signal_handler;
    sigact.sa_flags = SA_SIGINFO;

    sigaction(SIGINT, &sigact, NULL);   // Sinal de Ctrl+C
    sigaction(SIGUSR1, &sigact, NULL);
    sigaction(SIGUSR2, &sigact, NULL);
}


