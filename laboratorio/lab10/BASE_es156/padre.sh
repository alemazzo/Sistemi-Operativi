#!/bin/bash


handle_sig(){
    echo "EXIT"
    exit 0;
}
trap handle_sig SIGUSR2;

./figlio.sh &
while (( 1 )); do
    sleep 1;
done;