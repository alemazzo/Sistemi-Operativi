#!/bin/bash

if [[ $# != 2 ]]; then
	echo "Numero Argomenti Errato" 1>&2;
	exit 1;
fi;

File=$1
Stringa=$2

if [[ ! -e $File ]]; then
	echo "Argomento Non File" 1>&2;
	exit 2;
fi;

( sleep 2; echo "`grep $Stringa $File | wc -l`" >> OUTPUT.txt ) &
exit 0;
