#!/bin/bash

for PID in `./lanciaeprendipid.sh`; do
	kill -9 $PID;
done;
