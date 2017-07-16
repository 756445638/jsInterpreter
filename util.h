#include "js.h"
#include "memory.h"
#ifndef UTIL_H
#define UTIL_H
static  int line_number = 0;
JsInterpreter*  current_interpreter; /*current interpreter*/
STRING* literal_string_holder;


int alloc_temprory_string();

int appendchar_temprory_string(char c);



void increment_line_number();

int get_line_number();











#endif