#include "error.h"
#include <stdio.h>
#include "string.h"
#include "unistd.h"


MessageFormat CompileErrorMessagess[]= {
    {"dummy"},
    {"invalid charater"},
    {"can`t alloc memory"},
    {"dummy"}
};



void ERROR_compile_error(COMPILE_ERROR typ,char* buf){
    printf("compile failed,err:%s buf:%s",CompileErrorMessagess[typ].message,buf);
    _exit(1);
}