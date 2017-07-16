TARGET = jsinterpreter
CC = gcc 
OBJS = lex.yy.o\
  y.tab.o\
  main.o \
  memory.o \
  create.o\
  util.o\
  string.o\
  error.o\
  js.o

CFLAGS = -c -g -Wall -Wswitch-enum -ansi -pedantic -DDEBUG
INCLUDES = \

$(TARGET):$(OBJS)
	$(CC) $(OBJS) -o $@ -lm
	chmod +x $(TARGET)



y.tab.h : js.y
	bison --yacc -dv js.y
y.tab.c : js.y
	bison --yacc -dv js.y


y.tab.o:y.tab.c
	$(CC) -c -g $*.c $(INCLUDES)


util.o:util.c
	$(CC) -c $^
create.o:create.c 
	$(CC) -c $^
string.o:string.c
	$(CC) -c $^
error.o:error.c
	$(CC) -c $^
js.o:js.c
	$(CC) -c $^

lex.yy.c : js.l js.y y.tab.h
	flex js.l


clean:
	rm *.o  y.tab.c y.tab.h

