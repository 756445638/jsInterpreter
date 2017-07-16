#include "error.h"
#include <stdio.h>
#include "string.h"
#include "unistd.h"

void ERROR_compile_error(COMPILE_ERROR typ,char* buf){
    printf("compile failed,err:%s buf:%s",CompileErrorMessages[typ].message,buf);
    _exit(1);
}