CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L

LIBRARIES=-lrt -lpthread
DBGPTHREADFUNCTION_SOURCE_DIR=./

all: 	 megapizze.exe

megapizze.exe:  megapizze.o DBGpthread.o 
			gcc ${CFLAGS} -o megapizze.exe megapizze.o DBGpthread.o ${LIBRARIES}

megapizze.o: megapizze.c ${DBGPTHREADFUNCTION_SOURCE_DIR}DBGpthread.h ${DBGPTHREADFUNCTION_SOURCE_DIR}printerror.h
			gcc -c ${CFLAGS} -I${DBGPTHREADFUNCTION_SOURCE_DIR} megapizze.c 

DBGpthread.o: ${DBGPTHREADFUNCTION_SOURCE_DIR}DBGpthread.c ${DBGPTHREADFUNCTION_SOURCE_DIR}printerror.h
			gcc ${CFLAGS} -c ${DBGPTHREADFUNCTION_SOURCE_DIR}DBGpthread.c -I${DBGPTHREADFUNCTION_SOURCE_DIR} 


.PHONY:	clean

clean:
	-rm -f megapizze.o DBGpthread.o megapizze.exe


