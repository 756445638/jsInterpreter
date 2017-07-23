#ifndef JS_H
#define JS_H

#include "memory.h"
#include "string.h"
#define LINE_BUF_SIZE (1024)
#define SMALL_FLOAT (0.000001)
#define ISZORE(x) ((x<0.000001) && (x>-0.000001))



typedef enum {
    JS_BOOL_TRUE =1 ,
    JS_BOOL_FALSE = 0
} JSBool;


typedef enum {
    JS_VALUE_TYPE_BOOL = 1,
    JS_VALUE_TYPE_INT,
    JS_VALUE_TYPE_FLOAT,
    JS_VALUE_TYPE_STRING,
    JS_VALUE_TYPE_ARRAY,
    JS_VALUE_TYPE_FUNCTION
} JS_VALUE_TYPE;

typedef struct JsFunction_tag JsFunction;
typedef struct JsValue_tag JsValue;




struct JsValue_tag {
    JS_VALUE_TYPE typ;
    union{
        JSBool boolvalue;
        int intvalue;
        double floatvalue;
		JsFunction* func;
		JsValue* arrary;
		char* string;
    }u;
} ;






typedef enum {
    JS_OBJECT_TYPE_ARRAY = 1,
    JS_OBJECT_TYPE_STRING,
    JS_OBJECT_TYPE_OBJECT,
    JS_OBJECT_TYPE_FUNCTION
} JS_OBJECT_TYPE;

typedef struct JsOBjectArray_tag {
    JsValue elements;
    int length;
    int alloc;
}JsOBjectArray;

struct JsObejct_tag{
    JS_OBJECT_TYPE typ;
	char mark;/*this obejct can be use or not*/
    union{
        JsOBjectArray* array;
        STRING* string;
    } u;
};



typedef struct Variable_tag {
    char* name;
    JsValue value;
}Variable;

typedef struct VariableList_tag {
    Variable var;
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

typedef struct ExpressionCreateLocalVarialbe_tag{
    char* identifier;
    Expression* expression;
}ExpressionCreateLocalVarialbe;




typedef struct ExpressionIndex_tag{
    Expression* e;
    Expression* index;
}ExpressionIndex;


typedef struct ExpressionList_tag {
    Expression*  expression;
    struct ExpressionList_tag* next;
}ExpressionList;

typedef ExpressionList ArgumentList;

typedef struct ExpressionMethodCall_tag {
    Expression* expression;
    char* method;
    ArgumentList* args;
}ExpressionMethodCall;

typedef struct ExpressionFunctionCall_tag {
    char* func;
    ArgumentList* args;
}ExpressionFunctionCall;





typedef enum {
    EXPRESSION_TYPE_BOOL=1,
    EXPRESSION_TYPE_INT,
    EXPRESSION_TYPE_FLOAT,
    EXPRESSION_TYPE_STRING,
    EXPRESSION_TYPE_ARRAY,
    EXPRESSION_TYPE_LOGICAL_OR,
    EXPRESSION_TYPE_LOGICAL_AND,
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
    EXPRESSION_TYPE_DECREMENT,
    EXPRESSION_TYPE_NEGATIVE,
    EXPRESSION_TYPE_IDENTIFIER,/*identifier right value*/
    EXPRESSION_TYPE_CREATE_LOCAL_VARIABLE,
    EXPRESSION_TYPE_NULL
    
}EXPRESSION_TYPE;


struct Expression_tag {
    EXPRESSION_TYPE typ;
	int line;
    union{
        int int_value;
        JSBool bool_value;
        double double_value;
        ExpressionBinary* binary;
        ExpressionIndex* index;
        char* identifier;
        Expression* unary;
        ExpressionFunctionCall* function_call;
        ExpressionMethodCall* method_call;
		ExpressionCreateLocalVarialbe* create_var;
		char* string;
        ExpressionList* expression_list;
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
    STATEMENT_TYPE_RETURN,
    STATEMENT_TYPE_BREAK
}STATEMENT_TYPE;


typedef struct Statement_tag Statement;
typedef struct Block_tag Block;

typedef struct StatementElsif_tag StatementElsif;
typedef struct StatementElsifList_tag StatementElsifList;
typedef  StatementElsifList Elsif;


typedef struct StatementIf_tag {
    Expression* condition;
    Block* then;
    StatementElsifList* elseIfList;
    Block* els;
}StatementIf;

typedef struct StatementElse_tag {
    Block* block;
}StatementElse;


struct StatementElsif_tag {
    Block* block;
    Expression* condition;
};

struct StatementElsifList_tag {
	int line;
    StatementElsif elsif;
    struct StatementElsifList_tag* next;
};



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

typedef struct StatementContinue_tag StatementContinue;

/*
typedef struct StatementReturn_tag {
    Expression* expression;
}StatementReturn;
*/

struct Statement_tag{
    STATEMENT_TYPE typ;
	int line;
    union{
        Expression* expression_statement;
        StatementIf* if_statement;
        StatementFor* for_statement;
        StatementWhile* while_statement;
        StatementContinue* continue_stament;
        Expression* return_expression;
    }u;
};


typedef struct StatementList_tag {
    Statement* statement;
    struct StatementList_tag* next;
    struct StatementList_tag* prev;
}StatementList;


struct Block_tag{
    StatementList* list;
};


struct JsFunction_tag {
    char* name;/*function name*/
    Block* block;
    ParameterList* parameter_list;
};


typedef  struct JsFucntionList_tag{
    JsFunction* func;
    struct JsFucntionList_tag* next;
}JsFucntionList;



/*runtime stack*/
typedef struct Stack_tag{
	JsValue* vs;
	int sp;/*sp pointer*/
	int alloc; /*total length*/
} Stack;



typedef struct Heap_tag {
	struct Heap_tag * prev;
	struct Heap_tag * next;
	JsValue obj;  /*heap just for saving objects*/
    int line;/*alloc by which line*/
}Heap;





typedef  struct ExecuteEnvironment_tag {
	VariableList* vars;
	struct ExecuteEnvironment_tag* outter;
}ExecuteEnvironment;


/*runtime struct*/
typedef struct  JsInterpreter_tag {
    Memory* interpreter_memory;
    Memory* excute_memory;
    JsFucntionList* funcs;
    StatementList* statement_list;
    /*int current_line_number;*/
    VariableList vars;
	Stack stack;
	ExecuteEnvironment* env;
	Heap heap;
}JsInterpreter;













int get_expression_list_length(ExpressionList* list);



#endif /*JS_H*/

