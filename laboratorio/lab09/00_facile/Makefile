# MakefileBanali

CFLAGS=-ansi -Wpedantic -Wall -D_THREAD_SAFE -D_REENTRANT -D_POSIX_C_SOURCE=200112L
LFLAGS=-lpthread

all: facile.exe

facile.exe: facile.o
	gcc ${CFLAGS} -o facile.exe facile.o ${LFLAGS}

facile.o: facile.c
	gcc -c ${CFLAGS} facile.c

.PHONY:	clean

clean:
	rm -f facile.exe facile.o