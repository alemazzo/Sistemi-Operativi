#!/bin/bash

LungNomiDirectory=0;
FileCount=0;

for x in `ls`; do
	if [[ -d ${x} ]]; then
		(( LungNomiDirectory+=${#x} )); 
	else
		(( FileCount+=1 ));
	fi;
done;
echo "LungNomiDirectory = ${LungNomiDirectory}";
echo "FileCount = ${FileCount}";	
