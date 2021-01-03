#!/bin/bash
for elem in `ls /usr/include`; do
	ABS="/usr/include/$elem";
	if [[ -d $ABS  && -e $ABS && $ABS -nt "/usr/include/stdio.h" ]]; then
		echo $ABS;
	fi;
done;
