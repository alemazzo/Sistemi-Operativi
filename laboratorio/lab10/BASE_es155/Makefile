CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT  -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: vacche.exe

vacche.exe:	vacche.o	DBGpthread.o
	gcc ${CFLAGS} -o vacche.exe vacche.o DBGpthread.o	${LIBRARIES}

DBGpthread.o:	DBGpthread.c
	gcc ${CFLAGS} -c DBGpthread.c	${LIBRARIES}

vacche.o:	vacche.c	DBGpthread.h
	gcc ${CFLAGS} -c vacche.c DBGpthread.h	${LIBRARIES}

.PHONY:	clean

clean:
	-rm *.o *.exe