CFLAGS=-ansi -Wpedantic -Wall -pedantic

all:	main.exe

main.exe:	main.o
	gcc ${CFLAGS} -o main.exe main.o -lm

main.o: main.c macro.h
	gcc ${CFLAGS} -c main.c

.PHONY:		clean

clean:	
		rm -f main.exe main.o A.o

