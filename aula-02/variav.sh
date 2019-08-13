#!/bin/bash
# Um exemplo com variáveis
nomearq="/etc/passwd"
echo "Verifica a permissão no arquivo de senhas"
ls -l $nomearq
echo "Descobre quantas contas existem no sistema"
wc -l $nomearq
