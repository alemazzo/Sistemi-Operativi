#!/bin/bash


for file in `find /usr/include/linux/ -name "*.h" -mindepth 2`; do
    if [[ $file -nt $result ]]; then
        result=$file;
    fi;
done;

echo $result;