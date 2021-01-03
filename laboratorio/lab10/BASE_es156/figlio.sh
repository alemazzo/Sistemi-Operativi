#!/bin/bash

sleep 1;

padre=${PPID};
echo "padre = $padre";
kill -SIGUSR2 $padre;
