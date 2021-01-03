CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L

LIBRARIES=-lpthread

all: 	funivia.exe

funivia.exe: funivia.o DBGpthread.o
	gcc ${CFLAGS} -o funivia.exe funivia.o DBGpthread.o ${LIBRARIES}

funivia.o: funivia.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS} funivia.c

DBGpthread.o: DBGpthread.c printerror.h
	gcc ${CFLAGS} -c DBGpthread.c

.PHONY:	clean

clean:
	-rm -f funivia.o DBGpthread.o funivia.exe
