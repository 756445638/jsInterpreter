#include "js.h"
#include  "stack.h"
#include "util.h"
#include "memory.h"
#include "js_value.h"
#include "error.h"
#include <string.h>
#include "expression.h"
#include "interprete.h"




int get_expression_list_length(ExpressionList* list){
    int length = 0;
    while(NULL != list){
        list = list->next;
        length++;
    }
    return length;
};







// int eval_create_local_variable_expression(JsInterpreter * inter,ExecuteEnvironment *env,Expression* e){
// 	Variable* var = search_variable_from_variablelist(env->vars,e->u.create_var->identifier);
// 	if(NULL != var){
// 		ERROR_runtime_error(RUNTIME_ERROR_VARIALBE_ALEAY_DECLARED,e->line);
// 		return ;
// 	}
// 	eval_expression(inter,env,e);
// 	JsValue* v = pop_stack(&inter->stack);
	
// }



int eval_negative_expression(JsInterpreter * inter,ExecuteEnvironment *env,Expression* e){
	eval_expression(inter,env,e->u.unary);
	JsValue* v = pop_stack(&inter->stack);
	*v = js_nagetive(v) ;/*write value back*/
	push_stack(&inter->stack,v);
	return 0;
}

int eval_increment_decrement_expression(JsInterpreter * inter,ExecuteEnvironment *env,Expression* e){
	eval_expression(inter,env,e->u.unary);
	JsValue* v = pop_stack(&inter->stack);
	if(EXPRESSION_TYPE_INCREMENT == e->typ){
		js_increment_or_decrment( v,1);
	}else{
		js_increment_or_decrment( v,0);
	}
	push_stack(&inter->stack,v);
	return 0;
}


int eval_logical_expression(JsInterpreter * inter,ExecuteEnvironment *env,Expression* e){
	JsValue v;
	v.typ = JS_VALUE_TYPE_BOOL;
	eval_expression(inter,env,e->u.binary->left);
	JsValue* left = pop_stack(&inter->stack);
	v.u.boolvalue = is_js_value_true(left);
	if(JS_BOOL_FALSE == v.u.boolvalue  && EXPRESSION_TYPE_LOGICAL_AND == e->typ){
		 push_stack(&inter->stack,&v);
		 return 0;
	}
	if(JS_BOOL_TRUE == v.u.boolvalue  && EXPRESSION_TYPE_LOGICAL_OR == e->typ){
		 push_stack(&inter->stack,&v);
		 return 0;
	}
	eval_expression(inter,env,e->u.binary->right);
	JsValue* right = pop_stack(&inter->stack);
	JSBool second = is_js_value_true(right);
	if(JS_BOOL_TRUE == v.u.boolvalue  && EXPRESSION_TYPE_LOGICAL_AND == e->typ){
		 if(JS_BOOL_FALSE== second){
			v.u.boolvalue = JS_BOOL_FALSE;
		 }
		 push_stack(&inter->stack,&v);
		 return 0;
	}
	if(JS_BOOL_FALSE == v.u.boolvalue && EXPRESSION_TYPE_LOGICAL_OR == e->typ){
		if(JS_BOOL_TRUE == second){
			v.u.boolvalue = JS_BOOL_TRUE;
		}
		push_stack(&inter->stack,&v);
		return 0;
	}
	
}




int eval_string_expression(JsInterpreter * inter,Expression* e){
	int length = strlen(e->u.string);
	/* length * 2 + 1 in case length is zero*/
	JsValue * v =(JsValue *) INTERPRETE_creaet_heap(inter,JS_VALUE_TYPE_STRING,length * 2 + 1,e->line);
	if(NULL == v){
		return RUNTIME_ERROR_CANNOT_ALLOC_MEMORY;
	}
	v->u.string->length = length;
	strncpy(v->u.string->s,e->u.string,length);
	v->u.string->s[length] = 0;
	push_stack(&inter->stack,v);
	return 0;
}






int eval_arithmetic_expression(JsInterpreter * inter,ExecuteEnvironment* env,Expression* e){
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
		v = js_value_add(inter,left,right,e->line);
	}
	push_stack(&inter->stack,&v);
	return 0;
}




int eval_relation_expression(JsInterpreter * inter,ExecuteEnvironment* env,Expression* e){
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
	return 0;
}



int eval_assign_expression(JsInterpreter * inter,ExecuteEnvironment* env,Expression* e){
	eval_expression(inter,env,e->u.binary->right);/*get assign value*/
	JsValue* value = pop_stack(&inter->stack);
	JsValue *dest = get_left_value(env,e->u.binary->left);
	Variable* var;
	if(NULL == dest){
		if(EXPRESSION_TYPE_IDENTIFIER ==  e->typ){
			var = INTERPRETE_creaet_variable(inter,env,e->u.identifier,NULL,e->line);/*create a global variable*/
			dest = &var->value;
		}
	}
	if(NULL == dest){
		ERROR_runtime_error(RUNTIME_ERROR_VARIABLE_NOT_FOUND,e->line);
		return RUNTIME_ERROR_VARIABLE_NOT_FOUND;
	}
	*dest = *value;
	push_stack(&inter->stack,value);
	return 0;
}


