#!/bin/bash

for file in /usr/include/?[c-g]*; do
	if test ${#file} -lt 18 -o ${#file} -gt 23; then
		echo $file;
	fi;
done;
