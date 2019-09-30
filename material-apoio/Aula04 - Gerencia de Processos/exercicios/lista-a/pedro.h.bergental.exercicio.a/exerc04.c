#include<stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void repete(char *palavra, int count) {
 for(int i = 1; i <= count; i++) {
  printf("#%d '%s' | Meu PID = %d, PPID = %d \n", i, palavra, getpid(), getppid());
  sleep(1);
 }
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
  repete(palavra, count);
  exit(0);
 }
 wait(&status);
 printf("pai terminou\nMeu PID = %d, PPID = %d \n", getpid(), getppid());
}
