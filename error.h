#ifndef ERROR_H
#define ERROR_H

#include "js.h"


typedef enum {
    CHARACTER_INVALID_ERR = 1,

}COMPILE_ERROR;


MessageFormat CompileErrorMessage[]= {
    {"dummy"},
    {"invalid charater"},
    {"dummy"},
};


void ERROR_compile_error(COMPILE_ERROR typ,char* buf);










#endif