# Makefile per premortem.c
# a causa della presenza di pthread
# occorrerebbe compilare col flag -D_REENTRANT
# oppure con  -D_THREAD_SAFE 
# per ricordarmene, ho inserito i flag anche direttamente nel codice

CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: 	premortem.exe 

premortem.exe: premortem.o
	gcc ${CFLAGS} -o premortem.exe premortem.o ${LIBRARIES}

premortem.o: premortem.c
	gcc ${CFLAGS} -c premortem.c


.PHONY:	clean

clean:
	rm -f premortem.o premortem.exe 

