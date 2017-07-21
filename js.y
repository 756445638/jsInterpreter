%{
#include <stdio.h>
#include "js.h"
#define YYDEBUG 1
#include "message.h"
#include "util.h"
%}
%union {
    char                *identifier;
    ParameterList       *parameter_list;
    ArgumentList        *argument_list;
    Expression          *expression;
    ExpressionList      *expression_list;
    Statement           *statement;
    StatementList       *statement_list;
    Block               *block;
    Elsif               *elsif;
    JsFunction          *function;
}
%token <expression>     INT_LITERAL
%token <expression>     DOUBLE_LITERAL
%token <expression>     STRING_LITERAL
%token <identifier>     IDENTIFIER
%token FUNCTION IF ELSE ELSIF WHILE FOR RETURN_T BREAK CONTINUE NULL_T 
        LP RP LC RC LB RB SEMICOLON COMMA ASSIGN LOGICAL_AND LOGICAL_OR
        EQ NE GT GE LT LE ADD SUB MUL DIV MOD TRUE_T FALSE_T DOT VAR
        INCREMENT DECREMENT
%type   <parameter_list> parameter_list
%type   <argument_list> argument_list
%type   <expression> expression expression_opt
        logical_and_expression logical_or_expression
        equality_expression relational_expression
        additive_expression multiplicative_expression
        unary_expression postfix_expression primary_expression array_literal
%type   <expression_list> expression_list
%type   <statement> statement 
        if_statement while_statement for_statement
        return_statement break_statement continue_statement
%type   <statement_list> statement_list
%type   <block> block
%type   <elsif> elsif elsif_list
%type   <function> function_definition function_noname_definition
%%
translation_unit
        : definition_or_statement
        | translation_unit definition_or_statement
        ;
definition_or_statement
        : function_definition
        | statement
        {
            current_interpreter->statement_list
                = CREATE_chain_statement_list(current_interpreter->statement_list, $1);
        }
        ;

function_definition
        : FUNCTION IDENTIFIER LP parameter_list RP block
        {
            CREATE_global_function($2, $4, $6);
        }
        | FUNCTION IDENTIFIER LP RP block
        {
            CREATE_global_function($2, NULL, $5);
        }
        ;

function_noname_definition
    :FUNCTION LP RP block
    {
        $$ = CREATE_function("", NULL, $4);
    }
    |FUNCTION LP parameter_list RP block
    {
        $$ = CREATE_function("", $3, $5);
    }
    ;

parameter_list
    : parameter_list COMMA IDENTIFIER
    {
        $$ = CREATE_chain_parameter_list($1, $3);
    }
    | IDENTIFIER
    {
         $$ = CREATE_parameter_list($1);
    }
    ;

statement_list
    :statement
    {
        $$ = CREATE_statement_list($1);
    }
    |statement_list statement
    {
        $$ = CREATE_chain_statement_list($1, $2);
    }
    ;

statement
    :expression SEMICOLON
    {
        $$ = CREATE_expression_statement($1);
    }
    |postfix_expression  ASSIGN function_noname_definition{
        printf("create method\n");
    }
    |VAR IDENTIFIER ASSIGN function_noname_definition
    {
        printf("create local function");
    }
    | if_statement
    | while_statement
    | for_statement
    | return_statement
    | continue_statement
    | break_statement


break_statement
    :BREAK SEMICOLON
    {
            $$ = CREATE_break_statement();
    }
    ;

if_statement
    :IF LP expression RP block
    {
         $$ = CREATE_if_statement($3, $5, NULL, NULL);
    }
    | IF LP expression RP block ELSE block
    {
        $$ = CREATE_if_statement($3, $5, NULL, $7);
    }
    | IF LP expression RP block elsif_list
    {
        $$ = CREATE_if_statement($3, $5, $6, NULL);
    }
    | IF LP expression RP block elsif_list ELSE block
    {
        $$ = CREATE_if_statement($3, $5, $6, $8);
    }
    ;
elsif_list
    :elsif
    | elsif_list elsif
    {
         $$ = CREATE_chain_elsif_list($1, $2);
    }
    ;
elsif 
    :ELSIF LP expression RP block{
         $$ = CREATE_elsif_list($3, $5);
    }
    ;

while_statement
    :WHILE LP expression RP block
    {
        $$ = CREATE_while_statement($3, $5);
    }
    ;

for_statement
    :FOR LP expression_opt SEMICOLON expression_opt SEMICOLON expression_opt RP block
    {
        $$ = CREATE_for_statement($3, $5, $7, $9);
    }
    ;

return_statement
    :RETURN_T expression_opt SEMICOLON
    {
        $$ = CREATE_return_statement($2);
    }
    ;
continue_statement
    :CONTINUE SEMICOLON
    {
        $$ = CREATE_continue_statement();
    }
    ;

block
    :LC statement_list RC
    {
        $$ = CREATE_block($2);
    }
    |LC RC
    {
        $$ = CREATE_block(NULL);
    }
    ;

expression_opt
    : /* NULL */
    | expression
    ;

