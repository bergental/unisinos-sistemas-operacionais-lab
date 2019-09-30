#!/bin/bash
#echo "MON_DIR=$MON_DIR"
if [ ! -d $MON_DIR ]; then
 "[$(date)] A variável MON_DIR não é um diretório válido!" >> /dev/stderr
 exit 2
fi

INFO_ITENS=$(ls -l $MON_DIR)
INFO_ITENS_TEMP=""
while true; do
 INFO_ITENS_TEMP=$(ls -l $MON_DIR)
 if [ "$INFO_ITENS_TEMP" != "$INFO_ITENS" ]; then
  INFO_ITENS=$INFO_ITENS_TEMP
  echo "lista de parametros: $*"
  bash -c $*&
 fi
 sleep 2
done
