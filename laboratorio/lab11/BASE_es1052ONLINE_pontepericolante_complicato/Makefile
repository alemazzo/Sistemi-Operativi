CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L

LIBRARIES=-lpthread

all: 	pontepericolante_complicato.exe

pontepericolante_complicato.exe: pontepericolante_complicato.o DBGpthread.o
	gcc ${CFLAGS} -o pontepericolante_complicato.exe pontepericolante_complicato.o DBGpthread.o ${LIBRARIES}

pontepericolante_complicato.o: pontepericolante_complicato.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS} pontepericolante_complicato.c

DBGpthread.o: DBGpthread.c printerror.h
	gcc ${CFLAGS} -c DBGpthread.c

.PHONY:	clean

clean:
	-rm -f pontepericolante_complicato.o DBGpthread.o pontepericolante_complicato.exe


