#!/bin/bash

res=""
while read anno localita motivo danni; do
    str=`cat ./cadutevic.txt | grep $motivo | wc -l`;
    res+="$motivo = $str\n";
done < ./cadutevic.txt 
echo -e $res | sort | uniq
