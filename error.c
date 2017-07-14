#include "error.h"
#include <stdio.h>


void ERROR_compile_error(COMPILE_ERROR typ,char* buf){
    printf("compile failed,err:%s buf:%s",CompileErrorMessage[typ],buf);
}