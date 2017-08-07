
#include <string.h>
#include "js_value.h"
#include "js.h"
#include "interprete.h"
#include "stack.h"
#include "heap.h"
#include "js_value.h"
#include "error.h"

JsFunctionBuildin console_log_function_buildin;
JsFunction console_log_function;
JsKvList console_log;
JsObject console_object;
JsValue console;



int INTERPRETE_interprete(JsInterpreter* inter){
    if(NULL == inter->statement_list){
        return -1;/*no statement list*/
    }
	INTERPRETE_add_build_in_function(inter);
    StatementList *next = inter->statement_list;
    StamentResult result;
    while(NULL != next){
        result = INTERPRETE_execute_statement(inter,&inter->env,next->statement);
		switch(result.typ){
			case STATEMENT_RESULT_TYPE_NORMAL:
				break;
			case STATEMENT_RESULT_TYPE_CONTINUE:
			case STATEMENT_RESULT_TYPE_RETURN:
			case STATEMENT_RESULT_TYPE_BREAK:
				ERROR_runtime_error(RUNTIME_ERROR_CONTINUE_RETURN_BREAK_CAN_NOT_BE_IN_THIS_SCOPE,next->statement->line);
		} 
        next = next->next;
    }
}


void INTERPRETE_add_build_in_function(JsInterpreter* inter){
	/*add console object*/
	console_log_function_buildin.args_count = 1;
	console_log_function_buildin.u.func1 = js_print;
	console_log_function.typ = JS_FUNCTION_TYPE_BUILDIN;
	console_log_function.buildin = &console_log_function_buildin;
	console_log.kv.value.typ= JS_VALUE_TYPE_FUNCTION;
	console_log.kv.value.u.func = &console_log_function;
	console_log.kv.key = "log";
	console_object.eles = &console_log;	
	console_object.typ = JS_OBJECT_TYPE_BUILDIN;
	console.typ = JS_VALUE_TYPE_OBJECT;
	console.u.object = &console_object;
	INTERPRETE_creaet_variable(inter,&inter->env,"console",&console,0);

	
}

JsValue* INTERPRETE_search_field_from_object(JsObject* obj,char* key){
	if(NULL == obj || NULL == obj->eles){
		return NULL;
	}
	int length = strlen(key);
	JsKvList* list = obj->eles;
	while(NULL != list){
		if(0 == strncmp(key,list->kv.key,length)){
			return &list->kv.value;
		}
	}
	return NULL;
}










StamentResult INTERPRETE_execute_statement(JsInterpreter* inter,ExecuteEnvironment* env,Statement* s){
	StamentResult ret;
	ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
	if(STATEMENT_TYPE_EXPRESSION == s->typ){
		ret = INTERPRETE_execute_statement_expression(inter,env,s->u.expression_statement);
	}
	if(STATEMENT_TYPE_IF == s->typ){
		ret =  INTERPRETE_execute_statement_if(inter,env,s->u.if_statement);
	}
	if(STATEMENT_TYPE_FOR == s->typ){
		ret = INTERPRETE_execute_statement_for(inter,env,s->u.for_statement);
	}
	if(STATEMENT_TYPE_WHILE == s->typ){
		ret = INTERPRETE_execute_statement_while(inter,env, s->u.while_statement);
	}
	if(STATEMENT_TYPE_CONTINUE == s->typ){
		ret.typ = STATEMENT_RESULT_TYPE_CONTINUE;
	}
	if(STATEMENT_TYPE_RETURN == s->typ){/*push stack from outside*/
		eval_expression( inter, env,s->u.return_expression);
		ret.typ = STATEMENT_RESULT_TYPE_RETURN;
	}
	if(STATEMENT_TYPE_BREAK == s->typ){
		ret.typ = STATEMENT_RESULT_TYPE_BREAK;
	}
	
	return ret;
   
}


StamentResult INTERPRETE_execute_statement_for(JsInterpreter* inter,ExecuteEnvironment* env,StatementFor* f){
	StamentResult ret;
	ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
	if(NULL != f->init){
		eval_expression(inter,env,f->init);
		pop_stack(&inter->stack);
	}
	JsValue* v;
	JSBool istrue;
	StatementList* list;
	for(;;){
		if(NULL != f->condition){
			eval_expression(inter,env,f->condition);
			v = pop_stack(&inter->stack);
			istrue = is_js_value_true(v);
			if(JS_BOOL_TRUE != istrue){
				ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
				goto end;
			}
		}
			
		list = f->block->list;
		while(NULL != list){
			ret = INTERPRETE_execute_statement(inter,env,list->statement);
			switch(ret.typ){
				case STATEMENT_RESULT_TYPE_NORMAL:
					break;
				case STATEMENT_RESULT_TYPE_CONTINUE:
					goto after;
				case STATEMENT_RESULT_TYPE_RETURN:
					goto end;
				case STATEMENT_RESULT_TYPE_BREAK:
					ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
					goto end;
			}
			list = list->next;
		}
after:
		if(NULL != f->afterblock){
			eval_expression(inter,env,f->afterblock);
			pop_stack(&inter->stack);
		}
	}

end:
		return ret;
}


