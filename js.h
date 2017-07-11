#ifndef JS_H
#define JS_H

type enum {
    JS_BOOL_TRUE =1 ,
    JS_BOOL_FLASE = 0,
} JSBOOL;

type enum {
    JS_VALUE_TYPE_BOOL = 1,
    JS_VALUE_TYPE_INT,
    JS_VALUE_TYPE_FLOAT,
    JS_VALUE_TYPE_OBJECT
} JS_VALUE_TYPE;

type enum {
    JS_OBJECT_TYPE_ARRAY = 1,
    JS_OBJECT_TYPE_STRING,
    JS_OBJECT_TYPE_OBJECT,  // JS OBJECT 
} JS_OBJECT_TYPE;


typedef JS_OBJECT_tag struct{
    JS_OBJECT_TYPE typ;
    union{
        
    } 
}


typedef struct JS_VALUE_tag {
    int typ;
    union{
        JSBOOL boolvalue;
        int invalue;
        double floatvalue;
    }u;
} JS_VALUE;

typedef struct JS_VARIABLE_tag{
    char* name ; //variable name
    struct JS_VARIABLE_tag * next;
} JS_VARIABLE;

typedef struct JS_INTERPRETER_tag{
    JS_VARIABLE* global_vars;

} JS_INTERPRETER;













#endif /*JS_H*/
