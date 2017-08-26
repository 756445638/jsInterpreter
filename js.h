#ifndef JS_H
#define JS_H

#include "memory.h"
#include "string.h"

#define LINE_BUF_SIZE (1024)
#define SMALL_FLOAT (0.000001)
#define ISZORE(x) ((x<0.000001) && (x>-0.000001))
#define BUILDIN_FUNCTION_MAX_ARGS 10

#define GC_SWEEP_TIMING 1

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
    JS_VALUE_TYPE_FUNCTION,
    JS_VALUE_TYPE_NULL,
    JS_VALUE_TYPE_UNDEFINED,
    JS_VALUE_TYPE_OBJECT,
    JS_VALUE_TYPE_STRING_LITERAL
} JS_VALUE_TYPE;

typedef struct JsFunction_tag JsFunction;
typedef struct JsFunctionBuildin_tag JsFunctionBuildin;

typedef struct JsValue_tag JsValue;

typedef struct JsArray_tag JsArray;

typedef struct JsString_tag JsString;

typedef struct JsObject_tag JsObject;

typedef struct JsKv_tag JsKv;
typedef struct JsKvList_tag JsKvList;


typedef struct Heap_tag Heap;




struct JsValue_tag {
    JS_VALUE_TYPE typ;
    union{
        JSBool boolvalue;
        int intvalue;
        double floatvalue;
		JsFunction* func;
		Heap* array;
		Heap* string;
		JsObject* object;
		char* literal_string;
    }u;
};


struct JsFunctionBuildin_tag {
	int args_count;
	union{
		JsValue (*func1)(const JsValue *); /*��������Ϊ1*/
	}u;
};




struct JsKv_tag{
	char* key;
	JsValue value;
};

struct JsKvList_tag{
	JsKv kv;
	struct JsKvList_tag* next;
};

typedef  enum {
	JS_OBJECT_TYPE_USER,
	JS_OBJECT_TYPE_BUILDIN
}JS_OBJECT_TYPE;

struct JsObject_tag{
	char mark;
	JS_OBJECT_TYPE typ;
	JsKvList* eles; 
	int line;
};





struct JsString_tag {
	char* s ;
	int length;
	int alloc;
	char mark;
	int line;
};


struct JsArray_tag {
    JsValue* elements;
    int length;
    int alloc;
	char mark;
	int line;
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

typedef struct ExpressionList_tag  ExpressionList;



typedef struct ExpressionBinary_tag{
    Expression* left;
    Expression* right;
}ExpressionBinary;

typedef struct ExpressionAssignFunction_tag{	
	char* identifier;
    Expression* dest;
    JsFunction* func;
}ExpressionAssignFunction;





typedef struct ExpressionNew_tag {
	char* identifier;
	ExpressionList* args;
}ExpressionNew;

typedef struct ExpressionCreateLocalVarialbe_tag{
    char* identifier;
    Expression* expression;
}ExpressionCreateLocalVarialbe;




typedef enum{
	INDEX_TYPE_EXPRESSION = 1,
	INDEX_TYPE_IDENTIFIER

}INDEX_TYPE;

typedef struct ExpressionIndex_tag{
	INDEX_TYPE typ;
    Expression* e;
    Expression* index;
	char* identifier;
}ExpressionIndex;




struct ExpressionList_tag {
    Expression*  expression;
    struct ExpressionList_tag* next;
};

typedef ExpressionList ArgumentList;

typedef struct ExpressionMethodCall_tag {
    Expression* e;
    char* method;
    ArgumentList* args;
}ExpressionMethodCall;

typedef struct ExpressionFunctionCall_tag {
    char* func;
    ArgumentList* args;
}ExpressionFunctionCall;

typedef struct ExpressionObjectKV_tag {
	char* identifier_key;
	Expression* expression_key;
	Expression* value;
} ExpressionObjectKV;


typedef struct ExpressionObjectKVList_tag {
	ExpressionObjectKV* kv;
	struct ExpressionObjectKVList_tag* next;
}ExpressionObjectKVList;




typedef enum {
    EXPRESSION_TYPE_BOOL=1,
    EXPRESSION_TYPE_INT,
    EXPRESSION_TYPE_FLOAT,
    EXPRESSION_TYPE_STRING,
    EXPRESSION_TYPE_ARRAY,
    EXPRESSION_TYPE_OBJECT,
    EXPRESSION_TYPE_LOGICAL_OR,
    EXPRESSION_TYPE_LOGICAL_AND,
    EXPRESSION_TYPE_ASSIGN,
    EXPRESSION_TYPE_PLUS_ASSIGN,
    EXPRESSION_TYPE_MINUS_ASSIGN,
    EXPRESSION_TYPE_MUL_ASSIGN,
    EXPRESSION_TYPE_DIV_ASSIGN,
    EXPRESSION_TYPE_MOD_ASSIGN,
    EXPRESSION_TYPE_ASSIGN_FUNCTION,
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
    EXPRESSION_TYPE_NOT,
    EXPRESSION_TYPE_IDENTIFIER,/*identifier right value*/
    EXPRESSION_TYPE_CREATE_LOCAL_VARIABLE,
    EXPRESSION_TYPE_NULL,
    EXPRESSION_TYPE_NEW,
    EXPRESSION_TYPE_CREATE_FUNCTION
    
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
		ExpressionNew * new;
		ExpressionAssignFunction* assign_function;
		ExpressionObjectKVList* object_kv_list;
		JsFunction* func;
    }u;
};


