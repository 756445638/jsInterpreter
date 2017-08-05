#include "js.h"
#include "js_value.h"
#include <string.h>
#include <stdarg.h>
#include "interprete.h"
#include "error.h"

JSBool is_js_value_true(const JsValue* v){
	if(JS_VALUE_TYPE_BOOL== v->typ){
		return v->u.boolvalue;
	}
	if(JS_VALUE_TYPE_INT == v->typ){
		if(0 != v->u.intvalue){
			return JS_BOOL_TRUE;
		}else{
			return JS_BOOL_FALSE;
		}
	}
	if(JS_VALUE_TYPE_FLOAT == v->typ){
		if(v->u.floatvalue < SMALL_FLOAT && v->u.floatvalue > -SMALL_FLOAT){
			return JS_BOOL_FALSE;
		}else{
			return JS_BOOL_TRUE;
		}
	}
	if(JS_VALUE_TYPE_STRING == v->typ){
		int length = v->u.string->length;
		if(0 == length){
			return JS_BOOL_FALSE;
		}else{
			return JS_BOOL_TRUE;
		}
	}
	if(JS_VALUE_TYPE_ARRAY == v->typ){
		if(0 == v->u.array->length){
			return JS_BOOL_FALSE;
		}else{
			return JS_BOOL_TRUE;
		}
	}
	return JS_BOOL_FALSE;
	
}



JSBool js_reverse_bool(JSBool b){
	if(JS_BOOL_TRUE == b){
		return JS_BOOL_FALSE;
	}else{
		return JS_BOOL_TRUE;
	}
}


JsValue js_increment_or_decrment(JsValue* const v,char increment){
	JsValue ret = *v;
	if(JS_VALUE_TYPE_INT == v->typ){
		if(1 == increment){
			ret.u.intvalue++;
		}else{
			ret.u.intvalue--;
		}
	}
	if(JS_VALUE_TYPE_FLOAT == v->typ){
		if(1 == increment){
			ret.u.floatvalue++;
		}else{
			ret.u.floatvalue--;
		}
	}
	if(JS_VALUE_TYPE_BOOL == v->typ){
		ret.u.boolvalue = js_reverse_bool(v->u.boolvalue);
	}

	return ret;
}

JsValue js_nagetive(const JsValue* const v){
	JsValue ret = *v;
	if(JS_VALUE_TYPE_INT == v->typ){
		ret.u.intvalue -= 2 * v->u.intvalue;
	}
	if(JS_VALUE_TYPE_FLOAT == v->typ){
		ret.u.floatvalue -= 2 * v->u.floatvalue;
	}
	if(JS_VALUE_TYPE_BOOL == v->typ){
		ret.u.boolvalue = js_reverse_bool(v->u.boolvalue);
	}
	return ret;
}




JsValue js_value_add(JsInterpreter* inter,const JsValue* const v1,const JsValue* const v2,int line){
	JsValue v = *v1;
	/*handle bool part*/
	if(JS_VALUE_TYPE_BOOL == v1->typ && JS_VALUE_TYPE_INT == v2->typ){
		v.typ = JS_VALUE_TYPE_INT;
		v.u.intvalue = v2->u.intvalue + v1->u.boolvalue;
		return v;
	}
	if(JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_BOOL == v2->typ){
		v.typ = JS_VALUE_TYPE_INT;
		v.u.intvalue = v1->u.intvalue + v2->u.boolvalue;
		return v;
	}

	/*handle number part*/
	if(JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_INT == v2->typ){
		v.typ = JS_VALUE_TYPE_INT;
		v.u.intvalue = v1->u.intvalue + v2->u.intvalue;
		return v;
	}
	if(JS_VALUE_TYPE_FLOAT == v1->typ && JS_VALUE_TYPE_INT == v2->typ){
		v.typ = JS_VALUE_TYPE_FLOAT;
		v.u.floatvalue = v1->u.floatvalue + v2->u.intvalue;
		return v;
	}
	if(JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_FLOAT == v2->typ){
		v.typ = JS_VALUE_TYPE_FLOAT;
		v.u.floatvalue = v1->u.intvalue + v2->u.floatvalue;
		return v;
	}
	if(JS_VALUE_TYPE_FLOAT == v1->typ && JS_VALUE_TYPE_FLOAT == v2->typ){
		v.typ = EXPRESSION_TYPE_FLOAT;
		v.u.floatvalue = v1->u.floatvalue + v2->u.floatvalue;
		return v;
	}
	


	/*handle string part*/
	if(JS_VALUE_TYPE_STRING == v1->typ){
		JsValue vv2 = js_to_string(inter, v2 , line);
		v = *(INTERPRETE_concat_string( inter,  v1,  &vv2, line));
	}
	
	if(JS_VALUE_TYPE_STRING == v2->typ){
		JsValue vv1 = js_to_string(inter, v1, line);
		v =*(INTERPRETE_concat_string(inter,&vv1,v2,line));
	}

	


	return v;
}







