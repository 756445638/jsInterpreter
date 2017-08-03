#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "js.h"




int get_expression_list_length(ExpressionList* list);







int eval_create_local_variable_expression(JsInterpreter * inter,ExecuteEnvironment *env,Expression* e);


int eval_negative_expression(JsInterpreter * inter,ExecuteEnvironment *env,Expression* e);
int eval_increment_decrement_expression(JsInterpreter * inter,ExecuteEnvironment *env,Expression* e);


int eval_logical_expression(JsInterpreter * inter,ExecuteEnvironment *env,Expression* e);


int eval_string_expression(JsInterpreter * inter,Expression* e);


int eval_arithmetic_expression(JsInterpreter * inter,ExecuteEnvironment* env,Expression* e);


int eval_relation_expression(JsInterpreter * inter,ExecuteEnvironment* env,Expression* e);
int eval_assign_expression(JsInterpreter * inter,ExecuteEnvironment* env,Expression* e);





int eval_expression(JsInterpreter* inter,ExecuteEnvironment* env,Expression* e);

JsValue* get_left_value(ExecuteEnvironment* env,Expression* e);

 
Variable* search_variable_from_variablelist(VariableList* list,char* identifier);


int eval_array_expression(JsInterpreter * inter,ExecuteEnvironment* env,Expression* e);


int eval_function_call_expression(JsInterpreter* inter,ExecuteEnvironment* env,Expression* e);


int get_expression_list_length(ExpressionList* list);



#endif

















