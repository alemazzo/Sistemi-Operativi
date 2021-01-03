#!/bin/bash

if (( $1 == 0 )); then
	echo "ARG = 0 => END"
else
	(( NEXT=$1-1 ))
	echo "ARG = $1 => Call ./lanciaricorsivo $NEXT"
	./lanciaricorsivo.sh $NEXT &
	echo "$!"
	wait $!
fi;