JsValue js_to_string(JsInterpreter* inter,const JsValue* value,int line){
	JsValue* v;
	switch (value->typ)
		{
			case JS_VALUE_TYPE_BOOL:
				v = INTERPRETE_creaet_heap(inter, JS_VALUE_TYPE_STRING ,6, line);
				if(JS_BOOL_TRUE == v->u.boolvalue){
					v->u.string->length = 4;
					strncpy(v->u.string->s,"true",4);
					v->u.string->s[v->u.string->length] = 0;
				}else{
					v->u.string->length = 5;
					strncpy(v->u.string->s,"false",5);
					v->u.string->s[v->u.string->length] = 0;
				}
				break;
			case JS_VALUE_TYPE_INT:/*how to calculate size */
				v = INTERPRETE_creaet_heap(inter, JS_VALUE_TYPE_STRING ,100, line);
				v->u.string->length = snprintf(v->u.string->s,100,"%d",value->u.intvalue);
				break;
			case JS_VALUE_TYPE_FLOAT:
				v = INTERPRETE_creaet_heap(inter, JS_VALUE_TYPE_STRING ,100, line);
				v->u.string->length = snprintf(v->u.string->s,100,"%f",value->u.floatvalue);
				break;
			case JS_VALUE_TYPE_STRING:
				*v = *value;
				break;
			case JS_VALUE_TYPE_ARRAY:
				v = INTERPRETE_creaet_heap(inter, JS_VALUE_TYPE_STRING ,6, line);
				v->u.string->length = 5;
				strncpy(v->u.string->s,"array",5);
				v->u.string->s[v->u.string->length] = 0;
				break;
			case JS_VALUE_TYPE_FUNCTION:
				v = INTERPRETE_creaet_heap(inter, JS_VALUE_TYPE_STRING ,100, line);
				v->u.string->length = snprintf(v->u.string->s,100,"function:%s",value->u.func->name);
				v->u.string->s[v->u.string->length] = 0;
				break;
			case JS_VALUE_TYPE_NULL:
				v = INTERPRETE_creaet_heap(inter, JS_VALUE_TYPE_STRING ,5, line);
				v->u.string->length = 4;
				strncpy(v->u.string->s,"null",4);
				v->u.string->s[v->u.string->length] = 0;
				break;
			case JS_VALUE_TYPE_UNDEFINED:
				v = INTERPRETE_creaet_heap(inter, JS_VALUE_TYPE_STRING ,10, line);
				v->u.string->length = 9;
				strncpy(v->u.string->s,"undefined",9);
				v->u.string->s[v->u.string->length] = 0;
				break;
			default:
				ERROR_runtime_error(RUNTIME_ERROR_TYPE_NOE_RIGHT, line);
	}
	return *v;
}



JsValue js_value_mod(const JsValue* v1,const JsValue* v2){
	JsValue v;
	v.typ = JS_VALUE_TYPE_INT;
	int left = 0 ;
	int right = 0;
	if(JS_VALUE_TYPE_INT == v1->typ){
		left = v1->u.intvalue;
	}
	if(JS_VALUE_TYPE_FLOAT == v1->typ){
		left = (int)v1->u.floatvalue;
	}
	if(JS_VALUE_TYPE_INT == v2->typ){
		right = v2->u.intvalue;
	}
	if(JS_VALUE_TYPE_FLOAT == v2->typ){
		right = (int)v2->u.floatvalue;
	}
	if(0 == left || 0 == right){
		v.u.intvalue = 0;
	}else{
		v.u.intvalue = left%right;
	}
	return v;
	
}

