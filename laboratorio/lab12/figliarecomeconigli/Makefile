CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L

LIBRARIES=-lpthread

all: 	figliare.exe

figliare.exe: figliare.o DBGpthread.o
	gcc ${CFLAGS} -o figliare.exe figliare.o DBGpthread.o ${LIBRARIES}

figliare.o: figliare.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS} figliare.c

DBGpthread.o: DBGpthread.c printerror.h
	gcc ${CFLAGS} -c DBGpthread.c

.PHONY:	clean

clean:
	-rm -f figliare.o DBGpthread.o figliare.exe


