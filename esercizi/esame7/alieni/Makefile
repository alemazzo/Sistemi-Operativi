CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L

LIBRARIES=-lrt -lpthread
DBGPTHREADFUNCTION_SOURCE_DIR=./

all: 	 alieni.exe

alieni.exe:  alieni.o DBGpthread.o 
			gcc ${CFLAGS} -o alieni.exe alieni.o DBGpthread.o ${LIBRARIES}

alieni.o: alieni.c ${DBGPTHREADFUNCTION_SOURCE_DIR}DBGpthread.h ${DBGPTHREADFUNCTION_SOURCE_DIR}printerror.h
			gcc -c ${CFLAGS} -I${DBGPTHREADFUNCTION_SOURCE_DIR} alieni.c 

DBGpthread.o: ${DBGPTHREADFUNCTION_SOURCE_DIR}DBGpthread.c ${DBGPTHREADFUNCTION_SOURCE_DIR}printerror.h
			gcc ${CFLAGS} -c ${DBGPTHREADFUNCTION_SOURCE_DIR}DBGpthread.c -I${DBGPTHREADFUNCTION_SOURCE_DIR} 


.PHONY:	clean

clean:
	-rm -f alieni.o DBGpthread.o alieni.exe


