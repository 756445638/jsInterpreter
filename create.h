
#ifndef CREATE_H
#define CREATE_H
#include "js.h"

JsInterpreter *
JS_create_interpreter();

char *CREATE_identifier(char *i);

Expression *CREATE_alloc_expression(EXPRESSION_TYPE typ);

StatementList *CREATE_chain_statement_list(StatementList *list, Statement *s);

JsFunction *CREATE_function(char *name, ParameterList *parameterlist, Block *block);

JsFunction *CREATE_global_function(char *name, ParameterList *parameterlist, Block *block);

ParameterList *CREATE_parameter_list(char *identifier);

ParameterList *CREATE_chain_parameter_list(ParameterList *list, char *identifier);

StatementList *CREATE_statement_list(Statement *s);
Statement *
CREATE_expression_statement(Expression *e);

Statement *
CREATE_break_statement();

Statement *
CREATE_if_statement(Expression *condition, Block *then, StatementElsifList *elseiflist, Block *els);

StatementElsifList *
CREATE_elsif_list(Expression *condition, Block *block);
StatementElsifList *
CREATE_chain_elsif_list(StatementElsifList *list, StatementElsifList *els);

Statement *
CREATE_while_statement(Expression *condition, Block *block, char isdo);

Statement *
CREATE_for_statement(Expression *init, Expression *condition, Expression *afterblock, Block *block);
Statement *
CREATE_return_statement(Expression *e);

Statement *
CREATE_continue_statement();

Block *
CREATE_block(StatementList *list);
ExpressionList *
CREATE_expression_list(Expression *e);

ExpressionList *
CREATE_chain_expression_list(ExpressionList *list, Expression *e);

Expression *
CREATE_assign_expression(Expression *e1, Expression *e2);

Expression *
CREATE_binary_expression(EXPRESSION_TYPE typ, Expression *left, Expression *right);
Expression *
CREATE_minus_expression(Expression *e);
Expression *
CREATE_index_expression(Expression *e, INDEX_TYPE typ, Expression *index, char *identifier);

Expression *
CREATE_method_call_expression(Expression *e, char *method, ArgumentList *args);
Expression *
CREATE_incdec_expression(Expression *e, EXPRESSION_TYPE typ);
ExpressionList *
CREATE_argument_list(Expression *e);

ExpressionList *
CREATE_chain_argument_list(ExpressionList *list, Expression *e);

Expression *
CREATE_function_call_expression(char *funcname, Expression *e, ArgumentList *args);

Expression *
CREATE_identifier_expression(char *identifier);

Expression *
CREATE_localvariable_declare_expression(char *identifier, Expression *assignment);

Expression *
CREATE_boolean_expression(JSBool value);

Expression *
CREATE_null_expression();
Expression *
CREATE_array_expression(ExpressionList *list);

Expression *
CREATE_object_expression();

Expression *
CREATE_new_expression(char *identifer, ExpressionList *args);

#endif
