#
# CS 11: Makefile for C track, assignment 5.
#

CC     = gcc
CFLAGS = -g -Wall -Wstrict-prototypes -ansi -pedantic

all: array pointer

array: Array1dCA.o memcheck.o
	$(CC) Array1dCA.o memcheck.o -o Array1dCA

pointer: Pointer1dCA.o memcheck.o
	$(CC) Pointer1dCA.o memcheck.o -o Pointer1dCA

memcheck.o: memcheck.c memcheck.h
	$(CC) $(CFLAGS) -c memcheck.c

Array1dCA.o: Array1dCA.c memcheck.h
	$(CC) $(CFLAGS) -c Array1dCA.c

Pointer1dCA.o: Pointer1dCA.c memcheck.h
	$(CC) $(CFLAGS) -c Pointer1dCA.c

check:
	c_style_check Array1dCA Pointer1dCA

clean:
	rm -f *.o Array1dCA Pointer1dCA



