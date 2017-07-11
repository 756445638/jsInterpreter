TARGET = jsinterpreter
CC = gcc 
OBJS = lex.yy.o\
  y.tab.o\
  main.o \
  memory.o

CFLAGS = -c -g -Wall -Wswitch-enum -ansi -pedantic -DDEBUG
INCLUDES = \

$(TARGET):$(OBJS)
	$(CC) $(OBJS) -o $@ -lm



y.tab.h : js.y
	bison --yacc -dv js.y
y.tab.c : js.y
	bison --yacc -dv js.y


y.tab.o:y.tab.c
	$(CC) -c -g $*.c $(INCLUDES)



lex.yy.c : js.l js.y y.tab.h
	flex js.l



clean:
	rm *.o rm y.tab.c y.tab.h

