# Makefile du solveur

SHELL = /bin/bash
CC = gcc
DEP = gcc -MM

EXECS = main
OBJS = main.o lecture.o clause.o variable.o dpll.o utile.o

FLAGS = -Wall -std=c99 -g
RM = rm -f


all :: $(EXECS)

main : $(OBJS)

$(EXECS) :
	$(CC) $^ $(FLAGS) $(LIBS_I) -o $@ $(LIBS)
	
%.o : %.c
	$(CC) -c $(FLAGS) $(LIBS_I) $*.c
	
depend ::
	$(DEP) $(FLAGS) *.c >|.depend
	
clean ::
	$(RM) $(OBJS) $(EXECS)
	
-include .depend
