#include "util.h"
#include "string.h"
#include "error.h"
void increment_line_number(){
    line_number++;
}

int get_line_number(){
    return line_number;
}

void alloc_temprory_string(){
    STRING* s = STRING_new(current_interpreter->interpreter_memory);
    if(NULL == s){
        ERROR_compile_error(CANNOT_ALLOC_MEMORY,sprintf("line:%d",get_line_number));
        return ;
    }
    literal_string_holder = s ;
}

void appendchar_temprory_string(char c){
    STRING* s = STRING_appendchar(current_interpreter->interpreter_memory,literal_string_holder,c);
    if(NULL == s){
        ERROR_compile_error(CANNOT_ALLOC_MEMORY,sprintf("line:%d",get_line_number));
        return ;
    }
    literal_string_holder = s ; /*maybe new malloced*/
}


