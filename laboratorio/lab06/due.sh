#!/bin/bash

ricevutoSIGUSR2() {
	if read RIGA; then
		echo "DUE $RIGA"
		kill -s SIGUSR2 $OTHERPID;
	else
		kill -s SIGUSR2 $OTHERPID;
		exit 0;
	fi;
}
trap ricevutoSIGUSR2 SIGUSR2;


MYPID=$$
echo -n $MYPID > due.pid.txt
sleep 2;
OTHERPID=`cat uno.pid.txt`

while (( 1 )); do
	sleep 1
done;
