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
  expression.o

CFLAGS = -c -g -Wall -Wswitch-enum -ansi -pedantic -DDEBUG
INCLUDES = \

$(TARGET):$(OBJS)
	$(CC) $(OBJS) -o $@ -lm
	chmod +x $(TARGET)



y.tab.h : js.y js.l
	bison --yacc -dv js.y
y.tab.c : js.y
	bison --yacc -dv js.y


y.tab.o:y.tab.c
	$(CC) -c -g $*.c $(INCLUDES)

expression.o:expression.c js.h
	$(CC) -c $^

util.o:util.c util.h
	$(CC) -c $^
create.o:create.c  create.h js.h 
	$(CC) -c $^ 
string.o:string.c string.h
	$(CC) -c $^
error.o:error.c error.h message.h
	$(CC) -c $^

lex.yy.c : js.l js.y y.tab.h
	flex js.l


clean:
	rm *.o  y.tab.c y.tab.h

