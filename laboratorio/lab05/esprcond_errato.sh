#!/bin/bash

if [[ -e /usr/include/stdio.h ]]; then echo esiste; fi
head -n 5 /usr/include/stdio.h | tail -n 3
tail -n 3 /usr/include/stdio.h | cut -c -3
 
