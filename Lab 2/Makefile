#
# CS 11: Makefile for C track, assignment 2.
#
#

CC              = gcc
INFILE          = years.in
OUTFILE         = easter_dates.out
CORRECT_OUTFILE = correct_easter_dates.out


easter: easter.o
	$(CC) easter.o -o easter

easter.o: easter.c
	$(CC) -Wall -Wstrict-prototypes -ansi -pedantic -c easter.c

test:
	./easter < $(INFILE) > $(OUTFILE)
	./run_test $(OUTFILE) $(CORRECT_OUTFILE)

check:
	c_style_check easter.c

# Your clean target goes here...
clean:
	rm -f easter_dates.out easter.o easter

