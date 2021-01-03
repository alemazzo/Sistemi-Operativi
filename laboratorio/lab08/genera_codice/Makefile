CFLAGS=-ansi -Wall -Werror -Wpedantic -pedantic
SHELL=/bin/bash

all:	main.exe

main.exe: main.o variabiliglobali.o
	gcc ${CFLAGS} -o main.exe main.o variabiliglobali.o

main.o: main.c variabiliglobali.h
	gcc ${CFLAGS} -c main.c

variabiliglobali.o:	variabiliglobali.h variabiliglobali.c
	gcc ${CFLAGS} -c variabiliglobali.c

variabiliglobali.h: define.h
	./creaH.sh

variabiliglobali.c:	define.h
	./creaC.sh


