#!/bin/bash

function calculadora {
 echo "Calculadora"
 gcc calculadora.c -o calculadora;
 ./calculadora;
}

function analiseDeTexto {
 echo "Análise de texto"
}

function automacaoDeOperacoes {
 echo "Automação de operações"
}

function gestaoDeProcessos {
 echo "Gestão de processos"
}

function escolherOpcao {
 #clear;
 echo -e "************* CANIVETE SUICO *************

1 - Calculadora
2 - Análise de texto
3 - Automação de operações
4 - Gestão de processos
5 - Sair

******************************************

Digite a opção desejada: __

******************************************"
 read opcao
 case $opcao in
  1 )
  calculadora
  escolherOpcao
  ;;
  2 )
  analiseDeTexto
  escolherOpcao
  ;;
  3 )
  automacaoDeOperacoes
  escolherOpcao
  ;;
  4 )
  gestaoDeProcessos
  escolherOpcao
  ;;
  5 )
  echo "saindo"
  return 0
  ;;
  *)
  echo "opção inválida!"
  escolherOpcao
  ;;
 esac
 return 0
}

escolherOpcao
