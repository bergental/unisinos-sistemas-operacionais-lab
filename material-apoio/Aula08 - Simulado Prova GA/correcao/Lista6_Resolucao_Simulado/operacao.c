#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int i;

	if (argc < 3){
		printf("Não foram informadas 3 instruções pela linha de comando!\n");
	}
	else{
		for (i=3;i>=1;i--)
		{
			printf("\nExecutando comando %d: \n\n", i);
			system(argv[i]);
			system("sleep 5");
		}
		printf("\n");
		system("date");
		printf("Processamento concluído! Obrigado e até logo!\n");
	}
	return 0;
}
