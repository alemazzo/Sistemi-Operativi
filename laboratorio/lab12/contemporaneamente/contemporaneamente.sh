#!/bin/bash

i=1;
for file in $@; do
    if (( $i % 2 == 0 )); then
        echo `cat $file | wc -l`;
    else
        echo "ERR = `cat $file | wc -l`" 1>&2;
    fi;
    ((i+=1));
done;