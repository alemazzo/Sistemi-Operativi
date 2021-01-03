CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT  -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: pontepericolante_semplice.exe

pontepericolante_semplice.exe:	pontepericolante_semplice.o	DBGpthread.o
	gcc ${CFLAGS} -o pontepericolante_semplice.exe pontepericolante_semplice.o DBGpthread.o	${LIBRARIES}

DBGpthread.o:	DBGpthread.c
	gcc ${CFLAGS} -c DBGpthread.c ${LIBRARIES}

pontepericolante_semplice.o:	pontepericolante_semplice.c	DBGpthread.h
	gcc ${CFLAGS} -c pontepericolante_semplice.c DBGpthread.h 	${LIBRARIES}

.PHONY:	clean

clean:
	-rm *.o *.exe