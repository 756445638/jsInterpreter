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
    e->u.unary = NULL;
    if(EXPRESSION_TYPE_STRING == typ || EXPRESSION_TYPE_ARRAY == typ){
        e->u.object = MEM_alloc(current_interpreter->interpreter_memory,sizeof(JsObecjt),get_line_number());
        if(NULL == e->u.object){
            MEM_free(current_interpreter->interpreter_memory,e);
            return NULL;
        }
    }
    return e;
}

StatementList* CREATE_chain_statement_list(StatementList* list,Statement* s){
    if(NULL == list){
       StatementList* list = MEM_alloc(current_interpreter->interpreter_memory,sizeof(StatementList),get_line_number());
       if(NULL == list){
           return NULL;
       }
       list->prev = NULL;
       list->next = NULL;
       list->statement = s;
       return list;
    }
    StatementList* new = MEM_alloc(current_interpreter->interpreter_memory,sizeof(StatementList),get_line_number());
    if(NULL == new){
        return NULL;
    }
    StatementList* oldlast = list->prev;
    new->statement = s;
    new->next = list;
    list->prev = new;
    if(NULL == oldlast){
        oldlast = list;
    }
    oldlast->next = new;
    new->prev = oldlast;
    return list;
}


JsFunction* CREATE_function(char* name,ParameterList* list,Block* block){
    JsFunction* f = MEM_alloc(current_interpreter->interpreter_memory,sizeof(JsFunction),get_line_number());
    if(NULL == f){
        return NULL;
    }
    f->block = block;
    f->parameter_list = list;
    f->name = name;
    return f;
}



int CREATE_global_function(char* name,ParameterList* list,Block* block){
    JsFunction* f = CREATE_function(name,list,block);
    if(NULL == f){
        return -1;
    }
    if (NULL == current_interpreter->funcs){
       current_interpreter->funcs = MEM_alloc(current_interpreter->interpreter_memory,sizeof(JsFucntionList),get_line_number());
       if(NULL == current_interpreter->funcs){
           MEM_free(current_interpreter->interpreter_memory,f);
           return -1;
       }
       current_interpreter->funcs->func = f;
       current_interpreter->funcs->next = NULL;
       return 0;
    }

    JsFucntionList* new = MEM_alloc(current_interpreter->interpreter_memory,sizeof(JsFucntionList),get_line_number());
    if(NULL == new){
        MEM_free(current_interpreter->interpreter_memory,f);
        return -1;
    }
    new->next = NULL;
    new->func = f;
    JsFucntionList* next = current_interpreter->funcs;
    while(NULL != next->next){
        next = next->next;
    }
    next->next = new;
    return 0;
}


ParameterList* CREATE_parameter_list(char* identifier){
    ParameterList* list= MEM_alloc(current_interpreter->interpreter_memory,sizeof(ParameterList),get_line_number());
    if(NULL == list){
        return NULL;
    }
    list->identifier = identifier;
    return list;
}


ParameterList* CREATE_chain_parameter_list(ParameterList* list,char* identifier){
    ParameterList* new= MEM_alloc(current_interpreter->interpreter_memory,sizeof(ParameterList),get_line_number());
    if(NULL == new){
        return list;
    }
    new->next = NULL;
    new->identifier = identifier;
    ParameterList* next = list;
    while(NULL != next->next){
        next = next->next;
    }
    next->next = new;
    return list;
}


StatementList* CREATE_statement_list(Statement* s){
    StatementList* list = MEM_alloc(current_interpreter->interpreter_memory,sizeof(StatementList),get_line_number());
    if(NULL == list){
        return NULL;
    }
    list->statement = s ;
    list->next = NULL;
    list->prev = NULL;
    return list;
}

Statement*
CREATE_expression_statement(Expression* e){
    Statement* s = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Statement),get_line_number());
    if(NULL == s){
        return NULL;
    }
    s->typ = STATEMENT_TYPE_EXPRESSION;
    s->u.expression_statement = e;
    return s;
}

Statement*
CREATE_break_statement(){
    Statement* s = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Statement),get_line_number());
    if(NULL == s){
        return NULL;
    }
    s->typ = STATEMENT_TYPE_BREAK;
    return s;
}

