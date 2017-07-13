#include "js.h"
#include "memory.h"

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














