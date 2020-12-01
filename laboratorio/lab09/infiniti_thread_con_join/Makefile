CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT  -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: 	infiniti_join.exe 

infiniti_join.exe: infiniti_join.o
	gcc ${CFLAGS} -o infiniti_join.exe infiniti_join.o ${LIBRARIES}

infiniti_join.o: infiniti_join.c
	gcc ${CFLAGS} -c infiniti_join.c ${LIBRARIES}


.PHONY:	clean

clean:
	rm -f infiniti_join.o infiniti_join.exe 
