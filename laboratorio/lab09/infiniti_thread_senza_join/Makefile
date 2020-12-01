CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT  -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: 	infiniti.exe 

infiniti.exe: infiniti.o
	gcc ${CFLAGS} -o infiniti.exe infiniti.o ${LIBRARIES}

infiniti.o: infiniti.c
	gcc ${CFLAGS} -c infiniti.c ${LIBRARIES}


.PHONY:	clean

clean:
	rm -f infiniti.o infiniti.exe 