int eval_index_expression(JsInterpreter * inter,ExecuteEnvironment* env,Expression* e){
	eval_expression(inter,env,e->u.index->e);
	JsValue* v = pop_stack(&inter->stack);
	if(JS_VALUE_TYPE_ARRAY != v->typ){
		ERROR_runtime_error(RUNTIME_ERROR_CANNOT_INDEX_THIS_TYPE,e->line);
		return RUNTIME_ERROR_CANNOT_INDEX_THIS_TYPE;
	}
	eval_expression(inter,env,e->u.index->index);
	JsValue* index = pop_stack(&inter->stack);
	if(JS_VALUE_TYPE_INT != index->typ){
		ERROR_runtime_error(RUNTIME_ERROR_INDEX_HAS_WRONG_TYPE,e->line);
		return RUNTIME_ERROR_INDEX_HAS_WRONG_TYPE;
	}
	if(index->u.intvalue < 0 || index->u.intvalue >= v->u.array->length){
		ERROR_runtime_error(RUNTIME_ERROR_INDEX_OUT_RANGE,e->line);
		return RUNTIME_ERROR_INDEX_OUT_RANGE;
	}
	push_stack(&inter->stack,v->u.array->elements + index->u.intvalue);
	return 0;
	
}



int eval_array_expression(JsInterpreter * inter,ExecuteEnvironment* env,Expression* e){
	int length = get_expression_list_length(e->u.expression_list);
	JsValue* v = INTERPRETE_creaet_heap(inter,JS_VALUE_TYPE_ARRAY,length * 2 + 1,e->line);
	if(NULL == v){
		ERROR_runtime_error(RUNTIME_ERROR_CANNOT_ALLOC_MEMORY,e->line);
		return RUNTIME_ERROR_CANNOT_ALLOC_MEMORY;
	}
	v->u.array->length = length;
	int i = 0;
	ExpressionList* list = e->u.expression_list;
	JsValue * vv ;
	while(NULL != list){
		eval_expression(inter,env,list->expression);
		vv = pop_stack(&inter->stack);
		*(v->u.array->elements+i) = *vv;
		i++;
	}
	return 0;
}


int eval_function_call_expression(JsInterpreter* inter,ExecuteEnvironment* env,Expression* e){
	/*only support search global function now!!*/		
	JsFunction* func = INTERPRETE_search_func_from_function_list(inter->env.funcs,e->u.function_call->func);
	if(NULL == func){
		ERROR_runtime_error(RUNTIME_ERROR_FUNCTION_NOT_FOUND,e->line);
		return RUNTIME_ERROR_FUNCTION_NOT_FOUND;
	}
	
	ExecuteEnvironment* callenv = (ExecuteEnvironment*)MEM_alloc(inter->excute_memory,sizeof(ExecuteEnvironment),e->line);
	if(NULL == callenv){
		ERROR_runtime_error(RUNTIME_ERROR_CANNOT_ALLOC_MEMORY,e->line);
		return RUNTIME_ERROR_CANNOT_ALLOC_MEMORY;
	}
	callenv->outter = env;
	callenv->vars = NULL;
	callenv->funcs = NULL;
	//bind paramenters
	ArgumentList* args = e->u.function_call->args;
	ParameterList* paras = func->parameter_list;
	JsValue* v ;
	while(NULL != args){
		/*make value*/
		eval_expression(inter, env, args);
		v = pop_stack(&inter->stack);
		if(NULL != paras){
			INTERPRETE_creaet_variable(inter,callenv,paras->identifier,v,e->line);
			paras = paras->next;
		}
		args = args->next;
	}
	v->typ = JS_VALUE_TYPE_NULL;
	while(NULL != paras){/*args are more than paras,no big deal*/
		INTERPRETE_creaet_variable(inter,callenv,paras->identifier,v,e->line);
		paras = paras->next;
	}

	StatementList* list = func->block->list;
	StamentResult ret ;
	char returned = 0;
	while(NULL != list){
			ret = INTERPRETE_execute_statement(inter, callenv, list->statement);
			switch (ret.typ)
				{
					case STATEMENT_RESULT_TYPE_NORMAL:
						break;/*nothing to do*/
					case STATEMENT_RESULT_TYPE_CONTINUE:
						ERROR_runtime_error(RUNTIME_ERROR_CONTINUE_RETURN_BREAK_CAN_NOT_BE_IN_THIS_SCOPE, list->statement->line);
						return RUNTIME_ERROR_CONTINUE_RETURN_BREAK_CAN_NOT_BE_IN_THIS_SCOPE;
					case STATEMENT_RESULT_TYPE_BREAK:
						ERROR_runtime_error(RUNTIME_ERROR_CONTINUE_RETURN_BREAK_CAN_NOT_BE_IN_THIS_SCOPE, list->statement->line);
						return RUNTIME_ERROR_CONTINUE_RETURN_BREAK_CAN_NOT_BE_IN_THIS_SCOPE;
					case STATEMENT_RESULT_TYPE_RETURN:
						returned = 1;
						goto funcend;
				}
	}
	

funcend:
	/*push stack*/
	if(0 == returned){
		v->typ = JS_VALUE_TYPE_NULL;
		push_stack(&inter->stack, v);
	}

	INTERPRETE_free_env(inter, callenv);


	


	return 0;

}



