CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L

LIBRARIES=-lrt -lpthread
DBGPTHREADFUNCTION_SOURCE_DIR=./

all: 	 funiviacomplicato.exe

funiviacomplicato.exe:  funiviacomplicato.o DBGpthread.o 
			gcc ${CFLAGS} -o funiviacomplicato.exe funiviacomplicato.o DBGpthread.o ${LIBRARIES}

funiviacomplicato.o: funiviacomplicato.c ${DBGPTHREADFUNCTION_SOURCE_DIR}DBGpthread.h ${DBGPTHREADFUNCTION_SOURCE_DIR}printerror.h
			gcc -c ${CFLAGS} -I${DBGPTHREADFUNCTION_SOURCE_DIR} funiviacomplicato.c 

DBGpthread.o: ${DBGPTHREADFUNCTION_SOURCE_DIR}DBGpthread.c ${DBGPTHREADFUNCTION_SOURCE_DIR}printerror.h
			gcc ${CFLAGS} -c ${DBGPTHREADFUNCTION_SOURCE_DIR}DBGpthread.c -I${DBGPTHREADFUNCTION_SOURCE_DIR} 


.PHONY:	clean

clean:
	-rm -f funiviacomplicato.o DBGpthread.o funiviacomplicato.exe


