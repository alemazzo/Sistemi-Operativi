#!/bin/bash

CHARS="\* \[ \] \?"
while read RIGA; do
	SAFE=$RIGA
	for CH in ${CHARS}; do
		SAFE=${SAFE//"$CH"/"\\$CH"}
	done;
	echo $SAFE
done;
