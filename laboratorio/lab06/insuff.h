#!/bin/bash

while read Nome Cognome Matricola Voto; do
	if (( ${Voto} < 18 )); then
		if [[ `grep "$Matricola" RisultatiProvaPratica1.txt ` == "" ]]; then
			echo "$Matricola $Nome $Cognome $Voto";
		fi;
	fi;
done < RisultatiProvaPratica2.txt
