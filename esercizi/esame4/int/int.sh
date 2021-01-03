#!/bin/bash

for file in `find /usr/include/linux -type f -name "*.h"`; do
    if [[ `cat $file | grep int` != "" ]]; then
        for line in `cat $file | grep int`; do
            echo $line | cut -c -3
        done;
    fi;
done;