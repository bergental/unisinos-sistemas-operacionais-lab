#!/bin/bash

while [ 1 ]; do
	clear
	
	echo "************* CANIVETE SUICO *************"
	echo "Digite a opção desejada:"
	echo "1 - Calculadora"
	echo "2 - Análise de texto"
	echo "3 - Automação de operações"
	echo "4 - Gestão de processos"
	echo "5 - Sair"
	echo "******************************************"
	echo "Digite a opção desejada: "
	read opcao 
	echo "******************************************"

	case "$opcao" in
		1 )
			gcc -Wall calculadora.c -o calculadora
			./calculadora
		;;
		2 )
			echo "Digite uma palavra:"
			read palavra 
			gcc -Wall texto.c -o texto
			./texto $palavra
		;;
		3 )
			echo "Digite os 3 comandos: "
			read argumento
			gcc -Wall operacao.c -o operacao
			./operacao $argumento
		;;
		4 )
			gcc -Wall processo.c -o processo
			./processo $url
		;;
		5 )
			echo "Encerrando o canivete suíço... Obrigado! "
			exit 0
	esac  
	sleep 3
done
