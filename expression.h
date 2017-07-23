#ifndef EXPRESSION_H
#define EXPRESSION_H





int get_expression_list_length(ExpressionList* list);







void eval_create_local_variable_expression(JsInterpreter * inter,ExecuteEnvironment *env,Expression* e);


void eval_negative_expression(JsInterpreter * inter,ExecuteEnvironment *env,Expression* e);
void eval_increment_decrement_expression(JsInterpreter * inter,ExecuteEnvironment *env,Expression* e);


void eval_logical_expression(JsInterpreter * inter,ExecuteEnvironment *env,Expression* e);


void eval_string_expression(JsInterpreter * inter,Expression* e);


void eval_arithmetic_expression(JsInterpreter * inter,ExecuteEnvironment* env,Expression* e);


void eval_relation_expression(JsInterpreter * inter,ExecuteEnvironment* env,Expression* e);
JsValue eval_assign_expression(JsInterpreter * inter,ExecuteEnvironment* env,Expression* e);





int eval_expression(JsInterpreter* inter,ExecuteEnvironment* env,Expression* e);

JsValue* get_left_value(ExecuteEnvironment* env,Expression* e);

 
Variable* search_variable_from_variablelist(VariableList* list,char* identifier);










#endif

















