CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT  -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: 	main.exe 

main.exe: main.o
	gcc ${CFLAGS} -o main.exe main.o ${LIBRARIES}

main.o: main.c
	gcc ${CFLAGS} -c main.c ${LIBRARIES}


.PHONY:	clean

clean:
	rm -f main.o main.exe 
