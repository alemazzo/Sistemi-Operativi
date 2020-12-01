#!/bin/bash

ricevuto(){
	echo "Sospeso";
	sleep 3;
	(
		sleep 4;
		echo "Hello";
	) &
}

trap ricevuto SIGUSR2;


(
	### Solution 1 - The Best
	sleep 3;
	kill -s SIGUSR2 $$;
	###
) &


source puntini.sh 30


#(
	### Solution 2 - Bad
	#RIGA=`ps | grep "puntini.sh" | grep -v "lanciapuntini.sh" `
	#RIGA=${RIGA/#  }; #rimuovo i due spazi
	#PIDPUNTINI=${RIGA%% *};
	#kill -s SIGTSTP ${PIDPUNTINI};
	#echo "SOSPESO";
	#sleep 3;
	#kill -s SIGCONT ${PIDPUNTINI};
	#sleep 4;
	#echo "hello";
#) &

#source puntini.sh 30
