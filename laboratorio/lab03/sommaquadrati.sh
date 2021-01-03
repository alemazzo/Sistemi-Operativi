#!/bin/bash

(( SUM=0 ));
for arg in "$@"; do
	(( QUADRATO=${arg}*${arg} ));
	(( SUM=${SUM}+${QUADRATO} )); 
done;
echo $SUM;
