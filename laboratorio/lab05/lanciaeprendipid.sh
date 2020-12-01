#!/bin/bash

for (( I=0; $I<10; I+=1 )); do
	./puntini.sh 10 1>&2 &
	echo -n "$! "
done;
