#!/bin/bash
# Ilustra o uso de argumentos
clear
opcao=0
echo "1) % de memória livre"
echo "2) % de memória usada"
while read -p "Escolha umas das opções acima: " opcao; do
    [[ "$opcao" =~ [[:digit:]]+ ]] && break
    echo "Opção escolhida inválida" >&2
done
echo "Opção escolhida foi: $opcao"
