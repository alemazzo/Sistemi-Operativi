#!/bin/bash
NUM=0
while (( ${NUM} <= $1 )) ; do
	sleep 1;
	echo -n ". ${BASHPID}";
	(( NUM=${NUM}+1 ))
done