Statement*
CREATE_if_statement(Expression* condition,Block* then,StatementElsifList* elseiflist,Block* els){
    Statement* s = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Statement) + sizeof(StatementIf),get_line_number());
    if(NULL == s){
        return NULL;
    }
    s->u.if_statement = (StatementIf*)(s + 1);
    s->u.if_statement->condition = condition;
    s->u.if_statement->then = then;
    s->u.if_statement->elseIfList = elseiflist;
    s->u.if_statement->els = els;
    return s;
}


StatementElsifList*
CREATE_elsif_list(Expression* condition,Block* block){
    StatementElsifList* list =  MEM_alloc(current_interpreter->interpreter_memory,sizeof(StatementElsifList),get_line_number());
    if(NULL == list){
        return NULL;
    }
    list->next = NULL;
    list->elsif.condition = condition;
    list->elsif.block = block;
    return list;
}

StatementElsifList*
CREATE_chain_elsif_list(StatementElsifList* list,StatementElsifList* els){
    if(NULL == list){
        list = CREATE_elsif_list();
        if(NULL == list){
            return NULL;
        }
    }
    StatementElsifList* next = list;
    while(NULL != next->next){
        next = next->next;
    }
    next->next = els;
}

Statement* 
CREATE_while_statement(Expression* condition, Block* block){
    Statement* s = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Statement) + sizeof(StatementWhile),get_line_number());
    if(NULL == s){
        return NULL;
    }
    s->typ = STATEMENT_TYPE_WHILE;
    s->u.while_statement = (StatementWhile*) (s + 1);
    s->u.while_statement->condition  = condition;
    s->u.while_statement->block = block;
}


Statement* 
CREATE_for_statement(Expression* init,Expression* condition,Expression* afterblock,Block* block){
    Statement* s = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Statement) + sizeof(StatementFor),get_line_number());
    if(NULL == s){
        return NULL;
    }
    s->typ = STATEMENT_TYPE_FOR;
    s->u.for_statement = (StatementFor*)(s+1);
    s->u.for_statement.init = init;
    s->u.for_statement.condition = condition;
    s->u.for_statement.afterblock = afterblock;
    s->u.for_statement.block = block;
    return s;
}
Statement*
CREATE_return_statement(Expression* e){
    Statement* s = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Statement),get_line_number());
    if(NULL == s){
        return NULL;
    }
    s->typ = STATEMENT_TYPE_RETURN;
    s->u.return_expression =  e;
    return s;
}

Statement*
CREATE_continue_statement(){
    Statement* s = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Statement),get_line_number());
    if(NULL == s){
        return NULL;
    }
    s->typ = STATEMENT_TYPE_CONTINUE;
    return s;
}

block*
CREATE_block(StatementList* list){
    Block* b = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Block),get_line_number());
    if(NULL == b){
        return NULL;
    }
    b->list = list;
    return b;
}

ExpressionList*
CREATE_expression_list(Expression* e){
    list = MEM_alloc(current_interpreter->interpreter_memory,sizeof(ExpressionList),get_line_number());
    if(NULL == list){
        return NULL;
    }
    list->next = NULL;
    list->expression = e ;
    return e;
}

ExpressionList*
CREATE_chain_expression_list(ExpressionList* list,Expression* e){
    if(NULL == list){
        return NULL;
    }
    ExpressionList* new = CREATE_expression_list(e);
    if(NULL == new){
        return list;
    }
    ExpressionList* next = list ;
    while(NULL != next.list){
        next = next->next;
    }
    next->next = new;
    return list;
}


Expression*
CREATE_assign_expression(Expression* e1,Expression* e2){
    Expression* e= MEM_alloc(current_interpreter->interpreter_memory,sizeof(Expression) + sizeof(ExpressionBinary) + get_line_number()); 
    if(NULL == e){
        return NULL;
    }
    e->typ = EXPRESSION_TYPE_ASSIGN;
    e->u.binary = (ExpressionBinary*)(e + 1);
    e->u.binary->left = e1;
    e->u.binary->right = e2;
    return e;
}

Expression* 
CREATE_binary_expression(EXPRESSION_TYPE typ,Expression* left,Expression* right){
    Expression* e= MEM_alloc(current_interpreter->interpreter_memory,sizeof(Expression) + sizeof(ExpressionBinary) + get_line_number()); 
    if(NULL == e){
        return NULL;
    }
    e->typ = typ;
    e->u.binary = (ExpressionBinary*)(e + 1);
    e->u.binary->left = left;
    e->u.binary->right = right;
    return e;
}















