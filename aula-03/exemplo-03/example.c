#include <stdio.h>
void cadastra_cliente() {
 printf("--->[1] Cadastrar cliente\n\n");
}

void procura_cliente() {
 printf("--->[2] Procurar cliente\n\n");
}

void insere_pedido() {
 printf("--->[3] Inserir pedido\n\n");
}

int escolhe_opcao() {
 int opcao;
 printf("[1] Cadastrar cliente\n"
         "[2] Procurar cliente\n"
         "[3] Inserir pedido\n"
         "[0] Sair\n\n""Digite sua escolha: ");
 scanf ("%d", &opcao);
 switch (opcao) {
  case 1:
   cadastra_cliente(); 
   break;
  case 2:
   procura_cliente(); 
   break;
  case 3:
   insere_pedido();
   break;
  case 0:
   return 0;
  default:
   printf ("Opção inválida!\n");
 }
 return opcao;
}

int main(){
 int opcao = escolhe_opcao();
 while (opcao != 0) {
  opcao = escolhe_opcao();
 }
 return opcao;
}
