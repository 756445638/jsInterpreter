#include "js.h"
#include  "stack.h"
#include "util.h"
#include "memory.h"
#include "js_value.h"
#include "error.h"
#include <string.h>





int get_expression_list_length(ExpressionList* list){
    int length = 0;
    while(NULL != list){
        list = list->next;
        length++;
    }
    return length;
};







void eval_create_local_variable_expression(JsInterpreter * inter,ExecuteEnvironment *env,Expression* e){
	Variable* var = search_variable_from_variablelist(env->vars,e->u.create_var->identifier);
	if(NULL != var){
		ERROR_runtime_error(RUNTIME_ERROR_VARIALBE_ALEAY_DECLARED,e->line);
		return ;
	}
	eval_expression(inter,env,e);
	JsValue* v = pop_stack(&inter->stack);
	
}



void eval_negative_expression(JsInterpreter * inter,ExecuteEnvironment *env,Expression* e){
	eval_expression(inter,env,e->u.unary);
	JsValue* v = pop_stack(&inter->stack);
	*v = js_nagetive(v) ;/*write value back*/
	push_stack(&inter->stack,v);
	return ;
}

void eval_increment_decrement_expression(JsInterpreter * inter,ExecuteEnvironment *env,Expression* e){
	eval_expression(inter,env,e->u.unary);
	JsValue* v = pop_stack(&inter->stack);
	if(EXPRESSION_TYPE_INCREMENT == e->typ){
		js_increment_or_decrment( v,1);
	}else{
		js_increment_or_decrment( v,0);
	}
	push_stack(&inter->stack,v);
	return ;
}


void eval_logical_expression(JsInterpreter * inter,ExecuteEnvironment *env,Expression* e){
	JsValue v;
	v.typ = JS_VALUE_TYPE_BOOL;
	eval_expression(inter,env,e->u.binary->left);
	JsValue* left = pop_stack(&inter->stack);
	v.u.boolvalue = is_js_value_true(left);
	if(JS_BOOL_FALSE == v.u.boolvalue  && EXPRESSION_TYPE_LOGICAL_AND == e->typ){
		 push_stack(&inter->stack,&v);
		 return;
	}
	if(JS_BOOL_TRUE == v.u.boolvalue  && EXPRESSION_TYPE_LOGICAL_OR == e->typ){
		 push_stack(&inter->stack,&v);
		 return;
	}
	eval_expression(inter,env,e->u.binary->right);
	JsValue* right = pop_stack(&inter->stack);
	JSBool second = is_js_value_true(right);
	if(JS_BOOL_TRUE == v.u.boolvalue  && EXPRESSION_TYPE_LOGICAL_AND == e->typ){
		 if(JS_BOOL_FALSE== second){
			v.u.boolvalue = JS_BOOL_FALSE;
		 }
		 push_stack(&inter->stack,&v);
		 return;
	}
	if(JS_BOOL_FALSE == v.u.boolvalue && EXPRESSION_TYPE_LOGICAL_OR == e->typ){
		if(JS_BOOL_TRUE == second){
			v.u.boolvalue = JS_BOOL_TRUE;
		}
		push_stack(&inter->stack,&v);
		return;
	}
	
}




void eval_string_expression(JsInterpreter * inter,Expression* e){
	JsValue * v = INTERPRETE_creaet_heap(inter,e->line);
	if(NULL == v){
		return ;
	}
	v->typ = JS_VALUE_TYPE_STRING;
	int length = strlen(e->u.string);
	char *dest = MEM_alloc(inter->excute_memory,length + 1,e->line);
	strncpy(dest,e->u.string,length);
	dest[length] = 0;
	push_stack(&inter->stack,v);
}







void eval_arithmetic_expression(JsInterpreter * inter,ExecuteEnvironment* env,Expression* e){
	JsValue v;
	eval_expression(inter,env,e->u.binary->left);
	eval_expression(inter,env,e->u.binary->right);
	JsValue* right = pop_stack(&inter->stack);
	JsValue* left = pop_stack(&inter->stack);
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
	push_stack(&inter->stack,&v);
}




