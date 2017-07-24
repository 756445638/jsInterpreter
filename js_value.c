#include "js.h"
#include <string.h>



JSBool is_js_value_true(JsValue* v){
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
		int length = strlen(v->u.string);
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


JsValue js_increment_or_decrment(JsValue* v,char increment){
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

JsValue js_nagetive(JsValue* v){
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




JsValue js_value_add(JsValue* v1,JsValue* v2){
	JsValue v;
	/*handle number part*/
	if(EXPRESSION_TYPE_INT == v1->typ && EXPRESSION_TYPE_INT == v2->typ){
		v.typ = EXPRESSION_TYPE_INT;
		v.u.intvalue = v1->u.intvalue + v2->u.intvalue;
		return v;
	}
	if(EXPRESSION_TYPE_FLOAT== v1->typ && EXPRESSION_TYPE_INT == v2->typ){
		v.typ = EXPRESSION_TYPE_FLOAT;
		v.u.floatvalue = v1->u.floatvalue + v2->u.intvalue;
		return v;
	}
	if(EXPRESSION_TYPE_INT == v1->typ && EXPRESSION_TYPE_FLOAT == v2->typ){
		v.typ = EXPRESSION_TYPE_FLOAT;
		v.u.floatvalue = v1->u.intvalue + v2->u.floatvalue;
		return v;
	}
	if(EXPRESSION_TYPE_FLOAT == v1->typ && EXPRESSION_TYPE_FLOAT == v2->typ){
		v.typ = EXPRESSION_TYPE_FLOAT;
		v.u.floatvalue = v1->u.floatvalue + v2->u.floatvalue;
		return v;
	}
	/*handle string part*/
	

	return *v1;
}


JsValue js_value_mod(JsValue* v1,JsValue* v2){
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

JsValue js_value_mul(JsValue* v1,JsValue* v2){
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

JsValue js_value_div(JsValue* v1,JsValue* v2){
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

JsValue js_value_sub(JsValue* v1,JsValue* v2){
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








JSBool js_value_equal(JsValue* v1,JsValue* v2){
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
		if(0 == strcmp(v1->u.string,v2->u.string)){
			return JS_BOOL_TRUE;
		}else{
			return JS_BOOL_FALSE;
		}
	}
	return JS_BOOL_FALSE;
}


JSBool js_value_greater(JsValue* v1,JsValue* v2){
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
		if(strcmp(v1->u.string,v2->u.string) > 0){
			return JS_BOOL_TRUE;
		}else{
			return JS_BOOL_FALSE;
		}
	}
	return JS_BOOL_FALSE;
}



JSBool js_value_greater_or_equal(JsValue* v1,JsValue* v2){
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
		if(strcmp(v1->u.string,v2->u.string) >= 0){
			return JS_BOOL_TRUE;
		}else{
			return JS_BOOL_FALSE;
		}
	}
	return JS_BOOL_FALSE;
}





