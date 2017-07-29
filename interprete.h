#ifndef INTERPRETE_H
#define INTERPRETE_H
#include "js.h"



int INTERPRETE_interprete(JsInterpreter* inter);

int INTERPRETE_execute_statement(Statement* s);

int INTERPRETE_execute_statement_while(StatementWhile* w);


Variable* 
INTERPRETE_creaet_variable(JsInterpreter* inter,VariableList* list,char* name,JsValue* v,int line);



JsValue*
INTERPRETE_creaet_heap(JsInterpreter* inter,int size,int line);

#endif

