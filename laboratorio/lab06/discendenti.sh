#!/bin/bash

NUMFIGLI=$1

if (( $NUMFIGLI == 0 )); then
	echo $NUMFIGLI;
	exit 0;
else
	for (( i=0; i<=$NUMFIGLI; i++ )); do
	./discendenti.sh $(( ${NUMFIGLI}-1 ))
	done;
fi;

for (( i=0; i<=$NUMFIGLI; i++ )); do
	wait;
done;

echo $NUMFIGLI;
exit 0;
