CFLAGS=-ansi -Wpedantic -Wall -pedantic
HEADER=./header/
SRC=./src/

all:	main.exe

main.exe:	${SRC}main.o ${SRC}quadrato.o ${SRC}dimezza.o
		gcc ${CFLAGS} -o main.exe main.o quadrato.o dimezza.o -lm

main.o:	${SRC}main.c ${HEADER}dimezza.h ${HEADER}quadrato.h
		gcc -c ${CFLAGS} .I${HEADER} ${SRC}main.c

quadrato.o: ${SRC}quadrato.c	
		gcc -c ${CFLAGS} ${SRC}quadrato.c

dimezza.o:	${SRC}dimezza.c
		gcc -c ${CFLAGS} ${SRC}dimezza.c

.PHONY:		clean


clean:	
		rm -f *.exe *.o

