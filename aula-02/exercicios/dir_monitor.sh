#!/bin/bash
echo "MON_DIR=$MON_DIR"
if [ ! -d $MON_DIR ]; then
 echo "[$(date)] A variável MON_DIR não é um diretório válido!" > /dev/stderr
 exit 2
fi
