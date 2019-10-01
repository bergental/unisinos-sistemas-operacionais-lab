#include<stdio.h>
#include<stdlib.h>

/*
6.3 - Dever� calcular e exibir na sa�da padr�o: O valor de custo total do produto � R$ XX,XX (custo total do produto = quantidade x pre�o custo unit�rio).
[Exemplo: O valor de custo total do produto � R$ 100,00 (10 x R$ 10,00)]
*/
float custoTotal(int qtd, float preco) {
    return qtd * preco;
}

/*
6.4 - O valor de margem de contribui��o � XX,XX (calcular 50% sobre o valor de custo total).
[Exemplo: O valor de margem de contribui��o � R$ 50,00]
 */
float margemDeContribuicao(float custoTotal) {
    return custoTotal * 0.5;
}
/*
6.5 - O valor do ICMS para o produto � R$ XX,XX (calcular 17% sobre o valor de custo total + margem de contribui��o).
[Exemplo: O valor do ICMS para o produto �: R$ 25,50] */
float ICMS(float custoTotal, float margemDeContribuicao) {
    return (custoTotal + margemDeContribuicao) * 0.17;
}
/*
6.6 - O valor de venda do produto � R$ XX,XX (somat�ria dos valores 6.3, 6.4 e 6.5).
[Exemplo: O valor de venda do produto � R$ 175,50].
 */
float valorDeVenda(float custoTotal, float margemDeContribuicao, float ICMS) {
    return custoTotal + margemDeContribuicao + ICMS;
}

void buscarValores() {
    int qty;
    float price;
    printf("Quantidade e pre�o de custo unitário: ");
	scanf("%d", &qty);
	scanf("%f", &price);
    //getchar();
    if(qty < 0 || price < 0) {
        printf("Valores inválidos\n");
        buscarValores();
    }

    float ct = custoTotal(qty, price);
    float mdc = margemDeContribuicao(ct);
    float 

    
}

int main(int argc, char *argv[]){
    buscarValores();
}