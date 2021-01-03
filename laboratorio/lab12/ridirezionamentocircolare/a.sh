#!/bin/bash

echo 1;
while read num; do
    sleep 1;
    (( num+=1 ))
    echo $num
done;