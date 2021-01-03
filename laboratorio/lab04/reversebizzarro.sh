#!/bin/bash

STRINGA=$1;
LEN=${#STRINGA};

#echo "STRINGA = $STRINGA";
#echo "LEN = $LEN";

for (( i=1; $i<=$LEN; i+=1 )); do
	OUT=`echo $STRINGA | cut -c $i`$OUT;
done;
echo $OUT;





