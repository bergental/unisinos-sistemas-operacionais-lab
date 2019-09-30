#include <stdio.h>
#include <string.h>

void converter_binario(long int valorDecimal) {
  char convertido[128];
  long int valorBinario = 0;
  int resto, i = 1;

  while (valorDecimal!=0) {
      resto = valorDecimal%2;
      valorDecimal /= 2;
      valorBinario += resto*i;
      i *= 10;
  }

  sprintf(convertido, "%ld", valorBinario);

  for (int i=strlen(convertido); i>=0; i--) {
    printf("%c ", convertido[i]);
  }
}

int main() {
	long int valorDecimal;
	
	printf("Digite o valor em decimal:\n");
	scanf("%ld", &valorDecimal);
	
	printf("\nValor em binário:");
  	converter_binario(valorDecimal);

	return 0;
}
