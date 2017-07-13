#include "js.h"
#ifndef UTIL_H
#define UTIL_H
static  int line_number = 0;
static JsInterpreter*  current_interpreter; 


void increment_line_number();

int get_line_number();


#endif