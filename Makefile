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
  expression.o\
  stack.o\
  js_value.o\
  interprete.o\
  heap.o 

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

stack.o:stack.c stack.h js.h
	$(CC) -c $^

js_value.o:js_value.c js_value.h js.h
	$(CC) -c $^

interprete.o:interprete.c interprete.h js.h stack.h
	$(CC) -c $^

heap.o:heap.c heap.h js.h 
	$(CC) -c $^


clean:
	rm *.o  y.tab.c y.tab.h *.gch

