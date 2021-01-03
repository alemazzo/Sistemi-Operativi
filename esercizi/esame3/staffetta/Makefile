CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L

LIBRARIES=-lpthread

all: 	staffetta.exe

staffetta.exe: staffetta.o DBGpthread.o
	gcc ${CFLAGS} -o staffetta.exe staffetta.o DBGpthread.o ${LIBRARIES}

staffetta.o: staffetta.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS} staffetta.c

DBGpthread.o: DBGpthread.c printerror.h
	gcc ${CFLAGS} -c DBGpthread.c

.PHONY:	clean

clean:
	-rm -f staffetta.o DBGpthread.o staffetta.exe
