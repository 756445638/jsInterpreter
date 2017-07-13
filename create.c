#include "js.h"
#include "memory.h"
#include "util.h"
#include <string.h>
JsInterpreter*
JS_create_interpreter(){
    Memory*  inter_memory = MEM_open_storage();
    if(NULL == inter_memory){
        return NULL;
    }
    JsInterpreter* interpreter =  MEM_alloc(inter_memory,sizeof(JsInterpreter),0);
    if(NULL == interpreter){
        MEM_close_storage(inter_memory);
        return NULL;
    }
    interpreter->excute_memory = MEM_open_storage();
    if(NULL == interpreter->excute_memory){
        MEM_close_storage(inter_memory);
        return NULL;
    }
    interpreter->funcs = NULL;
    interpreter->current_line_number = 0 ;
    interpreter->statement_list = NULL;
    interpreter->vars = NULL;
    return interpreter;
}

char* CREATE_identifier(char * i){
    int length = strlen(i);
    char* identifier =(char*) MEM_alloc(current_interpreter->interpreter_memory,length + 1,get_line_number());
    if(NULL == identifier){
        return NULL;
    }
    strncpy(identifier,i,length);
    identifier[length] = 0;
    return identifier;
}

Expression* CREATE_alloc_expression(EXPRESSION_TYPE typ){
    Expression* e =(Expression*) MEM_alloc(current_interpreter->interpreter_memory,sizeof(Expression),get_line_number());
    if(NULL == e){
        return NULL;
    }
    e->typ = typ;
    e->u.binary = NULL;
    e->u.function_call = NULL;
    e->u.unary = null;
    return e;
}

















