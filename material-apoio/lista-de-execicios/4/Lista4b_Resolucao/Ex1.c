#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void load_firefox(char url[]){
	//int status;
        pid_t p = fork();                                       
        if (p < 0) {                                            
                fprintf(stderr, "Falha na criação do novo processo! \n");
                exit(13);                                       
        } else if (p == 0) {                                    
                printf("Filho iniciando... \n"); 
                execlp("firefox","firefox --new-window", url, NULL);                  
		//execlp("/bin/ls", "ls", NULL);			/* atribui novo programa ao filho */
		//execlp("/usr/bin/firefox","firefox" ,"--new-window", url, NULL);
		//system("/usr/bin/firefox","firefox" ,"--new-window", url, NULL);
                printf("Filho com parada de execução forçada! \n"); 
                exit(14);
        } else {       
                printf("Pai esperando... \n"); 
		//wait(&status);
                printf("Pai finalizando... \n"); 
                exit(0);
        }
}

int main(){

    char url[]="terra.com.br";
    load_firefox(url);
    //execlp("firefox","firefox --new-window", url, NULL);                  
    return 0;
}

