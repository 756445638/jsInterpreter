#include "util.h"
#include "string.h"
#include "error.h"
void increment_line_number(){
    line_number++;
}

int get_line_number(){
    return line_number;
}

int alloc_temprory_string(){
    STRING* s = STRING_new(current_interpreter->interpreter_memory);
    if(NULL == s){
        char buf[100];
        sprintf(buf,"line:%d",get_line_number());
        ERROR_compile_error(CANNOT_ALLOC_MEMORY,buf);
        return -1;
    }
    literal_string_holder = s ;
    return 0;
}

int appendchar_temprory_string(char c){
    STRING* s = STRING_appendchar(current_interpreter->interpreter_memory,literal_string_holder,c);
    if(NULL == s){
        char buf[100];
        sprintf(buf,"line:%d",get_line_number());
        ERROR_compile_error(CANNOT_ALLOC_MEMORY,buf);
        return -1;
    }
    literal_string_holder = s ; /*maybe new malloced*/
    return 0;
}


