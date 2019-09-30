#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int contador;

void load_firefox(char *url[]){
	//int status;
        pid_t p = fork();                                       
        if (p < 0) {                                            
                fprintf(stderr, "Falha na criação do novo processo! \n");
                exit(13);                                       
        } else if (p == 0) {                                    
                printf("Filho iniciando %s... \n", url[contador]); 
                execlp("firefox","firefox --new-window", url[contador], NULL);                  
                printf("Filho com parada de execução forçada! \n"); 
                exit(14);
        } else {       
                printf("Pai esperando... \n"); 
		//wait(&status);
		sleep(5);
		if(--contador>0) load_firefox(url);
                printf("Pai finalizando... \n"); 
                exit(0);
        }
}

void start_browser(char *url[]){
        load_firefox(url);
}

int main(int argc, char *argv[]){
	
	contador = --argc;
	if(contador < 1){
		printf("Informe pelo menos 1 URL!\n");
		return 99;
	}
	
	start_browser(argv);

	return 0;
}

