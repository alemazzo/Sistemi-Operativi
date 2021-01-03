#!/bin/bash

[[ `grep "$1 $2 $3" ./matricola.txt` != "" ]] && echo "$1 $2 `grep $3 ./email.txt`"

exit;

if [[ `grep "$1 $2 $3" ./matricola.txt` != "" ]]; then
	echo "$1 $2 `grep $3 ./email.txt`";
fi;

exit;
Nome=$1
Cognome=$2
Matricola=$3


while read Mat Email; do
	if [[ "$Matricola" == "$Mat" && `grep "$Nome $Cognome $Matricola" ./matricola.txt` != "" ]]; then
		echo "$Nome $Cognome $Matricola $Email";
	fi;
done < email.txt
