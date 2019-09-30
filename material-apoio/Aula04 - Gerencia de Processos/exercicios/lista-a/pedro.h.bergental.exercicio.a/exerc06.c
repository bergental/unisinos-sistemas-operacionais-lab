#include<stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int repete(char *palavra, int count) {
 if(count > 10 || count < 0)
  return 99;
 for(int i = 1; i <= count; i++) {
  printf("#%d '%s' | Meu PID = %d, PPID = %d \n", i, palavra, getpid(), getppid());
  sleep(1);
 }
 return 0;
}

int main(int argc, char *argv[]){
 int count = 0;
 char *palavra = argv[1];
 int status;
 pid_t pid;
 printf("\nInforme quantas vezes quer que repita a palavra: ");
 scanf("%d", &count);

 pid = fork();
 if(pid == 0) {
 int d = repete(palavra, count);
  exit(d);
 }

 wait(&status);
 status = WEXITSTATUS(status);
 if(status == 0) {
  printf("Processo fiho executou sem falhas\n");
 } else if(status == 99) {
  printf("Processo fiho terminou com o error pelo inteiro não estar entre 0 e 10\n");
 } else {
  printf("Processo fiho terminou com o error não esperado\n");
 }
 printf("pai terminou\nMeu PID = %d, PPID = %d \n", getpid(), getppid());
}
