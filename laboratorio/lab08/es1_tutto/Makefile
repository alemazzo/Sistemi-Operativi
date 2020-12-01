CFLAGS=-ansi -Wall -Werror -Wpedantic -pedantic
SHELL=/bin/bash

all:	B1.txt B2.txt
	touch tutto.txt
	echo "" > tutto.txt
	cat B1.txt >> tutto.txt
	cat B2.txt >> tutto.txt

clean:	A1.txt A2.txt
	rm A1.txt A2.txt

touch:	B1.txt
	touch B1.txt

B1.txt:	A1.txt
	cat A1.txt > B1.txt
	date >> B1.txt

B2.txt: A2.txt
	date > B2.txt
	cat A2.txt >> B2.txt

A1.txt:
	echo "AAAA" > A1.txt

A2.txt:
	echo "ZZZZ" > A2.txt

.PHONY:	clean touch