void eval_relation_expression(JsInterpreter * inter,ExecuteEnvironment* env,Expression* e){
	JsValue v;
	v.typ = JS_VALUE_TYPE_BOOL;
	v.u.boolvalue = JS_BOOL_FALSE;
	eval_expression(inter,env,e->u.binary->left);
	eval_expression(inter,env,e->u.binary->right);
	JsValue* right = pop_stack(&inter->stack);
	JsValue* left = pop_stack(&inter->stack);
	if(EXPRESSION_TYPE_EQ  == e->typ){
		v.u.boolvalue = js_value_equal(left,right);
	}
	if(EXPRESSION_TYPE_NE  == e->typ){
		v.u.boolvalue = js_value_equal(left,right);
		if(JS_BOOL_FALSE== v.u.boolvalue){
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
		if(JS_BOOL_FALSE== v.u.boolvalue){
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
		if(JS_BOOL_FALSE== v.u.boolvalue){
			v.u.boolvalue = JS_BOOL_TRUE;
		}else{
			v.u.boolvalue = JS_BOOL_FALSE;
		}
	}
	
	push_stack(&inter->stack,&v);
	
}



JsValue eval_assign_expression(JsInterpreter * inter,ExecuteEnvironment* env,Expression* e){
	JsValue * value = eval_expression(env,e->u.binary->right);/*get assign value*/
	JsValue *dest = get_left_value(env,e->u.binary->left);
	Variable* var;
	if(NULL == dest){
		if(EXPRESSION_TYPE_IDENTIFIER ==  e->typ){
			var = INTERPRETE_create_global_variable(inter,e->u.identifier,NULL);/*create a global variable*/
			dest = &var->value;
		}else{
			ERROR_runtime_error(RUNTIME_ERROR_VARIABLE_NOT_FOUND,e->line);
		}
	}
	*dest = *value;
	return *value;
}






// int eval_expression(JsInterpreter* inter,ExecuteEnvironment* env,Expression* e){
// 	JsValue v ;
// 	/*bool expression*/
// 	if(e->typ == EXPRESSION_TYPE_BOOL){
// 		v.typ = JS_VALUE_TYPE_BOOL;
// 		v.u.boolvalue = e->u.bool_value;
// 		push_stack(&inter->stack,&v);
// 		return 0;
// 	}
// 	/*int value*/
// 	if(e->typ == EXPRESSION_TYPE_INT){
// 		v.typ = JS_VALUE_TYPE_INT;
// 		v.u.intvalue = e->u.int_value;
// 		push_stack(&inter->stack,&v);
// 		return 0;
// 	}
// 	/*double value*/
// 	if(EXPRESSION_TYPE_FLOAT== e->typ){
// 		v.typ = JS_VALUE_TYPE_FLOAT;
// 		v.u.floatvalue = e->u.double_value;
// 		push_stack(&inter->stack,&v);
// 		return 0;
// 	}

// 	/*assign*/
// 	if(EXPRESSION_TYPE_ASSIGN == e->typ){
// 		eval_assign_expression(env,e);
// 		return 0;
// 	}
// 	if(EXPRESSION_TYPE_NE == e->typ
// 		|| EXPRESSION_TYPE_EQ ==  e->typ
// 		|| EXPRESSION_TYPE_GE == e->typ
// 		|| EXPRESSION_TYPE_GT == e->typ
// 		|| EXPRESSION_TYPE_LE ==  e->typ
// 		|| EXPRESSION_TYPE_LT == e->typ
			
// 	){
// 		eval_relation_expression(inter,env,e,&v);
// 		return 0;
// 	}
// 	if(EXPRESSION_TYPE_ADD == e->typ
// 		|| EXPRESSION_TYPE_SUB == e->typ
// 		|| EXPRESSION_TYPE_MUL == e->typ
// 		|| EXPRESSION_TYPE_DIV == e->typ
// 		|| EXPRESSION_TYPE_MOD == e->typ
		
// 	){
// 		eval_arithmetic_expression(inter,env,e);
// 		return 0;
// 	}
// 	if(EXPRESSION_TYPE_STRING == e->typ){
// 		eval_string_expression();
// 		return 0;
// 	}
// 	if(EXPRESSION_TYPE_LOGICAL_OR == e->typ 
// 		|| EXPRESSION_TYPE_LOGICAL_AND == e->typ
// 	){
// 		eval_logical_expression(inter,env,e);
// 		return 0;
// 	}

// 	if(EXPRESSION_TYPE_INCREMENT == e->typ 
// 		|| EXPRESSION_TYPE_DECREMENT == e->typ
// 	){
// 		eval_increment_decrement_expression(inter,env,e);
// 		return 0;
// 	}
// 	if(EXPRESSION_TYPE_NEGATIVE == e->typ){
// 		eval_negative_expression(inter,env,e);
// 		return 0;
// 	}
// 	if(EXPRESSION_TYPE_CREATE_LOCAL_VARIABLE == e->typ){
// 		eval_create_local_variable_expression(inter,env,e);
// 		return 0;
// 	}
	
	
	
	

	
	
// 	return -1;

	
// }


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

// Variable*
// search_variable_from_variablelist(VariableList* list,char* identifier){
// 	if(NULL == list){
// 		return NULL;
// 	}
// 	while(NULL != list){
// 		if(0 == strcmp(identifier,list.var->name)){
// 			return &list.var;
// 		}
// 		list = list->next;
// 	}
// 	return NULL;
// }