StamentResult INTERPRETE_execute_statement_expression(JsInterpreter* inter,ExecuteEnvironment* env,Expression* e){
	StamentResult ret;
	ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
	eval_expression(inter,env, e);
	pop_stack(&inter->stack);
	return ret;
}


StamentResult INTERPRETE_execute_normal_statement_list(JsInterpreter* inter,ExecuteEnvironment* env,StatementList* list){
	StamentResult ret;
	ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
	if(NULL == list){
		return ret;
	}
	StatementList* next = list;
	while(NULL != next){
		ret = INTERPRETE_execute_statement(inter,env,next->statement);
		switch(ret.typ){
			case STATEMENT_RESULT_TYPE_NORMAL:
				break;
			case STATEMENT_RESULT_TYPE_CONTINUE:
				goto end;
			case STATEMENT_RESULT_TYPE_RETURN:
				goto end;
			case STATEMENT_RESULT_TYPE_BREAK:
				goto end;
		}

		next = next->next;
	}
	
end:
	return ret;
}




StamentResult INTERPRETE_execute_statement_if(JsInterpreter* inter,ExecuteEnvironment* env,StatementIf* i){
	StamentResult ret;
	ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
	eval_expression(inter,env,i->condition);
	JsValue* v = pop_stack(&inter->stack);
	JSBool istrue = is_js_value_true(v);
	StatementList* list;
	if(JS_BOOL_TRUE == istrue){  /*handle true part*/
		ret = INTERPRETE_execute_normal_statement_list(inter,env,i->then->list);
		return ret;
	}
	if(NULL == i->elseIfList && NULL != i->els){ /*handle else part*/
		return INTERPRETE_execute_normal_statement_list(inter,env,i->els->list);
	}
	if(NULL == i->elseIfList){
		return ret;	
	}
	StatementElsifList* elsifnext = i->elseIfList;
	while(NULL != elsifnext){
		eval_expression(inter,env,elsifnext->elsif.condition);
		v = pop_stack(&inter->stack);
		istrue = is_js_value_true(v);
		if(JS_BOOL_TRUE == istrue){
			return INTERPRETE_execute_normal_statement_list(inter,env,elsifnext->elsif.block->list);
		}
		elsifnext = elsifnext->next;
	}
	if(NULL == i->els){
		return ret;
	}

	return INTERPRETE_execute_normal_statement_list(inter,env,i->els->list);
		
}



StamentResult INTERPRETE_execute_statement_while(
	JsInterpreter* inter,
	ExecuteEnvironment* env,
	StatementWhile* w
){
	StamentResult ret;
	ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
	StamentResult result;
	StatementList* list;
	for(;;){
again:
		eval_expression(inter,env,w->condition);
		JsValue* v = pop_stack(&inter->stack);
		JSBool is_true = is_js_value_true(v);
		if(JS_BOOL_TRUE != is_true){
			ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
			goto end;
		}
		list = w->block->list;
		while(NULL != list){
			result = INTERPRETE_execute_statement(inter,env,list->statement);
			switch(result.typ){
				case STATEMENT_RESULT_TYPE_NORMAL:
					break;
				case STATEMENT_RESULT_TYPE_CONTINUE:
					goto again;
				case STATEMENT_RESULT_TYPE_RETURN:
					ret.typ = STATEMENT_RESULT_TYPE_RETURN;
					goto end;
				case STATEMENT_RESULT_TYPE_BREAK:
					ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
					goto end;
			}
			list = list->next;
		}
		
	}
end:
	return ret;
}







Variable*  
INTERPRETE_creaet_variable(
		JsInterpreter* inter,
		ExecuteEnvironment* env,
		char* name,
		JsValue* v,
		int line
){
	int length = strlen(name);
	VariableList* newlist =(VariableList* ) MEM_alloc(inter->excute_memory,sizeof(VariableList) + length + 1,line);
	if(NULL == newlist){
		return NULL;
	}
	newlist->next = NULL;
	if(NULL == env->vars){
		env->vars = newlist;
	}else{
		VariableList* t = env->vars;
		while(NULL != t->next){
			t = t->next;
		}
		t->next = newlist;
	}
	newlist->var.name= (char*)(newlist + 1);
	strncpy(newlist->var.name,name,length);/*copy name*/
	newlist->var.name[length] = 0 ;
	if(NULL != v){
		newlist->var.value = *v;
	}
	return &newlist->var;
}


void INTERPRETE_free_env(JsInterpreter* inter,ExecuteEnvironment* env){
	if (NULL == env){
		return ;
	}
	if(NULL != env->vars){
		VariableList* list = env->vars;
		VariableList* next = env->vars;
		while(NULL != list){
			next = list->next;
			MEM_free(inter->excute_memory, list);
			list = next;
		}
	}
}




