#include "error.h"
#include <stdio.h>
#include "string.h"
#include "unistd.h"


MessageFormat CompileErrorMessages[]= {
    {"dummy"},
    {"invalid charater"},
    {"can`t alloc memory"},
    {"dummy"}
};
MessageFormat RuntimeErrorMessages[] = {
	{"dummy"},
	{"can`t find variable"},
	{"variable alreay declared"},
    {"can`t alloc memory"},
    {"can`t index this type"},
    {"can`t use this for index"},
    {"index out of range"},
	{"function not found"},
    {"continue or return or break can`t in this scope"},
	{"type is not right"},
	{"is not a object"},
	{"field not defined"},
	{"not a function or method"},
	{"dummy"},
};






void ERROR_compile_error(COMPILE_ERROR typ,char* buf){
    printf("compile failed,err:%s buf:%s",CompileErrorMessages[typ].message,buf);
    _exit(1);
}


void ERROR_runtime_error(RUNTIME_ERROR typ,int line){
	printf("runtime failed,err:%s line:%d\n",RuntimeErrorMessages[typ].message,line);
    _exit(1);
}




