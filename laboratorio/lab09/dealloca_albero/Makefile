CFLAGS=-ansi -Wall -Wpedantic -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: dealloca_albero.exe

dealloca_albero.exe:	dealloca_albero.o
	gcc ${CFLAGS} -o dealloca_albero.exe dealloca_albero.o ${LIBRARIES}

dealloca_albero.o: dealloca_albero.c
	gcc ${CFLAGS} -c dealloca_albero.c

.PHONY:	clean

clean:
	rm dealloca_albero.exe dealloca_albero.o