int eval_expression(JsInterpreter* inter,ExecuteEnvironment* env,Expression* e){
	JsValue v ;
	/*bool expression*/
	switch (e->typ)
		{
			case EXPRESSION_TYPE_BOOL:
				v.typ = JS_VALUE_TYPE_BOOL;
				v.u.boolvalue = e->u.bool_value;
				push_stack(&inter->stack,&v);
				break;
			case EXPRESSION_TYPE_INT:
				v.typ = JS_VALUE_TYPE_INT;
				v.u.intvalue = e->u.int_value;
				push_stack(&inter->stack,&v);
				break;
			case EXPRESSION_TYPE_FLOAT:
				v.typ = JS_VALUE_TYPE_FLOAT;
				v.u.floatvalue = e->u.double_value;
				push_stack(&inter->stack,&v);
				break;
			case EXPRESSION_TYPE_NULL:
				v.typ = JS_VALUE_TYPE_NULL;
				push_stack(&inter->stack,&v);
				break;
			case EXPRESSION_TYPE_ASSIGN:
				return eval_assign_expression(inter,env,e);
			case EXPRESSION_TYPE_NE:
			case EXPRESSION_TYPE_EQ:
			case EXPRESSION_TYPE_GE:
			case EXPRESSION_TYPE_GT:
			case EXPRESSION_TYPE_LE:
			case EXPRESSION_TYPE_LT:
				return eval_relation_expression(inter,env,e);
			case EXPRESSION_TYPE_ADD:
			case EXPRESSION_TYPE_SUB:
			case EXPRESSION_TYPE_MUL:
			case EXPRESSION_TYPE_DIV:
			case EXPRESSION_TYPE_MOD:
				return eval_arithmetic_expression(inter,env,e);
			case EXPRESSION_TYPE_STRING:
				return eval_string_expression(inter,e);
			case EXPRESSION_TYPE_LOGICAL_OR:
			case EXPRESSION_TYPE_LOGICAL_AND:
				return eval_logical_expression(inter,env,e);
			case EXPRESSION_TYPE_INCREMENT:
			case EXPRESSION_TYPE_DECREMENT:
				return eval_increment_decrement_expression(inter,env,e);
			case EXPRESSION_TYPE_NEGATIVE:
				return eval_negative_expression(inter,env,e);
			case EXPRESSION_TYPE_CREATE_LOCAL_VARIABLE:
				return eval_create_variable_expression(inter, env,  e);
			case EXPRESSION_TYPE_INDEX:
				return eval_index_expression(inter,env,e);
			case EXPRESSION_TYPE_ARRAY:
				return eval_array_expression(inter,env,e);
			case EXPRESSION_TYPE_FUNCTION_CALL:
				return eval_function_call_expression(inter,env,e);
			case EXPRESSION_TYPE_IDENTIFIER:
				return eval_identifier_expression(inter,env,e);
		}
	
	return 0;

	
}


int eval_identifier_expression(JsInterpreter * inter,ExecuteEnvironment *env,Expression* e){
	JsValue* v = INTERPRETE_search_variable_from_env(env, e->u.identifier);
	if(NULL == v){
		ERROR_runtime_error(RUNTIME_ERROR_VARIABLE_NOT_FOUND, e->line);
		return RUNTIME_ERROR_VARIABLE_NOT_FOUND;
	}
	push_stack(&inter->stack, v);
	return 0;
}




int eval_create_variable_expression(JsInterpreter * inter,ExecuteEnvironment *env,Expression* e){
	eval_expression(inter, env, e->u.create_var->expression);
	JsValue* v = pop_stack(&inter->stack);
	INTERPRETE_creaet_variable(inter, env, e->u.create_var->identifier,  v, e->line);
	push_stack(&inter->stack, v);
	return 0;

}






JsValue* get_left_value(ExecuteEnvironment* env,Expression* e){
	Variable* var;
	while(NULL != env){
		if(EXPRESSION_TYPE_IDENTIFIER == e->typ){
			var = search_variable_from_variablelist(env->vars,e->u.identifier);
			if(NULL != var){
				return &var->value;
			}
		}
		env = env->outter;
	}
	return NULL;
}

Variable*
search_variable_from_variablelist(VariableList* list,char* identifier){
	if(NULL == list){
		return NULL;
	}
	while(NULL != list){
		if(0 == strcmp(identifier,list->var.name)){
			return &list->var;
		}
		list = list->next;
	}
	return NULL;
}













