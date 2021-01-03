CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L

LIBRARIES=-lrt -lpthread
DBGPTHREADFUNCTION_SOURCE_DIR=./

all: 	 attacchini.exe

attacchini.exe:  attacchini.o DBGpthread.o 
			gcc ${CFLAGS} -o attacchini.exe attacchini.o DBGpthread.o ${LIBRARIES}

attacchini.o: attacchini.c ${DBGPTHREADFUNCTION_SOURCE_DIR}DBGpthread.h ${DBGPTHREADFUNCTION_SOURCE_DIR}printerror.h
			gcc -c ${CFLAGS} -I${DBGPTHREADFUNCTION_SOURCE_DIR} attacchini.c 

DBGpthread.o: ${DBGPTHREADFUNCTION_SOURCE_DIR}DBGpthread.c ${DBGPTHREADFUNCTION_SOURCE_DIR}printerror.h
			gcc ${CFLAGS} -c ${DBGPTHREADFUNCTION_SOURCE_DIR}DBGpthread.c -I${DBGPTHREADFUNCTION_SOURCE_DIR} 


.PHONY:	clean

clean:
	-rm -f attacchini.o DBGpthread.o attacchini.exe