JsValue*
INTERPRETE_creaet_heap(JsInterpreter* inter,JS_VALUE_TYPE typ,int size,int line){
	int allocsize = sizeof(Heap);
	switch (typ)
		{
			case JS_VALUE_TYPE_STRING:
				allocsize += sizeof(JsString) + sizeof(char);
				break;
			case JS_VALUE_TYPE_ARRAY:
				allocsize += sizeof(JsArray) + sizeof(JsValue) * size;
				break;
		}
	Heap * h = MEM_alloc(inter->excute_memory,  allocsize,line);
	if(NULL == h){
		return NULL;
	}
	if(NULL == inter->heap){
		inter->heap = h;
	}else{
		push_heap(inter->heap,h);
	}
	switch (typ)
		{
			case JS_VALUE_TYPE_STRING:
				h->value.typ = JS_VALUE_TYPE_STRING;
				h->value.u.string = (JsString*)(h+1);
				h->value.u.string->alloc = size;
				h->value.u.string->length = 0;
				h->value.u.string->s = (char*)(h->value.u.string+1);
				h->value.u.string->s[0] = 0;
				h->value.u.string->mark = 0;
				break;
			case JS_VALUE_TYPE_ARRAY:
				h->value.typ = JS_VALUE_TYPE_ARRAY;
				h->value.u.array = (JsArray*)(h+1);
				h->value.u.array->mark = 0;
				h->value.u.array->length = 0;
				h->value.u.array->alloc = size;
				h->value.u.array->elements = (JsValue*)(h->value.u.array + 1);
				break;
		}
	return &h->value;
}


JsValue* INTERPRETE_concat_string(JsInterpreter* inter,const JsValue* v1,const JsValue* v2,int line){
	if(JS_VALUE_TYPE_STRING != v1->typ || JS_VALUE_TYPE_STRING != v2->typ){
		return v1;
	}
	if( v1->u.string->length == 0 &&  v2->u.string->length == 0){
		return v1;
	}
	if(v1->u.string->length ==0 && v2->u.string->length > 0){
		return v2;
	}
	if(v1->u.string->length >0 && v2->u.string->length == 0){
		return v1;
	}
	JsValue* v;
	int length = v1->u.string->length + v2->u.string->length;
	v = INTERPRETE_creaet_heap(inter, JS_VALUE_TYPE_STRING, length*2 + 1,  line);
	int i =0;
	for(;i<v1->u.string->length;i++){
		v->u.string->s[i] = v1->u.string->s[i];
	}
	i = 0;
	for(;i<v2->u.string->length;i++){
		v->u.string->s[i+v1->u.string->length] = v2->u.string->s[i];
	}
	v->u.string->length = length;
	v->u.string->s[length] = 0;
	return v;
	
}




JsFunction *
INTERPRETE_search_func_from_function_list(JsFucntionList* list,char* function){
	while(NULL != list){
		if(0 == strcmp(list->func.name,function)){
			return &list->func;
		}
		list = list->next;
	}
	return NULL;
}


JsFunction *
INTERPRETE_search_func_from_env(ExecuteEnvironment* env,char* function){
	int length = strlen(function);
	JsFucntionList* list ;
	while(NULL != env){
		list = env->funcs;
		while(NULL != list){
			if(0 == strncmp(list->func.name,function,length)){
				return &list->func;
			}
			list = list->next;
		}
		env = env->outter;
	}
	return NULL;
}




JsValue *
INTERPRETE_search_variable_from_env(ExecuteEnvironment* env,char* variable){
	int length = strlen(variable);
	VariableList* list;
	while(NULL != env){
		list = env->vars;
		while(NULL != list){
			if(0 == strncmp(list->var.name,variable,length)){
				return &list->var.value;
			}
			list = list->next;
		}
		env = env->outter;
	}
	return NULL;
}







JsFunction* INTERPRETE_create_function(JsInterpreter* inter,ExecuteEnvironment* env,const char* func,ParameterList* args,Block* block,int line){
	JsFucntionList* funclist = MEM_alloc(inter->excute_memory, sizeof(JsFucntionList), line);
	if(NULL == funclist){
		return NULL;
	}
	funclist->next = NULL;
	funclist->func.name = func;
	funclist->func.typ = JS_FUNCTION_TYPE_USER,
	funclist->func.parameter_list = args;
	funclist->func.block = block;
	funclist->func.typ = JS_FUNCTION_TYPE_USER;
	if(NULL == env->funcs){
		env->funcs = funclist;
		return &funclist->func;
	}

	JsFucntionList* list = env->funcs;
	while(NULL != list->next){
		list = list->next;
	}
	list->next = funclist;
	return &funclist->func;
}














