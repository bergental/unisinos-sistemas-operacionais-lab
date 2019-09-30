#include <stdio.h>

void repete(int numeroRepeticao, char *palavra){
  for(int i=0; i<numeroRepeticao; i++) {
    printf("#%d '%s'\n", i+1, palavra);
  }
}

int main(int argc, char *argv[]) {
  int nro;
  if(argc == 2) {
    printf("Digite o número de repetições: \n");
    scanf("%d", &nro);
    repete(nro,argv[1]);
  } else {
    printf("Número de argumentos inválido! Deve ser digitado um parâmetro na linha de comando!\n");
  }

  return 0;
}
