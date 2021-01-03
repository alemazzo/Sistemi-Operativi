#!/bin/bash

OUTPUT_FILE=./variabiliglobali.h

while read KEYWORD NAME VALUE; do
    if [[ $NAME == "NUM" ]]; then
        echo "int conta(void);" > $OUTPUT_FILE;
        for((i=1; i <= $VALUE; i++)); do
            echo "extern int var$i;" >> $OUTPUT_FILE;
        done
    fi;
done < ./define.h
