#include "js.h"
#include  "stack.h"
#include "util.h"
#include "memory.h"
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
	if(JS_VALUE_TYPE_OBJECT == v->typ &&  JS_OBJECT_TYPE_STRING  == v->u.object->typ){
		int length = STRING_length(v->u.object->u.string);
		if(0 == length){
			return JS_BOOL_FALSE;
		}else{
			return JS_BOOL_TRUE;
		}
	}
	if(JS_VALUE_TYPE_OBJECT == v->typ &&  JS_OBJECT_TYPE_ARRAY== v->u.object->typ){
		if(0 == v->u.object->u->array->length){
			return JS_BOOL_FALSE;
		}else{
			return JS_BOOL_TRUE;
		}
	}
	return JS_BOOL_FALSE;
	
}


JsValue js_value_add(Memory* m,JsValue* v1,JsValue* v2){
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
		left = int(v1->u.floatvalue);
	}
	if(JS_VALUE_TYPE_INT == v2->typ){
		right = v2->u.intvalue;
	}
	if(JS_VALUE_TYPE_FLOAT == v2->typ){
		right = int(v2->u.floatvalue);
	}
	if(0 == left || 0 == right){
		v.u->intvalue = 0;
	}else{
		v.u->intvalue = left%right;
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
	v->typ = JS_VALUE_TYPE_FLOAT;
	v->u.floatvalue = 0;
	if(JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_INT == v2->typ){
		if(0 != v2->u.intvalue){
			v.u.floatvalue = double(v1->u.intvalue) / double(v2->u.intvalue);
		}
	}
	if(JS_VALUE_TYPE_FLOAT== v1->typ && JS_VALUE_TYPE_INT == v2->typ){
		if(0 != v2->u.intvalue){
			v.u.floatvalue = v1->u.floatvalue / double(v2->u.intvalue);
		}
	}
	if(JS_VALUE_TYPE_INT== v1->typ && JS_VALUE_TYPE_FLOAT == v2->typ){
		if(!ISZORE(v2)){
			v.u.floatvalue = double(v1->u.intvalue)/v2->u.floatvalue;
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
		v->typ = JS_VALUE_TYPE_INT;
		v->u.intvalue = v1->u.intvalue - v2->u.intvalue;
	}
	if(JS_VALUE_TYPE_FLOAT== v1->typ && JS_VALUE_TYPE_INT == v2->typ){
		v->typ = JS_VALUE_TYPE_FLOAT;
		v->u.floatvalue = v1->u.floatvalue - v2->u.intvalue;
	}
	if(JS_VALUE_TYPE_INT== v1->typ && JS_VALUE_TYPE_FLOAT == v2->typ){
		v->typ = JS_VALUE_TYPE_FLOAT;
		v->u.floatvalue = v1->u.intvalue - v2->u.floatvalue;
	}
	if(JS_VALUE_TYPE_FLOAT== v1->typ && JS_VALUE_TYPE_FLOAT == v2->typ){
		v.typ = JS_VALUE_TYPE_FLOAT;
		v.u.floatvalue = v1->u.floatvalue - v2->u.floatvalue;
	}
	return v;
}








JSBool js_value_equal(JsValue* v1,JsValue* v2){
	if(v1->typ != v2->typ){
		return JS_BOOL_FLASE;
	}
	if(JS_VALUE_TYPE_BOOL == v1->typ){
		if(v1->u.boolvalue == v2->u.boolvalue){
			return JS_BOOL_TRUE;
		}else{
			return JS_BOOL_FLASE;
		}
	}
	if(JS_VALUE_TYPE_INT == v1->typ){
		if(v1->u.intvalue == v2->u.intvalue){
			return JS_BOOL_TRUE;
		}else{
			return JS_BOOL_FLASE;
		}
	}
	if(JS_VALUE_TYPE_FLOAT == v1->typ){
		if(v1->u.floatvalue == v2->u.floatvalue){
			return JS_BOOL_TRUE;
		}else{
			return JS_BOOL_FLASE;
		}
	}
	if(JS_VALUE_TYPE_OBJECT == v1->typ){  /*must be a obejct*/
		if(JS_OBJECT_TYPE_STRING == v1->u.object->typ){
			if(0 == strcmp(v1->u.object->u.string->s,v2->u.object->u.string->s)){
				return JS_BOOL_TRUE;
			}else{
				return JS_BOOL_FLASE;
			}
		}else{ /*compare pointer*/
			if(v1->u.object == v2->u.object){
				return JS_BOOL_TRUE;
			}else{
				return JS_BOOL_FLASE;
			}
		}
	}
	return JS_BOOL_FLASE;
}


JSBool js_value_greater(JsValue* v1,JsValue* v2){
	if(JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_INT == v2->typ){
		if(v1->u.intvalue > v2->u.intvalue){
			return JS_BOOL_TRUE;
		}else{
			return JS_BOOL_FLASE;
		}
	}
	
	if(JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_FLOAT== v2->typ){
			if(v1->u.intvalue > v2->u.floatvalue){
				return JS_BOOL_TRUE;
			}else{
				return JS_BOOL_FLASE;
			}
	}
	if(JS_VALUE_TYPE_FLOAT == v1->typ && JS_VALUE_TYPE_INT== v2->typ){
			if(v1->u.floatvalue> v2->u.intvalue){
				return JS_BOOL_TRUE;
			}else{
				return JS_BOOL_FLASE;
			}
	}

	if(JS_VALUE_TYPE_FLOAT == v1->typ && JS_VALUE_TYPE_FLOAT== v2->typ){
			if(v1->u.floatvalue> v2->u.floatvalue){
				return JS_BOOL_TRUE;
			}else{
				return JS_BOOL_FLASE;
			}
	}

	if(JS_VALUE_TYPE_OBJECT == v1->typ && JS_VALUE_TYPE_OBJECT ==  v2->typ){
		if(JS_OBJECT_TYPE_STRING == v1->u.object->typ && JS_OBJECT_TYPE_STRING == v2->u.object->typ){
			if(strcmp(v1->u.object->u.string.s,v2->u.object->u.string.s) > 0){
				return JS_BOOL_TRUE;
			}else{
				return JS_BOOL_FLASE;
			}
		}
	}
	return JS_BOOL_FLASE;
}



JSBool js_value_greater_or_equal(JsValue* v1,JsValue* v2){
	if(JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_INT == v2->typ){
		if(v1->u.intvalue >= v2->u.intvalue){
			return JS_BOOL_TRUE;
		}else{
			return JS_BOOL_FLASE;
		}
	}
	
	if(JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_FLOAT== v2->typ){
			if(v1->u.intvalue >= v2->u.floatvalue){
				return JS_BOOL_TRUE;
			}else{
				return JS_BOOL_FLASE;
			}
	}
	if(JS_VALUE_TYPE_FLOAT == v1->typ && JS_VALUE_TYPE_INT== v2->typ){
			if(v1->u.floatvalue>= v2->u.intvalue){
				return JS_BOOL_TRUE;
			}else{
				return JS_BOOL_FLASE;
			}
	}

	if(JS_VALUE_TYPE_FLOAT == v1->typ && JS_VALUE_TYPE_FLOAT== v2->typ){
			if(v1->u.floatvalue>= v2->u.floatvalue){
				return JS_BOOL_TRUE;
			}else{
				return JS_BOOL_FLASE;
			}
	}

	if(JS_VALUE_TYPE_OBJECT == v1->typ && JS_VALUE_TYPE_OBJECT ==  v2->typ){
		if(JS_OBJECT_TYPE_STRING == v1->u.object->typ && JS_OBJECT_TYPE_STRING == v2->u.object->typ){
			if(strcmp(v1->u.object->u.string.s,v2->u.object->u.string.s) >= 0){
				return JS_BOOL_TRUE;
			}else{
				return JS_BOOL_FLASE;
			}
		}
	}
	return JS_BOOL_FLASE;
}





int get_expression_list_length(ExpressionList* list){
    int length = 0;
    while(NULL != list){
        list = list->next;
        length++;
    }
    return length;
};


int eval_expression(JsInterpreter* inter,ExecuteEnvironment* env,Expression* e){
	JsValue v ;
	/*bool expression*/
	if(e->typ == EXPRESSION_TYPE_BOOL){
		v.typ = JS_VALUE_TYPE_BOOL;
		v.u.boolvalue = e->u.bool_value;
		push_stack(&inter->stack,&v);
		return 0;
	}
	/*int value*/
	if(e->typ == EXPRESSION_TYPE_INT){
		v.typ = JS_VALUE_INT;
		v.u.intvalue = e->u.int_value;
		push_stack(&inter->stack,&v);
		return 0;
	}
	/*double value*/
	if(EXPRESSION_TYPE_FLOAT== e->typ){
		v.typ = JS_VALUE_FLOAT;
		v.u.floatvalue = e->u.double_value;
		push_stack(&inter->stack,&v);
		return 0;
	}

	/*assign*/
	if(EXPRESSION_TYPE_ASSIGN == e->typ){
		eval_assign_expression(env,e);
		return 0;
	}
	if(EXPRESSION_TYPE_NE == e->typ
		|| EXPRESSION_TYPE_EQ ==  e->typ
		|| EXPRESSION_TYPE_GE == e->typ
		|| EXPRESSION_TYPE_GT == e->typ
		|| EXPRESSION_TYPE_LE ==  e->typ
		|| EXPRESSION_TYPE_LT == e->typ
			
	){
		eval_relation_expression(inter,env,e,&v);
		return 0;
	}
	if(EXPRESSION_TYPE_ADD == e->typ
		|| EXPRESSION_TYPE_SUB == e->typ
		|| EXPRESSION_TYPE_MUL == e->typ
		|| EXPRESSION_TYPE_DIV == e->typ
		|| EXPRESSION_TYPE_MOD == e->typ
		
	){
		eval_arithmetic_expression(inter,env,e);
		return 0;
	}
	if(EXPRESSION_TYPE_STRING == e->typ){
		eval_string_expression();
		return 0;
	}
	if(EXPRESSION_TYPE_LOGICAL_OR == e->typ 
		|| EXPRESSION_TYPE_LOGICAL_AND == e->typ
	){
		
	}
	
	

	
	
	return -1;
	
	
}


void eval_logical_expression(JsInterpreter * inter,ExecuteEnvironment *env,Expression* e){
	JsValue v;
	v.typ = JS_VALUE_TYPE_BOOL;
	eval_expression(inter,env,e->u.binary->left);
	JsValue* left = pop_stack(inter->stack);
	v.u.boolvalue = is_js_value_true(left);
	if(JS_BOOL_FLASE == v.u.boolvalue  && EXPRESSION_TYPE_LOGICAL_AND == e->typ){
		 push_stack(inter->stack,&v);
		 return;
	}
	if(JS_BOOL_TRUE == v.u.boolvalue  && EXPRESSION_TYPE_LOGICAL_OR == e->typ){
		 push_stack(inter->stack,&v);
		 return;
	}
	eval_expression(inter,env,e->u.binary->right);
	JsValue* right = pop_stack(inter->stack);
	JSBool second = is_js_value_true(right);
	if(JS_BOOL_TRUE == v.u.boolvalue  && EXPRESSION_TYPE_LOGICAL_AND == e->typ){
		 if(JS_BOOL_FLASE== second){
			v.u.boolvalue = JS_BOOL_FLASE;
		 }
		 push_stack(inter->stack,&v);
		 return;
	}
	if(JS_BOOL_FLASE == v.u.boolvalue && EXPRESSION_TYPE_LOGICAL_OR == e->typ){
		if(JS_BOOL_TRUE == second){
			v.u.boolvalue = JS_BOOL_TRUE;
		}
		push_stack(inter->stack,&v);
		return;
	}
	
}

void eval_string_expression(JsInterpreter * inter,Expression* e){
	JsValue v;
	v->typ = JS_VALUE_TYPE_OBJECT;
	JsObejct* obj = MEM_alloc(inter->excute_memory,sizeof(JsObejct),e->line);
	v->u.object = obj;
	obj->typ = JS_OBJECT_TYPE_STRING;
	obj->u.string = STRING_new_form_chars(inter->excute_memory,e->u.object->u.string->s);
	push_stack(inter->stack,&v);
	return ;
}




void eval_arithmetic_expression(JsInterpreter * inter,ExecuteEnvironment* env,Expression* e){
	JsValue v;
	eval_expression(inter,env,e->u.binary->left);
	eval_expression(inter,env,e->u.binary->right);
	JsValue* right = pop_stack(inter->stack);
	JsValue* left = pop_stack(inter->stack);
	if(EXPRESSION_TYPE_MUL == e->typ){
		v = js_value_mul(left,right);
	}
	if(EXPRESSION_TYPE_MOD == e->typ){
		v = js_value_mod(left,right);
	}
	if(EXPRESSION_TYPE_DIV == e->typ){
		v = js_value_div(left,right);
	}
	if(EXPRESSION_TYPE_SUB == e->typ){
		v = js_value_sub(left,right);
	}
	if(EXPRESSION_TYPE_ADD == e->typ){
		v = js_value_add(left,right);
	}
	push_stack(inter->stack,&v);
}




void eval_relation_expression(JsInterpreter * inter,ExecuteEnvironment* env,Expression* e){
	JsValue v;
	v.typ = JS_VALUE_TYPE_BOOL;
	v.u.boolvalue = JS_BOOL_FLASE;
	eval_expression(inter,env,e->u.binary->left);
	eval_expression(inter,env,e->u.binary->right);
	JsValue* right = pop_stack(inter->stack);
	JsValue* left = pop_stack(inter->stack);
	if(EXPRESSION_TYPE_EQ  == e->typ){
		v.u.boolvalue = js_value_equal(left,right);
	}
	if(EXPRESSION_TYPE_NE  == e->typ){
		v.u.boolvalue = js_value_equal(left,right);
		if(JS_BOOL_FLASE== v.u.boolvalue){
			v.u.boolvalue = JS_BOOL_TRUE;
		}else{
			v.u.boolvalue = JS_BOOL_FALSE;
		}
	}
	if(EXPRESSION_TYPE_GE == e->typ){
		v.u.boolvalue = js_value_greater_or_equal(left,right);
	}
	if(EXPRESSION_TYPE_LE == e->typ){
		v.u.boolvalue = js_value_greater_or_equal(left,right);
		if(JS_BOOL_FLASE== v.u.boolvalue){
			v.u.boolvalue = JS_BOOL_TRUE;
		}else{
			v.u.boolvalue = JS_BOOL_FALSE;
		}
	}
	if(EXPRESSION_TYPE_GT == e->typ){
		v.u.boolvalue = js_value_greater(left,right);
	}
	if(EXPRESSION_TYPE_LT == e->typ){
		v.u.boolvalue = js_value_greater(left,right);
		if(JS_BOOL_FLASE== v.u.boolvalue){
			v.u.boolvalue = JS_BOOL_TRUE;
		}else{
			v.u.boolvalue = JS_BOOL_FALSE;
		}
	}
	
	push_stack(inter->stack,&v);
	
}



JsValue eval_assign_expression(JsInterpreter * inter,ExecuteEnvironment* env,Expression* e){
	JsValue v = eval_expression(env,e);/*get assign value*/
	JsValue *dest = get_left_value(env,e->u.binary.left);
	Variable* var;
	if(NULL == dest){
		if(EXPRESSION_TYPE_IDENTIFIER ==  e->typ){
			var = INTERPRETE_create_global_variable(inter,e->u.identifier,NULL);/*create a global variable*/
			dest = &var->value;
		}else{
			ERROR_runtime_error(RUNTIME_ERROR_VARIABLE_NOT_FOUND,e->line);
		}
	}
	*dest = v;
	return v;
}

JsValue* get_left_value(ExecuteEnvironment* env,Expression* e){
	JsValue* ret = NULL;
	while(NULL != env){
		if(EXPRESSION_TYPE_IDENTIFIER == e->typ){
			ret = search_variable_from_variablelist(env->vars,e->u.identifier);
			if(NULL == ret){
				env = env->outter;
			}else{
				return ret;
			}
		}
	}
	return NULL;
}

Variable* search_variable_from_variablelist(VariableList* list,char* identifier){
	if(NULL == list){
		return NULL;
	}
	while(NULL != list){
		if(0 == strcmp(identifier,list.var->name)){
			return &list.var;
		}
		list = list->next;
	}
	return NULL;
}













