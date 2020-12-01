#!/bin/bash

rm -f ./out.txt
for((i=0; i < 10; i++)); do
    ../genera/genera.sh ./out.txt
done

sum=0
while read VAL; do
    (( sum+=$VAL ))
done < ./out.txt
echo "SUM = $sum";


