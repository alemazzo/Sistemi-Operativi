#!/bin/bash
TOT_SEC=$1
COUNT=0
while (( $COUNT != $TOT_SEC )); do
	sleep 1
	(( COUNT+=1 ))
	echo -n "." $$
done;
echo ""

