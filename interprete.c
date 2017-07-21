#include "interprete.h"
#include "js.h"

int INTERPRETE_interprete(JsInterpreter* inter){
    if(NULL == inter->statement_list){
        return -1;/*no statement list*/
    }
    Statement* s = inter->statement_list->statement;
    StatementList *next = inter->statement_list;
    int result;
    while(next != inter->statement_list){
        result = INTERPRETE_execute_statement(s);
        if(-1 == result){

        }

        next = next->next;
    }
}

int INTERPRETE_execute_statement(Statement* s){
    if(s->typ == STATEMENT_TYPE_WHILE){
        return INTERPRETE_execute_statement_while(s->u.while_statement);
    }



    return -1 ;/*no such type*/
}

int INTERPRETE_execute_statement_while(StatementWhile* w){
    
}