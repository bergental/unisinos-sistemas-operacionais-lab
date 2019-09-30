#!/bin/bash
if [ ! -d  "$MON_DIR" ]; then
	echo "Não é um diretório válido!" >&2
	exit 1
elif [ -z "$MON_DIR" ]; then
	echo "Diretório nulo. Não informado!" >&2
	exit 2
else
	echo "Diretório válido: $MON_DIR"
	exit 0
fi

