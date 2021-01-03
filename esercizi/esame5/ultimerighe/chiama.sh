#!/bin/bash

./ultimerighe.sh /usr/include/stdio.h
./ultimerighe.sh ./VICSCEMO.txt
if (( $? != 0 )); then
    echo "SBAGLIATOOO"
fi;