#!/bin/bash

echo -n "" > b.txt
while read num; do
    echo $num
    echo $num >> b.txt;
done;