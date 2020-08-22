# Defined macros needed for Makefile
CURR_DIR=$(shell pwd)
CC=gcc
CFLAGS=-I$(CURR_DIR)
FILES=main.c
LIBS=-L$(CURR_DIR)

# Rule for compiling main.c with linking path
mainprog: .
	$(CC) $(CFLAGS) $(FILES) -o mainprog $(LIBS)

# Rule for removing executable/obj files
clean:
	rm -f *.o mainprog

# Rule for executing 'mainprog' rule
all: mainprog
