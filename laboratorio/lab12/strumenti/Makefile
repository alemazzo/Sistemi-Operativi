CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L

LIBRARIES=-lpthread

all: 	strumenti.exe

strumenti.exe: strumenti.o DBGpthread.o
	gcc ${CFLAGS} -o strumenti.exe strumenti.o DBGpthread.o ${LIBRARIES}

strumenti.o: strumenti.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS} strumenti.c

DBGpthread.o: DBGpthread.c printerror.h
	gcc ${CFLAGS} -c DBGpthread.c

.PHONY:	clean

clean:
	-rm -f strumenti.o DBGpthread.o strumenti.exe


