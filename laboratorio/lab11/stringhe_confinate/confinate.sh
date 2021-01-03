#!/bin/bash

while read riga; do
    riga=${riga#*\"*\"*\"*\"*\"};
    echo ${riga%%\"*}
done < ./cadutevic.txt 