#!/bin/bash

FILENAME="$1";
OUT="";

exec {FD}<"${FILENAME}";
if (( $? == 0 )); then
	while read -u ${FD} A B C; do
		OUT+="${B} ";
	done;
	exec {FD}>&-;
	echo ${OUT};
fi;
