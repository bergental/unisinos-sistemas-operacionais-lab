function calendario {
 echo "Calendario"
 cal
 date
 echo ""
}

function texto {
 echo "Texto"
 echo "Informe o texto a ser passado para o programa:"
 read txt
 gcc texto.c -o texto;
 ./texto "$txt";
}

function contabilidade {
 echo "Contabilidade"
 gcc simplificado.c -o simplificado;
 gcc contabilidade.c -o contabilidade;
 ./contabilidade;
}

function vendas {
 echo "Vendas"
}

function escolherOpcao {
 #clear;
 echo -e "*******************************
********** CONTROLE ***********
*******************************
1 - Calendario	      
2 - Texto
3 - Contabilidade
4 - Vendas
5 - Sair
*******************************

Digite a opção desejada: __

*******************************
*******************************"
 read opcao
 case $opcao in
  1 )
  calendario
  escolherOpcao
  ;;
  2 )
  texto
  escolherOpcao
  ;;
  3 )
  contabilidade
  escolherOpcao
  ;;
  4 )
  vendas
  escolherOpcao
  ;;
  5 )
  echo "Obrigado por utilizar o sistema de controle!"
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