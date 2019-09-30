#include <stdio.h>

int main(void)
{
  /*Criando a struct */
  struct ficha_de_aluno
  {
    char nome[50];
    char disciplina[30];
    float nota_prova1;
    float nota_prova2;
  };
  
  /*Criando a variável aluno que será do
  tipo struct ficha_de_aluno */
  struct ficha_de_aluno aluno;
  
  printf("\n---------- Cadastro de aluno -----------\n\n\n");
  
  printf("Nome do aluno ......: ");
  //fflush(stdin);
  
  /*usaremos o comando fgets() para ler strings, no caso o nome
  do aluno e a disciplina
  fgets(variavel, tamanho da string, entrada)
  como estamos lendo do teclado a entrada é stdin (entrada padrão),
  porém em outro caso, a entrada tambem poderia ser um arquivo */
  
  scanf(" %s", aluno.nome);
  //fgets(aluno.nome, 40, stdin);
  
  printf("\nDisciplina ......: ");
  scanf(" %s", aluno.disciplina);
  //fflush(stdin);
  //fgets(aluno.disciplina, 40, stdin);
  
  printf("\nInforme a 1a. nota ..: ");
  
  scanf("%f", &aluno.nota_prova1);
  
  printf("\nInforme a 2a. nota ..: ");
  scanf("%f", &aluno.nota_prova2);
  
  printf("\n\n --------- Lendo os dados da struct ---------\n\n");
  printf("Nome ...........: %s", aluno.nome);
  printf("\nDisciplina .....: %s", aluno.disciplina);
  printf("\nNota da Prova 1 ...: %.2f" , aluno.nota_prova1);
  printf("\nNota da Prova 2 ...: %.2f\n" , aluno.nota_prova2);
  
  //getch();
  return(0);
}