#!/bin/bash

SRC1=$1
SRC2=$2

conta=1
OUTPUT=./out.txt
echo "" > $OUTPUT;

while (( 1 )); do
    completed=0
    if (( $conta <= $(cat ${SRC1} | wc -l ) )); then
        echo `head -n $conta $SRC1 | tail -n 1` >> $OUTPUT;
        completed=1
    fi;

    if (( $conta <= $(cat ${SRC2} | wc -l) )); then
        completed=1
        echo `head -n $conta $SRC2 | tail -n 1` >> $OUTPUT;
    fi;

    if [[ $completed == 0 ]]; then
        exit 0;
    fi;

    (( conta+=1 ))

done;
