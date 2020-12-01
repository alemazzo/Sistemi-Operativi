CFLAGS=-ansi -Wpedantic -Wall -Werror -D_POSIX_SOURCE

all: 	casuale.exe 

casuale.exe: casuale.o
	gcc ${CFLAGS} -o casuale.exe casuale.o ${LIBRARIES}

casuale.o: casuale.c
	gcc ${CFLAGS} -c casuale.c ${LIBRARIES}


.PHONY:	clean

clean:
	rm -f casuale.o casuale.exe 

