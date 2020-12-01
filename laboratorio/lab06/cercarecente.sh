#!/bin/bash

FILES=`find /usr/include/linux/*/ -name "*.h"`

for REC in ${FILES}; do
	break;
done;

for file in ${FILES}; do
	if [[ ${file} -nt ${REC} ]]; then
		REC=${file}
	fi;
done;
echo "Il file più recente è ${REC}";
