#ifndef JS_VALUE_H 
#define JS_VALUE_H



#include "js.h"


#include "js.h"
#include "js_value.h"
#include <string.h>
#include <stdarg.h>


JSBool is_js_value_true(const JsValue* v);


JSBool js_reverse_bool(JSBool b);

JsValue js_increment_or_decrment(const JsValue* v,char increment);


JsValue js_nagetive(const JsValue* const v);


JsValue js_value_add(JsInterpreter* inter,const JsValue* const v1,const JsValue* const v2,int line);
JsValue js_value_mod(const JsValue* v1,const JsValue* v2);
JsValue js_value_mul(const JsValue* v1,const JsValue* v2);
JsValue js_value_div(const JsValue* v1,const JsValue* v2);

JsValue js_value_sub(const JsValue* v1,const JsValue* v2);






JSBool js_value_equal(const JsValue* v1,const JsValue* v2);

JSBool js_value_greater(const JsValue* v1,const JsValue* v2);


JSBool js_value_greater_or_equal(const JsValue* v1,const JsValue* v2);



JsValue js_print(const JsValue *value);
JsValue js_println(const JsValue *value);



void js_print_array(JsArray* array);

JsValue js_to_string(JsInterpreter* inter,const JsValue* value,int line);




JsValue js_typeof(const JsValue* value);




#endif


