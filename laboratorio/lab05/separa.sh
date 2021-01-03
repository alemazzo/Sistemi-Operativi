#!/bin/bash

PPATH=$PATH
#echo $PPATH

while [[ "$PPATH" != "" ]]; do
	ELEM=${PPATH%%:*}
	echo $ELEM
	NEWPATH=${PPATH#*:}
	if [[ "$NEWPATH" == "$PPATH" ]]; then
		break;
	fi;
	PPATH=$NEWPATH	
done;
