NUM=$1;
if [[ ${NUM}>1 ]]; then
	(( RIS=${RIS}*${NUM} ));
	NUM=$(( ${NUM} - 1));
	source fattoriale1.sh "$NUM";
fi;
