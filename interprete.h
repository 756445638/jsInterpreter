#ifndef INTERPRETE_H
#define INTERPRETE_H
#include "js.h"



int INTERPRETE_interprete(JsInterpreter* inter);

StamentResult INTERPRETE_execute_statement(JsInterpreter* inter,ExecuteEnvironment* env,Statement* s);


StamentResult INTERPRETE_execute_statement_for(JsInterpreter* inter,ExecuteEnvironment* env,StatementFor* f,int line);


StamentResult INTERPRETE_execute_statement_if(JsInterpreter* inter,ExecuteEnvironment* env,StatementIf* i,int line);



StamentResult INTERPRETE_execute_statement_while(	JsInterpreter* inter,	ExecuteEnvironment* env,	StatementWhile* w,int line);



StamentResult INTERPRETE_execute_statement_expression(JsInterpreter* inter,ExecuteEnvironment* env,Expression* e);

JsFunction* INTERPRETE_create_function(JsInterpreter* inter,ExecuteEnvironment* env,JsFunction* func,int line);

Variable*  
INTERPRETE_creaet_variable(
		JsInterpreter* inter,
		ExecuteEnvironment* env,
		char* name,
		JsValue* v,
		int line
);



void* INTERPRETE_creaet_heap(JsInterpreter* inter,JS_VALUE_TYPE typ,int size,int line);



JsFunction *
INTERPRETE_search_func_from_function_list(JsFunctionList* list,char* function);



JsValue INTERPRETE_concat_string(JsInterpreter* inter,const JsValue* v1,const JsValue* v2,int line);


void INTERPRETE_free_env(JsInterpreter* inter,ExecuteEnvironment* env);

JsValue *
INTERPRETE_search_variable_from_env(ExecuteEnvironment* env,char* function);




JsValue* INTERPRETE_search_field_from_object(JsObject* obj,const char* key);

JsValue* INTERPRETE_create_object_field(JsInterpreter* inter,JsObject* obj,const char* key,JsValue* value,int line);


JsFunction *
INTERPRETE_search_func_from_env(ExecuteEnvironment* env,char* function);



void INTERPRETE_add_buildin(JsInterpreter* inter);

ExecuteEnvironment*
INTERPRETE_alloc_env(JsInterpreter* inter,ExecuteEnvironment* outter,int line);





void INTERPRETE_check_return_value_free_or_push_in_envheap(
	JsInterpreter* inter,
	ExecuteEnvironment* env,
	StamentResult* ret
);



ExecuteEnvironment*
get_last_not_null_outter_env(ExecuteEnvironment* env);


#endif

