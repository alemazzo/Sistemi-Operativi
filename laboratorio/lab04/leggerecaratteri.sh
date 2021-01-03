#!/bin/bash
NUM=0;
exec {FD}<./leggere.sh;
if (( $? == 0 )); then
	while read -u ${FD} -N 1 -r C; do
		(( NUM+=1 ));
	done;
	exec {FD}>&-;
fi;
echo "WC = ${NUM}";
