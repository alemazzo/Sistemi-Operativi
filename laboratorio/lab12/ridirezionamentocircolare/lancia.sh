#!/bin/bash

echo -n "" > ./atob.txt
echo -n "" > ./btoa.txt
echo -n "" > ./b.txt


(tail -f btoa.txt | ./a.sh 1> atob.txt) &
echo $!;

(tail -f atob.txt | ./b.sh 1> btoa.txt) &
echo $!

tail -f b.txt
