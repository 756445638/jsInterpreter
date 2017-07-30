#ifndef INTERPRETE_H
#define INTERPRETE_H
#include "js.h"



int INTERPRETE_interprete(JsInterpreter* inter);

StamentResult INTERPRETE_execute_statement(Statement* s);

StamentResult  INTERPRETE_execute_statement_while(StatementWhile* w);


Variable* 
INTERPRETE_creaet_variable(JsInterpreter* inter,ExecuteEnvironment* env,	char* name,	JsValue* v,	int line);



JsValue*
INTERPRETE_creaet_heap(JsInterpreter* inter,int size,int line);



JsFunction *
INTERPRETE_search_func_from_function_list(JsFucntionList* list,char* function);


#endif

