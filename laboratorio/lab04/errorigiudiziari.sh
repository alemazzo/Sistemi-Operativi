#!/bin/bash

exec {DENUNCE}<./denunce.txt

while read -u ${DENUNCE} A B C D; do
	exec {PROCESSI}<./processi.txt
	while read -u ${PROCESSI} E F; do
		if [[ "$E" == "$C" ]]; then
			exec {VERDETTI}<./verdetti.txt
			while read -u ${VERDETTI} G H; do
				if [[ "$F" == "$G" ]]; then
					echo $A $B $D $H;
				fi;
			done;
		fi;
	done;
done;