typedef enum {
    STATEMENT_TYPE_EXPRESSION = 1,
    STATEMENT_TYPE_IF,
    STATEMENT_TYPE_FOR,
    STATEMENT_TYPE_FOR_IN,
    STATEMENT_TYPE_WHILE,
    STATEMENT_TYPE_CONTINUE,
    STATEMENT_TYPE_RETURN,
    STATEMENT_TYPE_BREAK,
    STATEMENT_TYPE_SWITCH
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


struct StatementElsif_tag {
    Block* block;
    Expression* condition;
	int line;
};

struct StatementElsifList_tag {
    StatementElsif elsif;
    struct StatementElsifList_tag* next;
};



typedef struct StatementFor_tag {
    Block* block;
    Expression* init;
    Expression* condition;
    Expression* afterblock;
}StatementFor;

typedef struct StatementForIn_tag {
	char* identifer;
	Expression* target;
	Block* block;
}StatementForIn;


typedef struct StatementWhile_tag {
    Expression* condition;
    Block* block;
	char isdo;
}StatementWhile;


typedef struct StatementReturn_tag {
    Expression* expression;
}StatementReturn;


 typedef struct StatementSwitch_tag StatementSwitch;
 


struct Statement_tag{
    STATEMENT_TYPE typ;
	int line;
    union{
        Expression* expression_statement;
        StatementIf* if_statement;
        StatementFor* for_statement;
		StatementForIn* forin_statement;
        StatementWhile* while_statement;
        Expression* return_expression;
		StatementSwitch* switch_statement;
    }u;
};





typedef struct StatementList_tag {
    Statement* statement;
    struct StatementList_tag* next;
}StatementList;



typedef struct  StatementSwitchCaseList_tag {
	Expression* match;
	StatementList* list;
	int line;
	struct StatementSwitchCaseList_tag* next;
}StatementSwitchCaseList;

struct StatementSwitch_tag{
	Expression* condition;
	StatementSwitchCaseList* list;
	StatementList* defaultpart;
};

struct Block_tag{
    StatementList* list;
};

typedef enum{
	JS_FUNCTION_TYPE_USER =1,
	JS_FUNCTION_TYPE_BUILDIN
}JS_FUNCTION_TYPE;





struct JsFunction_tag {
	JS_FUNCTION_TYPE typ;
    char* name;/*function name*/
    Block* block;
    ParameterList* parameter_list;
	JsFunctionBuildin* buildin;
};


typedef  struct JsFunctionList_tag{
    JsFunction func;
    struct JsFunctionList_tag* next;
}JsFunctionList;



/*runtime stack*/
typedef struct Stack_tag{
	JsValue* vs;
	int sp;/*sp pointer*/
	int alloc; /*total length*/
} Stack;



struct Heap_tag {
	struct Heap_tag * prev;
	struct Heap_tag * next;
	JS_VALUE_TYPE typ;
	union{
		JsString* string;
		JsObject* object;
		JsArray* array;
	}u;
    int line;/*alloc by which line*/
};





typedef  struct ExecuteEnvironment_tag {
	JsFunctionList* funcs;
	VariableList* vars;
	struct ExecuteEnvironment_tag* outter;
}ExecuteEnvironment;




/*runtime struct*/
typedef struct  JsInterpreter_tag {
    Memory* interpreter_memory;
    Memory* excute_memory;
    StatementList* statement_list;
    VariableList* vars;
	Stack stack;
	ExecuteEnvironment env;
	Heap* heap;  /*header heap is not use*/
}JsInterpreter;


typedef enum {
	STATEMENT_RESULT_TYPE_NORMAL = 1,
	STATEMENT_RESULT_TYPE_CONTINUE,
	STATEMENT_RESULT_TYPE_RETURN,
	STATEMENT_RESULT_TYPE_BREAK
}STATEMENT_RESULT_TYPE;

typedef  struct StamentResult_tag{
	STATEMENT_RESULT_TYPE typ;
}StamentResult; 






#endif /*JS_H*/

