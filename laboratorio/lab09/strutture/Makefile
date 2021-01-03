CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: strutture.exe

strutture.exe:	strutture.o
	gcc ${CFLAGS} -o strutture.exe strutture.o ${LIBRARIES}

strutture.o: strutture.c
	gcc ${CFLAGS} -c strutture.c

.PHONY:	clean

clean:
	rm strutture.exe strutture.o