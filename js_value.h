#ifndef JS_VALUE_H 
#define JS_VALUE_H



#include "js.h"



JSBool is_js_value_true(JsValue* v);



JSBool js_reverse_bool(JSBool b);

JsValue js_increment_or_decrment(JsValue* v,char increment);

JsValue js_nagetive(JsValue* v);



JsValue js_value_add(JsValue* v1,JsValue* v2);


JsValue js_value_mod(JsValue* v1,JsValue* v2);

JsValue js_value_mul(JsValue* v1,JsValue* v2);

JsValue js_value_div(JsValue* v1,JsValue* v2);




JsValue js_value_sub(JsValue* v1,JsValue* v2);



JSBool js_value_equal(JsValue* v1,JsValue* v2);

JSBool js_value_greater(JsValue* v1,JsValue* v2);



JSBool js_value_greater_or_equal(JsValue* v1,JsValue* v2);










#endif


