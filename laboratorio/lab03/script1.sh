#!/bin/bash

for arg in "$@"; do
	echo "$arg";
done;

./script2.sh "$@";
