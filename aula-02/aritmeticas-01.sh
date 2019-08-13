B=0;
D=0;
echo "Lista completa de argumentos: $*"
echo "argumento: $1 $2"
if [ "X$1" != "X" ]
then
 expr $1 + 0 1>/dev/null 2>&1
 if test $? -lt 2
 then
  B=$1
 fi
fi

if [ "X$2" != "X" ]
then
 expr $2 + 0 1>/dev/null 2>&1
 if test $? -lt 2
 then
  D=$2
 fi
fi
echo "B=$B"
echo "D=$D"
A=$(($B+5*($D/3)))
echo $A
