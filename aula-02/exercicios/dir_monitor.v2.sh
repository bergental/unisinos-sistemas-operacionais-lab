#!/bin/bash
echo "MON_DIR=$MON_DIR"
if [ ! -d $MON_DIR ]; then
 "[$(date)] A variável MON_DIR não é um diretório válido!" >> /dev/stderr
 exit 2
fi

while true; do
 ls -1 $MON_DIR
 echo -e " "
 sleep 2
done
