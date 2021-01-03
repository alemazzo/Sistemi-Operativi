#!/bin/bash

ricevutoSIGUSR2() {
	if read RIGA; then
		echo "UNO $RIGA";
		kill -s SIGUSR2 $OTHERPID;
	else
		kill -s SIGUSR2 $OTHERPID;
		exit 0;
	fi;
}
trap ricevutoSIGUSR2 SIGUSR2;


MYPID=$$
echo -n $MYPID > uno.pid.txt
sleep 2;
OTHERPID=`cat due.pid.txt`

if read RIGA; then
	echo "UNO $RIGA";
fi;

kill -s SIGUSR2 $OTHERPID;

while (( 1 )); do
	sleep 1
done;
