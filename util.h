#include "js.h"
#ifndef UTIL_H
#define UTIL_H
static  int line_number = 0;
JsInterpreter*  current_interpreter; /*current interpreter*/


void increment_line_number();

int get_line_number();


#endif