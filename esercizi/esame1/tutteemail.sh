#!/bin/bash

while read Nome Cognome Matricola Indirizzo; do
	./cercaemail.sh $Nome $Cognome $Matricola;
done < matricola.txt
