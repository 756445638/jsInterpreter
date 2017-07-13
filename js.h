#include "memory.h"

#ifndef JS_H
#define JS_H

typedef enum {
    JS_BOOL_TRUE =1 ,
    JS_BOOL_FLASE = 0
} JSBOOL;


typedef enum {
    JS_VALUE_TYPE_BOOL = 1,
    JS_VALUE_TYPE_INT,
    JS_VALUE_TYPE_FLOAT,
    JS_VALUE_TYPE_OBJECT
} JS_VALUE_TYPE;

typedef struct JS_OBEJCT_tag JS_OBJECT;
typedef struct JsFunction_tag JsFunction;


typedef struct JS_VALUE_tag {
    JS_VALUE_TYPE typ;
    union{
        JSBOOL boolvalue;
        int intvalue;
        double floatvalue;
        JS_OBJECT* object;
    }u;
} JS_VALUE;


typedef enum {
    JS_OBJECT_TYPE_ARRAY = 1,
    JS_OBJECT_TYPE_STRING,
    JS_OBJECT_TYPE_OBJECT,
    JS_OBJECT_TYPE_FUNCTION
} JS_OBJECT_TYPE;

typedef struct JS_OBEJCT_ARRAY_tag {
    JS_VALUE* elements;
    int size;
    int alloc;
}JS_OBEJCT_ARRAY;

typedef struct JS_OBEJCT_STRING_tag {
    char* s;  
    /*len(s) == length+1*/ 
    int length;
}JS_OBEJCT_STRING;

struct JS_OBEJCT_tag{
    JS_OBJECT_TYPE typ;
    union{
        JS_OBEJCT_ARRAY* array;
        JS_OBEJCT_STRING* string;
        JsFunction* func;/*js function is also a value*/
    } u;
};



/* js values */


typedef struct Variable_tag {
    char* name;
    JS_VALUE* value;
}Variable;

typedef struct VariableList_tag {
    Variable* var;
    struct VariableList_tag* next;
}VariableList;


typedef struct IdentifierList_tag{
    char* identifier;
    struct IdentifierList_tag* next;
}IdentifierList;

typedef IdentifierList ParameterList ;

typedef struct Expression_tag  Expression;

typedef struct ExpressionBinary_tag{
    Expression* left;
    Expression* right;
}ExpressionBinary;

typedef struct ExpressionList_tag {
    Expression*  expression;
    Expression* next;
}ExpressionList;

typedef ExpressionList ArgumentList;

typedef struct ExpressionListFucntionCall_tag {
    char* name;
    ArgumentList* args;
}ExpressionListFucntionCall;



typedef enum {
    EXPRESSION_TYPE_BOOL=1,
    EXPRESSION_TYPE_INT,
    EXPRESSION_TYPE_FLOAT,
    EXPRESSION_TYPE_STRING,
    EXPRESSION_TYPE_OR,
    EXPRESSION_TYPE_AND,
    EXPRESSION_TYPE_ASSIGN,
    EXPRESSION_TYPE_EQ,
    EXPRESSION_TYPE_NE,
    EXPRESSION_TYPE_GE,
    EXPRESSION_TYPE_GT,
    EXPRESSION_TYPE_LE,
    EXPRESSION_TYPE_LT,
    EXPRESSION_TYPE_ADD,
    EXPRESSION_TYPE_SUB,
    EXPRESSION_TYPE_MUL,
    EXPRESSION_TYPE_DIV,
    EXPRESSION_TYPE_MOD,
    EXPRESSION_TYPE_INDEX,
    EXPRESSION_TYPE_METHOD_CALL,
    EXPRESSION_TYPE_FUNCTION_CALL,
    EXPRESSION_TYPE_INCREMENT,
    EXPRESSION_TYPE_DECREMENT
}EXPRESSION_TYPE;


struct Expression_tag {
    EXPRESSION_TYPE typ;
    union{
        JS_VALUE* value;
        ExpressionBinary* binary;
        Expression* unary;
        ExpressionListFucntionCall* function_call;
    }u;
};


typedef enum {
    STATEMENT_TYPE_EXPRESSION = 1,
    STATEMENT_TYPE_IF,
    STATEMENT_TYPE_ELSE,
    STATEMENT_TYPE_ELSIF,
    STATEMENT_TYPE_FOR,
    STATEMENT_TYPE_WHILE,
    STATEMENT_TYPE_CONTINUE,
    STATEMENT_TYPE_RETURN
}STATEMENT_TYPE;


typedef struct Statement_tag Statement;
typedef struct Block_tag Block;


typedef struct StatementIf_tag {
    Expression* condition;
    Block* block;
}StatementIf;

typedef struct StatementElse_tag {
    Block* block;
}StatementElse;


typedef struct StatementElsif_tag {
    Block* block;
    Expression* condition;
}StatementElsif;

typedef  StatementElsif Elsif;

typedef struct StatementFor_tag {
    Block* block;
    Expression* init;
    Expression* condition;
    Expression* afterblock;
}StatementFor;





typedef struct StatementWhile_tag {
    Expression* condition;
    Block* block;
}StatementWhile;

typedef struct StatementContinue_tag {
}StatementContinue;

typedef struct StatementReturn_tag {
}StatementReturn;

typedef struct Statement_tag{
    STATEMENT_TYPE typ;
    union{
        Expression* expression;
        StatementIf* if_statement;
        StatementElse* else_statement;
        StatementElsif * elseif_statement;
        StatementFor* for_statement;
        StatementWhile* while_statement;
        StatementContinue* continue_stament;
        StatementReturn* return_statement;
    }u;
}Statement;


typedef struct StatementList_tag {
    Statement* stament;
    Statement* next;
}StatementList;


struct Block_tag{
    StatementList* list;
};


typedef struct JsFunction_tag {
    char* name;/*function name*/
    Block* block;
    ParameterList* parameter_list;
}JsFunction;


typedef  struct JsFucntionList_tag{
    JsFunction* func;
    struct JsFucntionList_tag* next;
}JsFucntionList;


/*runtime struct*/

typedef struct  JsInterpreter_tag {
    Memory* interpreter_memory;
    Memory* excute_memory;
    JsFucntionList* funcs;
    StatementList* statement_list;
    int current_line_number;
    VariableList* vars;
}JsInterpreter;




#endif /*JS_H*/

