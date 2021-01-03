CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT  -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: fachiri.exe

fachiri.exe:	fachiri.o	DBGpthread.o
	gcc ${CFLAGS} -o fachiri.exe fachiri.o DBGpthread.o	${LIBRARIES}

DBGpthread.o:	DBGpthread.c
	gcc ${CFLAGS} -c DBGpthread.c	${LIBRARIES}

fachiri.o:	fachiri.c	DBGpthread.h
	gcc ${CFLAGS} -c fachiri.c DBGpthread.h	${LIBRARIES}

.PHONY:	clean

clean:
	-rm *.o *.exe