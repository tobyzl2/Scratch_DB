CC      = gcc
CFLAGS  = -g
RM      = rm -f


default: all

all: Scratch

Scratch: repl.c
	$(CC) $(CFLAGS) -o Scratch repl.c

clean veryclean:
	$(RM) Scratch
