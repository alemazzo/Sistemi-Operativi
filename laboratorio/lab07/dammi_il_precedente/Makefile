CFLAGS= -ansi -Wall -Wpedantic -pedantic -Werror

all:	main.exe

main.exe:	main.o
	gcc ${CFLAGS} -o main.exe main.o -lm

main.o:	main.c
	gcc ${CFLAGS} -c main.c

.PHONY:
	clean

clean:
	rm -rf *.o *.exe
