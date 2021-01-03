CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT  -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: piattello.exe

piattello.exe:	piattello.o	DBGpthread.o
	gcc ${CFLAGS} -o piattello.exe piattello.o DBGpthread.o	${LIBRARIES}

DBGpthread.o:	DBGpthread.c
	gcc ${CFLAGS} -c DBGpthread.c	${LIBRARIES}

piattello.o:	piattello.c	DBGpthread.h
	gcc ${CFLAGS} -c piattello.c DBGpthread.h	${LIBRARIES}

.PHONY:	clean

clean:
	-rm *.o *.exe