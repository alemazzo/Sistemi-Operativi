CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT  -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: banche.exe

banche.exe:	banche.o	DBGpthread.o
	gcc ${CFLAGS} -o banche.exe banche.o DBGpthread.o	${LIBRARIES}

DBGpthread.o:	DBGpthread.c
	gcc ${CFLAGS} -c DBGpthread.c	${LIBRARIES}

banche.o:	banche.c	DBGpthread.h
	gcc ${CFLAGS} -c banche.c DBGpthread.h	${LIBRARIES}

.PHONY:	clean

clean:
	-rm *.o *.exe