expression_list
        : /* empty */
        {
            $$ = NULL;
        }
        | expression
        {
            $$ = CREATE_expression_list($1);
        }
        | expression_list COMMA expression
        {
            $$ = CREATE_chain_expression_list($1, $3);
        }
        ;
expression
    :logical_or_expression
    |postfix_expression ASSIGN expression
    {
        $$ = CREATE_assign_expression($1, $3);
    }
    |VAR IDENTIFIER ASSIGN expression
    {
        $$ = CREATE_assign_expression($2, $4);
    }
    ;
logical_or_expression
    :logical_and_expression
    | logical_or_expression LOGICAL_OR logical_and_expression
    {
        $$ = CREATE_binary_expression(EXPRESSION_TYPE_LOGICAL_OR, $1, $3);
    }
    ;

logical_and_expression
    :equality_expression
    |logical_and_expression LOGICAL_AND equality_expression
    {
        $$ = CREATE_binary_expression(EXPRESSION_TYPE_LOGICAL_AND, $1, $3);
    }
    ;
equality_expression
    :relational_expression
    |equality_expression EQ relational_expression
    {
        $$ = CREATE_binary_expression(EXPRESSION_TYPE_EQ, $1, $3);
    }
    |equality_expression NE relational_expression
    {
        $$ = CREATE_binary_expression(EXPRESSION_TYPE_NE, $1, $3);
    }
    ;
relational_expression
    :additive_expression
    |relational_expression GT additive_expression
    {
        $$ = CREATE_binary_expression(EXPRESSION_TYPE_GT, $1, $3);
    }
    | relational_expression GE additive_expression
    {
        $$ = CREATE_binary_expression(EXPRESSION_TYPE_GE, $1, $3);
    }
    | relational_expression LT additive_expression
    {
        $$ = CREATE_binary_expression(EXPRESSION_TYPE_LT, $1, $3);
    }
    | relational_expression LE additive_expression
    {
        $$ = CREATE_binary_expression(EXPRESSION_TYPE_LE, $1, $3);
    }
    ;

additive_expression
    : multiplicative_expression
    |additive_expression ADD multiplicative_expression
    {
        $$ = CREATE_binary_expression(EXPRESSION_TYPE_ADD, $1, $3);
    }
    | additive_expression SUB multiplicative_expression{
        $$ = CREATE_binary_expression(EXPRESSION_TYPE_SUB, $1, $3);
    }
    ;
multiplicative_expression
    :unary_expression
    |multiplicative_expression MUL unary_expression
    {
        $$ = CREATE_binary_expression(EXPRESSION_TYPE_MUL, $1, $3);
    }
    |multiplicative_expression DIV unary_expression
    {
        $$ = CREATE_binary_expression(EXPRESSION_TYPE_DIV, $1, $3);
    }
    | multiplicative_expression MOD unary_expression
    {
        $$ = CREATE_binary_expression(EXPRESSION_TYPE_MOD, $1, $3);
    }
    ;

unary_expression
    :postfix_expression
    |SUB unary_expression
    {
        $$ = CREATE_minus_expression($2);
    }
postfix_expression
    :primary_expression
    |postfix_expression LB expression RB
    {
         $$ = CREATE_index_expression($1, $3);
    }
    |postfix_expression DOT IDENTIFIER 
    {
        printf("access object`s field\n");
    }
    |postfix_expression DOT IDENTIFIER LP argument_list RP
    {
        $$ = CREATE_method_call_expression($1, $3, $5);
    }
    |postfix_expression DOT IDENTIFIER LP RP
    {
        $$ = CREATE_method_call_expression($1, $3, NULL);
    }
    |postfix_expression INCREMENT
    {
        $$ = CREATE_incdec_expression($1, EXPRESSION_TYPE_INCREMENT);
    }
    | postfix_expression DECREMENT
    {
        $$ = CREATE_incdec_expression($1, EXPRESSION_TYPE_DECREMENT);
    }
    ;
argument_list
        : expression
        {
            $$ = CREATE_argument_list($1);
        }
        | argument_list COMMA expression
        {
            $$ = CREATE_chain_argument_list($1, $3);
        }
        ;

primary_expression
        : IDENTIFIER LP argument_list RP
        {
            $$ = CREATE_function_call_expression($1, $3);
        }
        | IDENTIFIER LP RP
        {
            $$ = CREATE_function_call_expression($1, NULL);
        }
        | LP expression RP
        {
            $$ = $2;
        }
        | IDENTIFIER
        {
            $$ = CREATE_identifier_expression($1);
        }
        | INT_LITERAL
        | DOUBLE_LITERAL
        | STRING_LITERAL
        | TRUE_T
        {
            $$ = CREATE_boolean_expression(JS_BOOL_TRUE);
        }
        | FALSE_T
        {
            $$ = CREATE_boolean_expression(JS_BOOL_FLASE);
        }
        | NULL_T
        {
            $$ = CREATE_null_expression();
        }
        | array_literal
        ;
array_literal
        :LB  expression_list RB
        {
            $$ = CREATE_array_expression($2);
        }
        ;
%%