JsValue js_value_mul(const JsValue* v1,const JsValue* v2){
	JsValue v;
	if(JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_INT == v2->typ){
		v.typ = JS_VALUE_TYPE_INT;
		v.u.intvalue = v1->u.intvalue * v2->u.intvalue;
	}
	if(JS_VALUE_TYPE_FLOAT== v1->typ && JS_VALUE_TYPE_INT == v2->typ){
		v.typ = JS_VALUE_TYPE_FLOAT;
		v.u.floatvalue = v1->u.floatvalue * v2->u.intvalue;
	}
	if(JS_VALUE_TYPE_INT== v1->typ && JS_VALUE_TYPE_FLOAT == v2->typ){
		v.typ = JS_VALUE_TYPE_FLOAT;
		v.u.floatvalue = v1->u.intvalue* v2->u.floatvalue;
	}
	if(JS_VALUE_TYPE_FLOAT== v1->typ && JS_VALUE_TYPE_FLOAT == v2->typ){
		v.typ = JS_VALUE_TYPE_FLOAT;
		v.u.floatvalue = v1->u.floatvalue* v2->u.floatvalue;
	}
	return v;
}

JsValue js_value_div(const JsValue* v1,const JsValue* v2){
	JsValue v;
	v.typ = JS_VALUE_TYPE_FLOAT;
	v.u.floatvalue = 0;
	if(JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_INT == v2->typ){
		if(0 != v2->u.intvalue){
			v.u.floatvalue = ((double)v1->u.intvalue )/ ((double)v2->u.intvalue);
		}
	}
	if(JS_VALUE_TYPE_FLOAT== v1->typ && JS_VALUE_TYPE_INT == v2->typ){
		if(0 != v2->u.intvalue){
			v.u.floatvalue = v1->u.floatvalue / ((double)v2->u.intvalue);
		}
	}
	if(JS_VALUE_TYPE_INT== v1->typ && JS_VALUE_TYPE_FLOAT == v2->typ){
		if(!ISZORE(v2->u.floatvalue)){
			v.u.floatvalue = ((double)v1->u.intvalue)/v2->u.floatvalue;
		}
	}
	if(JS_VALUE_TYPE_FLOAT== v1->typ && JS_VALUE_TYPE_FLOAT == v2->typ){
		v.typ = JS_VALUE_TYPE_FLOAT;
		v.u.floatvalue = v1->u.floatvalue / v2->u.floatvalue;
	}
	return v;
}

JsValue js_value_sub(const JsValue* v1,const JsValue* v2){
	JsValue v;
	if(JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_INT == v2->typ){
		v.typ = JS_VALUE_TYPE_INT;
		v.u.intvalue = v1->u.intvalue - v2->u.intvalue;
	}
	if(JS_VALUE_TYPE_FLOAT== v1->typ && JS_VALUE_TYPE_INT == v2->typ){
		v.typ = JS_VALUE_TYPE_FLOAT;
		v.u.floatvalue = v1->u.floatvalue - v2->u.intvalue;
	}
	if(JS_VALUE_TYPE_INT== v1->typ && JS_VALUE_TYPE_FLOAT == v2->typ){
		v.typ = JS_VALUE_TYPE_FLOAT;
		v.u.floatvalue = v1->u.intvalue - v2->u.floatvalue;
	}
	if(JS_VALUE_TYPE_FLOAT== v1->typ && JS_VALUE_TYPE_FLOAT == v2->typ){
		v.typ = JS_VALUE_TYPE_FLOAT;
		v.u.floatvalue = v1->u.floatvalue - v2->u.floatvalue;
	}
	return v;
}








JSBool js_value_equal(const JsValue* v1,const JsValue* v2){
	if(v1->typ != v2->typ){
		return JS_BOOL_FALSE;
	}
	if(JS_VALUE_TYPE_BOOL == v1->typ){
		if(v1->u.boolvalue == v2->u.boolvalue){
			return JS_BOOL_TRUE;
		}else{
			return JS_BOOL_FALSE;
		}
	}
	if(JS_VALUE_TYPE_INT == v1->typ){
		if(v1->u.intvalue == v2->u.intvalue){
			return JS_BOOL_TRUE;
		}else{
			return JS_BOOL_FALSE;
		}
	}
	if(JS_VALUE_TYPE_FLOAT == v1->typ){
		if(v1->u.floatvalue == v2->u.floatvalue){
			return JS_BOOL_TRUE;
		}else{
			return JS_BOOL_FALSE;
		}
	}
	if(JS_VALUE_TYPE_STRING == v1->typ){  /*must be a obejct*/
		if(0 == strcmp(v1->u.string->s,v2->u.string->s)){
			return JS_BOOL_TRUE;
		}else{
			return JS_BOOL_FALSE;
		}
	}
	return JS_BOOL_FALSE;
}


