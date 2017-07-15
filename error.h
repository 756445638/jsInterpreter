#ifndef ERROR_H
#define ERROR_H

#include "message.h"



typedef enum {
    CHARACTER_INVALID_ERR = 1,
    CANNOT_ALLOC_MEMORY,
}COMPILE_ERROR;


MessageFormat CompileErrorMessage[]= {
    {"dummy"},
    {"invalid charater"},
    {"can`t alloc memory"},
    {"dummy"}
};


void ERROR_compile_error(COMPILE_ERROR typ,char* buf);










#endif