#!/bin/bash

if (( $# != 1 )) ; then
    echo "NUM ARGOMENTI SBAGLIATO" 1>&2;
    exit 1;
fi;

if [[ ! -e $1 ]]; then
    echo "FILE NON ESISTE" 1>&2;
    exit 2
fi;

(sleep 2; cat $1 | tail -n 3 >> ./OUTPUT.txt) &
exit 0;