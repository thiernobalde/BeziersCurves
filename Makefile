# Makefile de pong - 04/02/2011

SHELL  = /bin/bash
CC     = gcc
RM     = rm -f
CFLAGS = `pkg-config gtk+-2.0 --cflags` -W -Wall -ansi -pedantic -g
LIBS   = `pkg-config gtk+-2.0 --libs`
MKDEP  = gcc -MM $(CFLAGS)

OBJECTS = prog.o gui.o gui-area.o bez_control.o bez_drawing.o bez_curve.o vect.o info.o util.o listeners.o 
EXEC    = prog

.c.o :
	$(CC) $(CFLAGS) -c $*.c

all :: $(EXEC)

$(EXEC) : $(OBJECTS)
	$(CC) -o $@ $^ $(LIBS)

clean ::
	@ $(RM) *.o $(EXEC)

depend ::
	$(MKDEP) *.c > .depend

include .depend