JSBool js_value_greater(const JsValue* v1,const JsValue* v2){
	if(JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_INT == v2->typ){
		if(v1->u.intvalue > v2->u.intvalue){
			return JS_BOOL_TRUE;
		}else{
			return JS_BOOL_FALSE;
		}
	}
	
	if(JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_FLOAT== v2->typ){
			if(v1->u.intvalue > v2->u.floatvalue){
				return JS_BOOL_TRUE;
			}else{
				return JS_BOOL_FALSE;
			}
	}
	if(JS_VALUE_TYPE_FLOAT == v1->typ && JS_VALUE_TYPE_INT== v2->typ){
			if(v1->u.floatvalue> v2->u.intvalue){
				return JS_BOOL_TRUE;
			}else{
				return JS_BOOL_FALSE;
			}
	}

	if(JS_VALUE_TYPE_FLOAT == v1->typ && JS_VALUE_TYPE_FLOAT== v2->typ){
			if(v1->u.floatvalue> v2->u.floatvalue){
				return JS_BOOL_TRUE;
			}else{
				return JS_BOOL_FALSE;
			}
	}

	if(JS_VALUE_TYPE_STRING == v1->typ && JS_VALUE_TYPE_STRING ==  v2->typ){
		if(strcmp(v1->u.string->s,v2->u.string->s) > 0){
			return JS_BOOL_TRUE;
		}else{
			return JS_BOOL_FALSE;
		}
	}
	return JS_BOOL_FALSE;
}



JSBool js_value_greater_or_equal(const JsValue* v1,const JsValue* v2){
	if(JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_INT == v2->typ){
		if(v1->u.intvalue >= v2->u.intvalue){
			return JS_BOOL_TRUE;
		}else{
			return JS_BOOL_FALSE;
		}
	}
	
	if(JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_FLOAT== v2->typ){
			if(v1->u.intvalue >= v2->u.floatvalue){
				return JS_BOOL_TRUE;
			}else{
				return JS_BOOL_FALSE;
			}
	}
	if(JS_VALUE_TYPE_FLOAT == v1->typ && JS_VALUE_TYPE_INT== v2->typ){
			if(v1->u.floatvalue>= v2->u.intvalue){
				return JS_BOOL_TRUE;
			}else{
				return JS_BOOL_FALSE;
			}
	}

	if(JS_VALUE_TYPE_FLOAT == v1->typ && JS_VALUE_TYPE_FLOAT== v2->typ){
			if(v1->u.floatvalue>= v2->u.floatvalue){
				return JS_BOOL_TRUE;
			}else{
				return JS_BOOL_FALSE;
			}
	}

	if(JS_VALUE_TYPE_STRING== v1->typ && JS_VALUE_TYPE_STRING ==  v2->typ){
		if(strcmp(v1->u.string->s,v2->u.string->s) >= 0){
			return JS_BOOL_TRUE;
		}else{
			return JS_BOOL_FALSE;
		}
	}
	return JS_BOOL_FALSE;
}




void js_print(const JsValue *value){
	switch (value->typ)
		{
			case JS_VALUE_TYPE_BOOL:
				if(JS_BOOL_TRUE == value->u.boolvalue){
					printf("true");
				}else{
					printf("false");
				}
				break;
			case JS_VALUE_TYPE_INT:
				printf("%d",value->u.intvalue);
				break;
			case JS_VALUE_TYPE_FLOAT:
				printf("%f",value->u.floatvalue);
				break;
			case JS_VALUE_TYPE_STRING:
				printf("%s",value->u.string->s);
				break;
			case JS_VALUE_TYPE_NULL:
				printf("null");
				break;
			case JS_VALUE_TYPE_UNDEFINED:
				printf("undefined");
				break;
			case JS_VALUE_TYPE_ARRAY:
				js_print_array(value->u.array);
				break;
			case JS_VALUE_TYPE_FUNCTION:
				printf("function");
				break;
		}

}


void js_print_array(JsArray* array){
	if(NULL == array || 0 == array->length){
		return ;
	}
	int i;
	printf("[");
	for(i = 0;i<array->length;i++){
		js_print(array->elements + i);
		if(i < array->length -1){
			printf(",");
		}
	}
	printf("]");
}

void js_println(const JsValue *value){
	
}





