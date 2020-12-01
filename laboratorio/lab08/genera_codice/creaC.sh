#!/bin/bash

OUTPUT_FILE=./variabiliglobali.c
echo "" > $OUTPUT_FILE;

while read KEYWORD NAME VALUE; do
    if [[ $NAME == "NUM" ]]; then
        for((i=1; i <= $VALUE; i++)); do
            echo "int var$i = $i;" >> $OUTPUT_FILE;
        done

        echo -e "\nint conta(){" >> $OUTPUT_FILE;
        echo -e -n "\treturn var1" >> $OUTPUT_FILE;
        for((i=2; i <= $VALUE; i++)); do
            echo -n -e "\n\t+ var$i" >> $OUTPUT_FILE;
        done
        echo -e ";\n}" >> $OUTPUT_FILE;

    fi;
done < ./define.h
