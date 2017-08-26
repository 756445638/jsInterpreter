
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
VariableList console_var_list;


JsFunctionList   jstypeof;
JsFunctionBuildin typeof_buildin;

unsigned int create_heap_count = 0;
char gc_sweep_execute = 0;




int INTERPRETE_interprete(JsInterpreter* inter){
    if(NULL == inter->statement_list){
        return -1;/*no statement list*/
    }
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
				ERROR_runtime_error(RUNTIME_ERROR_CONTINUE_RETURN_BREAK_CAN_NOT_BE_IN_THIS_SCOPE,"break",next->statement->line);
		} 
        next = next->next;
    }
	INTERPRETE_free_env(inter,&inter->env);
	inter->env.funcs = NULL;
	inter->env.vars = NULL;
	gc_mark(NULL);
	gc_sweep(inter);
	print_heap(inter->heap);
	return 0;
	
}


void INTERPRETE_add_buildin(JsInterpreter* inter){
	/*add console object*/
	console_log_function_buildin.args_count = 1;
	console_log_function_buildin.u.func1 = js_println;
	console_log_function.typ = JS_FUNCTION_TYPE_BUILDIN;
	console_log_function.buildin = &console_log_function_buildin;
	console_log.kv.value.typ= JS_VALUE_TYPE_FUNCTION;
	console_log.kv.value.u.func = &console_log_function;
	console_log.kv.key = "log";
	console_log.next = NULL;
	console_object.eles = &console_log;	
	console_object.typ = JS_OBJECT_TYPE_BUILDIN;
	console_object.env = NULL;
	console_var_list.next = NULL;
	console_var_list.var.name = "console";
	console_var_list.var.value.typ = JS_VALUE_TYPE_OBJECT;
	console_var_list.var.value.u.object = &console_object;
	inter->env.vars = &console_var_list;
	/*buildin function typeof*/
	jstypeof.func.typ= JS_FUNCTION_TYPE_BUILDIN;
	jstypeof.func.buildin = &typeof_buildin;
	jstypeof.func.name = "typeof";
	jstypeof.next = NULL;
	typeof_buildin.args_count = 1;
	typeof_buildin.u.func1 = js_typeof;

		
	inter->env.funcs = &jstypeof;

		
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



JsValue* INTERPRETE_search_field_from_object(JsObject* obj,const char* key){
	JsKvList* list = obj->eles;
	while(NULL != list){
		if(0 == strcmp(key,list->kv.key)){
			return &list->kv.value;
		}
		list = list->next;
	}
	return NULL;
}

JsValue* INTERPRETE_search_field_from_object_include_prototype(JsObject* obj,const char* key){
	JsValue* prototype ;
	JsKvList* list ; 
	while(NULL != obj){
		prototype = NULL;
		list = obj->eles;
		while(NULL != list){
		if(0 == strcmp(list->kv.key,"prototype")){
			prototype = &list->kv.value;
		}
		if(0 == strcmp(key,list->kv.key)){
			return &list->kv.value;
		}
		list = list->next;
		}
		if(NULL != prototype && JS_VALUE_TYPE_OBJECT == prototype->typ){
			obj = prototype->u.object;
		}else{
			obj = NULL;
		}
	}
	
	return NULL;
}



JsValue* INTERPRETE_create_object_field(JsInterpreter* inter,JsObject* obj,const char* key,JsValue* value,int line){
	JsValue* v = INTERPRETE_search_field_from_object(obj,key);
	if(NULL != v){
		if(NULL != value){
			*v = *value;
		}
		return v;
	}
	int length = strlen(key);
	JsKvList* list =(JsKvList*) MEM_alloc(inter->excute_memory,sizeof(JsKvList) + length + 1,line);
	if(NULL == list){
		return NULL;
	}
	list->next = NULL;
	list->kv.key = (char*)(list+1);
	strncpy(list->kv.key,key,length);
	list->kv.key[length] = 0;

	if(NULL == obj->eles){
		obj->eles = list;
	}else{
		list->next = obj->eles;
		obj->eles = list;
	}
	if(NULL != value){
		list->kv.value = *value;
	}
	return &list->kv.value;
	
}








StamentResult INTERPRETE_execute_statement_for_in(
	JsInterpreter* inter,
	ExecuteEnvironment* env,
	StatementForIn* in,
	int line
){

	ExecuteEnvironment *forinenv = (ExecuteEnvironment*)INTERPRETE_alloc_env(inter,env,line);
	StamentResult ret;
	ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
	eval_expression(inter,env,in->target);
	JsValue target = pop_stack(&inter->stack);
	if(JS_VALUE_TYPE_ARRAY != target.typ && JS_VALUE_TYPE_OBJECT != target.typ){
		INTERPRETE_free_env(inter, forinenv);
		return ret; /*can for in this type,just return nothing to do*/
	}
	Variable* var;
	/*handle array part*/
	if(JS_VALUE_TYPE_ARRAY == target.typ){
		JsArray* array= target.u.array->u.array;
		int length = array->length;
		int i = 0;
		for(;i<length;i++){
			if(0 == i){
				var = INTERPRETE_creaet_variable(inter,forinenv,in->identifer,NULL,-1);
				var->value.typ = JS_VALUE_TYPE_INT;
				var->value.u.intvalue = 0;
			}else{
				var->value.u.intvalue = i;
			}
			ret = INTERPRETE_execute_normal_statement_list(inter,forinenv,in->block->list);
			switch(ret.typ){
				case STATEMENT_RESULT_TYPE_NORMAL:
					break;
				case STATEMENT_RESULT_TYPE_CONTINUE:
					break;
				case STATEMENT_RESULT_TYPE_RETURN:
					goto end;
				case STATEMENT_RESULT_TYPE_BREAK:
					ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
					goto end;
			}
		}
	}

	if(JS_VALUE_TYPE_OBJECT == target.typ){
		JsKvList* list = target.u.object->eles;
		if(NULL == list){
			goto end;
		}
		var = INTERPRETE_creaet_variable(inter,forinenv,in->identifer,NULL,-1);
		var->value.typ = JS_VALUE_TYPE_STRING_LITERAL;
		while(NULL != list){
			var->value.u.literal_string = list->kv.key;
			ret = INTERPRETE_execute_normal_statement_list(inter,forinenv,in->block->list);
			switch(ret.typ){
				case STATEMENT_RESULT_TYPE_NORMAL:
					break;
				case STATEMENT_RESULT_TYPE_CONTINUE:
					break;
				case STATEMENT_RESULT_TYPE_RETURN:
					goto end;
				case STATEMENT_RESULT_TYPE_BREAK:
					ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
					goto end;
			}
			list = list->next;
		}
	}
	
	

	
 
end:
	if(STATEMENT_RESULT_TYPE_RETURN != ret.typ){
		ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
	}
	INTERPRETE_check_return_value_free_env_or_push_in_envheap(inter, forinenv,&ret);
	return ret;
	
}


StamentResult
INTERPRETE_execute_statement_switch(JsInterpreter* inter,ExecuteEnvironment* env,StatementSwitch* s){
	StamentResult ret;
	ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
	eval_expression( inter,  env, s->condition);
	JsValue value = pop_stack(&inter->stack);
	ExecuteEnvironment* senv =  (ExecuteEnvironment*)INTERPRETE_alloc_env(inter, env, s->condition->line);
	StatementSwitchCaseList* list = s->list;
	JsValue match;
	JSBool istrue;
	char casematched = 0;
	while(NULL != list){
		eval_expression(inter, senv, list->match);
		match = pop_stack(&inter->stack);
		istrue = js_value_equal(&value, &match);
		if(JS_BOOL_TRUE == istrue){
			casematched = 1;
			break;
		}
		list = list->next;
	}
	if(1 == casematched){
		while(NULL != list){
		ret = INTERPRETE_execute_normal_statement_list(inter, senv, list->list);
			switch (ret.typ)
				{
					case STATEMENT_RESULT_TYPE_NORMAL:
						break;
					case STATEMENT_RESULT_TYPE_CONTINUE:
						goto end;
					case STATEMENT_RESULT_TYPE_RETURN:
						goto end;
					case STATEMENT_RESULT_TYPE_BREAK:
						ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
						goto end;
				}
			list = list->next;
		}
	}else{ /*default part*/
		if(NULL == s->defaultpart){
			goto end;
		}
		ret = INTERPRETE_execute_normal_statement_list(inter, senv, s->defaultpart);
			switch (ret.typ)
				{
					case STATEMENT_RESULT_TYPE_NORMAL:
						break;
					case STATEMENT_RESULT_TYPE_CONTINUE:
						goto end;
					case STATEMENT_RESULT_TYPE_RETURN:
						goto end;
					case STATEMENT_RESULT_TYPE_BREAK:
						ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
						goto end;
				}
	}
	


	

	

end:
	INTERPRETE_check_return_value_free_env_or_push_in_envheap(inter, senv,&ret);
	return ret;
}


void INTERPRETE_mark_js_value_env(JsValue* v,ExecuteEnvironment* env){
	int i = 0;
	switch(v->typ){
				case JS_VALUE_TYPE_FUNCTION:
					v->u.func->env = NULL;
					break;
				case JS_VALUE_TYPE_OBJECT:
					v->u.object->env = NULL;
					break;
				case JS_VALUE_TYPE_ARRAY:
					for(;i<v->u.array->u.array->length;i++){
						INTERPRETE_mark_js_value_env(v->u.array->u.array->elements + i,env);
					}
					break;
		}
}



StamentResult INTERPRETE_execute_statement(JsInterpreter* inter,ExecuteEnvironment* env,Statement* s){
	StamentResult ret;
	ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
	if(NULL == s){

		return ret;
	}
	if(STATEMENT_TYPE_EXPRESSION == s->typ){
		ret = INTERPRETE_execute_statement_expression(inter,env,s->u.expression_statement);
	}
	if(STATEMENT_TYPE_IF == s->typ){
		ret =  INTERPRETE_execute_statement_if(inter,env,s->u.if_statement,s->line);
	}
	if(STATEMENT_TYPE_FOR == s->typ){
		ret = INTERPRETE_execute_statement_for(inter,env,s->u.for_statement,s->line);
	}
	if(STATEMENT_TYPE_FOR_IN == s->typ){
		ret = INTERPRETE_execute_statement_for_in(inter,env,s->u.forin_statement,s->line);
	}	
	if(STATEMENT_TYPE_WHILE == s->typ){
		ret = INTERPRETE_execute_statement_while(inter,env, s->u.while_statement,s->line);
	}
	if(STATEMENT_TYPE_CONTINUE == s->typ){
		ret.typ = STATEMENT_RESULT_TYPE_CONTINUE;
	}
	if(STATEMENT_TYPE_RETURN == s->typ){/*push stack from outside*/
		if(NULL == s->u.return_expression){
			JsValue v;
			v.typ = JS_VALUE_TYPE_NULL;
			push_stack(&inter->stack,&v);
		}else{
			eval_expression( inter, env,s->u.return_expression);
			JsValue v = peek_stack(&inter->stack,0);
			INTERPRETE_mark_js_value_env(&v,NULL);
		}
		ret.typ = STATEMENT_RESULT_TYPE_RETURN;
	}
	if(STATEMENT_TYPE_BREAK == s->typ){
		ret.typ = STATEMENT_RESULT_TYPE_BREAK;
	}

	if(STATEMENT_TYPE_SWITCH == s->typ){
		ret = INTERPRETE_execute_statement_switch(inter,env,s->u.switch_statement);
	}
	
	return ret;
   
}


StamentResult INTERPRETE_execute_statement_for(
	JsInterpreter* inter,
	ExecuteEnvironment* env,
	StatementFor* f,
	int line
	)
	{
	ExecuteEnvironment* forenv = (ExecuteEnvironment*)INTERPRETE_alloc_env(inter,env,line);
	StamentResult ret;
	ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
	if(NULL != f->init){
		eval_expression(inter,forenv,f->init);
		pop_stack(&inter->stack);
	}
	JsValue v;
	JSBool istrue;
	StatementList* list;
	for(;;){
		if(NULL != f->condition){
			eval_expression(inter,forenv,f->condition);
			v = pop_stack(&inter->stack);
			istrue = is_js_value_true(&v);
			if(JS_BOOL_TRUE != istrue){
				ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
				goto end;
			}
		}
			
		list = f->block->list;
		while(NULL != list){
			ret = INTERPRETE_execute_statement(inter,forenv,list->statement);
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
			eval_expression(inter,forenv,f->afterblock);
			pop_stack(&inter->stack);
		}
	}

end:
		if(STATEMENT_RESULT_TYPE_RETURN != ret.typ){
			ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
		}
		INTERPRETE_check_return_value_free_env_or_push_in_envheap(inter,forenv,&ret);
		return ret;
}


StamentResult INTERPRETE_execute_statement_expression(JsInterpreter* inter,ExecuteEnvironment* env,Expression* e){
	StamentResult ret;
	ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
	eval_expression(inter,env, e);
	pop_stack(&inter->stack);
	return ret;
}

StamentResult INTERPRETE_execute_statement_if(
	JsInterpreter* inter,
	ExecuteEnvironment* env,
	StatementIf* i,
	int line
	)
{
	
	StamentResult ret;
	ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
	ExecuteEnvironment* conditionenv = INTERPRETE_alloc_env(inter,env,line);
	eval_expression(inter,conditionenv,i->condition);
	JsValue v = pop_stack(&inter->stack);
	JSBool istrue = is_js_value_true(&v);
	StatementList* list;
	if(JS_BOOL_TRUE == istrue){  /*handle true part*/
		ret = INTERPRETE_execute_normal_statement_list(inter,conditionenv,i->then->list);
		INTERPRETE_check_return_value_free_env_or_push_in_envheap(inter, conditionenv,&ret);
		return ret;
	}
	
	if(NULL == i->elseIfList && NULL != i->els){ /*handle else part*/
		ExecuteEnvironment* ifenv = (ExecuteEnvironment*)INTERPRETE_alloc_env(inter,env,line);
		ret =  INTERPRETE_execute_normal_statement_list(inter,ifenv,i->els->list);
		INTERPRETE_check_return_value_free_env_or_push_in_envheap(inter, ifenv,&ret);
		return ret;
	}
	if(NULL == i->elseIfList){
		return ret;	
	}
	StatementElsifList* elsifnext = i->elseIfList;
	while(NULL != elsifnext){
		eval_expression(inter,env,elsifnext->elsif.condition);
		v = pop_stack(&inter->stack);
		istrue = is_js_value_true(&v);
		if(JS_BOOL_TRUE == istrue){
			ExecuteEnvironment* ifenv = (ExecuteEnvironment*)INTERPRETE_alloc_env(inter,env,line);
			ret = INTERPRETE_execute_normal_statement_list(inter,ifenv,elsifnext->elsif.block->list);
			INTERPRETE_check_return_value_free_env_or_push_in_envheap(inter, ifenv,&ret);
			return ret;
		}
		elsifnext = elsifnext->next;
	}

	ExecuteEnvironment* ifenv = (ExecuteEnvironment*)INTERPRETE_alloc_env(inter,env,line);
	ret =  INTERPRETE_execute_normal_statement_list(inter,ifenv,i->els->list);
	INTERPRETE_check_return_value_free_env_or_push_in_envheap(inter, ifenv,&ret);
	return ret;
		
}



StamentResult INTERPRETE_execute_statement_while(
	JsInterpreter* inter,
	ExecuteEnvironment* env,
	StatementWhile* w,
	int line
){
	ExecuteEnvironment* whileenv = (ExecuteEnvironment*)INTERPRETE_alloc_env(inter,env,line);
	StamentResult ret;
	ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
	StatementList* list;
	char isdo_done;
	if(0 == w->isdo){
		isdo_done = 1;
	}else{
		isdo_done = 0;
	}
	for(;;){
again:
		if(0 == isdo_done){
			isdo_done = 1;
		}else{
			eval_expression(inter,whileenv,w->condition);
			JsValue v = pop_stack(&inter->stack);
			JSBool is_true = is_js_value_true(&v);
			if(JS_BOOL_TRUE != is_true){
				ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
				goto end;
			}
		}
		list = w->block->list;
		while(NULL != list){
			ret = INTERPRETE_execute_statement(inter,whileenv,list->statement);
			switch(ret.typ){
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
	if(STATEMENT_RESULT_TYPE_RETURN != ret.typ){
		ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
	}
	INTERPRETE_check_return_value_free_env_or_push_in_envheap(inter,whileenv,&ret);
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
		newlist->next = env->vars;
		env->vars = newlist;
	}
	newlist->var.name = (char*)(newlist + 1);
	strncpy(newlist->var.name,name,length);
	newlist->var.name[length] = 0;
	if(NULL != v){
		newlist->var.value = *v;
	}else{
		newlist->var.value.typ = JS_VALUE_TYPE_NULL;
	}
	return &newlist->var;
}


ExecuteEnvironment*
INTERPRETE_alloc_env(JsInterpreter* inter,ExecuteEnvironment* outter,int line){
	ExecuteEnvironment* env = (ExecuteEnvironment*)MEM_alloc(inter->excute_memory,sizeof(ExecuteEnvironment),line);
	if(NULL == env){
		ERROR_runtime_error(RUNTIME_ERROR_CANNOT_ALLOC_MEMORY,"alloc",line);
		return NULL;
	}
	env->funcs = NULL;
	env->outter = outter;
	env->vars = NULL;
	env->next = NULL;
	env->mark = 0 ;
	return env;
}


void INTERPRETE_free_env(JsInterpreter* inter,ExecuteEnvironment* env){
	if (NULL == env){
		return ;
	}
	{/*free vars*/
		VariableList* list = env->vars;
		VariableList* next = env->vars;
		while(NULL != list){
			next = list->next;
			MEM_free(inter->excute_memory, list);
			list = next;
		}
	}
	
	{/*free function*/
		JsFunctionList * list = env->funcs;
		JsFunctionList * next = env->funcs;
		while(NULL != list){
			next = list->next;
			MEM_free(inter->excute_memory, list);
			list = next;
		}
	
	}
	MEM_free(inter->excute_memory,env);
	
}


Heap*
INTERPRETE_creaet_heap(JsInterpreter* inter,JS_VALUE_TYPE typ,int size,int line){
	
	Heap * h = MEM_alloc(inter->excute_memory,  sizeof(Heap),line);
	if(NULL == h){
		ERROR_runtime_error(RUNTIME_ERROR_CANNOT_ALLOC_MEMORY,"", line);
		return ;
	}
	int allocsize = 0;
	switch(typ){
		case JS_VALUE_TYPE_STRING:
			allocsize = sizeof(JsString) + sizeof(char) * size;
			break;
		case JS_VALUE_TYPE_ARRAY:
			allocsize = sizeof(JsArray) + sizeof(JsValue) * size;
			break;
		case JS_VALUE_TYPE_OBJECT:
			allocsize = sizeof(JsObject);
			break;
	}
	char* p = MEM_alloc(inter->excute_memory,allocsize,line);
	if(NULL == p){
		ERROR_runtime_error(RUNTIME_ERROR_CANNOT_ALLOC_MEMORY,"", line);
		return ;
	}
	h->prev = NULL;
	h->next = NULL;
	h->line = line;
	if(NULL == inter->heap){
		inter->heap = MEM_alloc(inter->excute_memory,sizeof(Heap),line);
		inter->heap->prev = inter->heap;
		inter->heap->next = inter->heap;
		inter->heap->line = -1;
	}
	h->typ = typ;
	switch (typ)
		{
			case JS_VALUE_TYPE_STRING:
				h->u.string = (JsString*)p;
				h->u.string->alloc = size;
				h->u.string->length = 0;
				h->u.string->s = (char*)(h->u.string+1);
				h->u.string->s[0] = 0;
				h->u.string->mark = 0;
				h->u.string->line = line;
				break;
			
			case JS_VALUE_TYPE_OBJECT:
				h->u.object = (JsObject*)p;
				h->u.object->mark = 0;
				h->u.object->eles = NULL;
				h->u.object->line = line;
				h->u.object->env = NULL;
				break;
			case JS_VALUE_TYPE_ARRAY:
				h->u.array = (JsArray*)p;
				h->u.array->mark = 0;
				h->u.array->length = 0;
				h->u.array->alloc = size;
				h->u.array->line = line;
				h->u.array->elements = (JsValue*)(h->u.array + 1);
				break;
		}
	push_heap(inter->heap,h);
	create_heap_count;
	create_heap_count++;
	if(0 == (create_heap_count % GC_SWEEP_TIMING)){
		gc_sweep_execute = 1;	
	}
	return h;
}










/* must be string or string_literal*/
JsValue INTERPRETE_concat_string(JsInterpreter* inter,const JsValue* v1,const JsValue* v2,int line){
	char* first;
	int first_length;
	char* second;
	int second_lenth;
	JsString* string;
	if(JS_VALUE_TYPE_STRING == v1->typ){
		string = v1->u.string->u.string;
		first = string->s;
		first_length = string->length;
	}else{/*string literal*/
		first = v1->u.literal_string;
		first_length = strlen(v1->u.literal_string);
	}
	if(JS_VALUE_TYPE_STRING == v2->typ){
			string = v2->u.string->u.string;
			second= string->s;
			second_lenth = string->length;
	}else{/*string literal*/
		second = v2->u.literal_string;
		second_lenth = strlen(v2->u.literal_string);
	}
	int length = first_length + second_lenth;
	JsValue v ;
	v.typ = JS_VALUE_TYPE_STRING;
	Heap* h = INTERPRETE_creaet_heap(inter, JS_VALUE_TYPE_STRING, length + 1,  line);
	string = h->u.string;
	v.u.string = h;
	strncpy(string->s,first,first_length);
	strncpy(string->s + first_length,second,second_lenth);
	string->s[length] = 0;
	string->length = length;
	return v;
}




JsFunction *
INTERPRETE_search_func_from_function_list(JsFunctionList* list,char* function){
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
	JsFunctionList* funclist;
	VariableList* variablelist;
	while(NULL != env){
		funclist = env->funcs;
		while(NULL != funclist){
			if(0 == strcmp(funclist->func.name,function)){
				return &funclist->func;
			}
			funclist = funclist->next;
		}
		variablelist = env->vars;
		while(NULL != variablelist){
			if(0 == strcmp(variablelist->var.name,function) && JS_VALUE_TYPE_FUNCTION== variablelist->var.value.typ){
				return variablelist->var.value.u.func;
			}
			variablelist = variablelist->next;
		}
		env = env->outter;
	}
	return NULL;
}




JsValue *
INTERPRETE_search_variable_from_env(ExecuteEnvironment* env,char* variable){
	VariableList* list;
	JsFunctionList* funclist;
	while(NULL != env){
		list = env->vars;
		while(NULL != list){
			if(0 == strcmp(list->var.name,variable)){
				return &list->var.value;
			}
			list = list->next;
		}
		env = env->outter;
	}
	return NULL;
}







JsFunction* INTERPRETE_create_function(JsInterpreter* inter,ExecuteEnvironment* env,JsFunction* func,int line){
	JsFunctionList* funclist = MEM_alloc(inter->excute_memory, sizeof(JsFunctionList), line);
	if(NULL == funclist){
		return NULL;
	}
	funclist->next = NULL;
	funclist->func = *func;
	if(NULL == env->funcs){
		env->funcs = funclist;
	}else{
		funclist->next = env->funcs;
		env->funcs = funclist;
	}
	return &funclist->func;
}






void INTERPRETE_check_return_value_free_env_or_push_in_envheap(
	JsInterpreter* inter,
	ExecuteEnvironment* env,
	StamentResult* ret
){
	if( STATEMENT_RESULT_TYPE_RETURN != ret->typ){
		INTERPRETE_free_env( inter, env);
		return ;
	}
	JsValue value = peek_stack(&inter->stack,0);
	char is_object_embed_array = 0;
	if(JS_VALUE_TYPE_ARRAY == value.typ){
		int i = 0;
		for(;i<value.u.array->u.array->length;i++){
			if(JS_VALUE_TYPE_OBJECT == value.u.array->u.array->elements[i].typ){
				is_object_embed_array = 1;
				if(NULL  == value.u.array->u.array->elements[i].u.object->env){
					value.u.array->u.array->elements[i].u.object->env = env;
				}
			}
		}
	}
	if(
		is_object_embed_array == 0 /*no object in a array*/
		&& JS_VALUE_TYPE_FUNCTION != value.typ
		&& JS_VALUE_TYPE_OBJECT != value.typ
	)
	{
		INTERPRETE_free_env( inter, env);
		return ;
	}
	switch(value.typ){
		case JS_VALUE_TYPE_FUNCTION:
			if(NULL == value.u.func->env){
				value.u.func->env = env;
			}
			break;
		case JS_VALUE_TYPE_OBJECT:
			if(NULL == value.u.object->env){
				value.u.object->env = env;
			}
			break;
	}
	/*put env in heap*/
	if(NULL == inter->heapenv){
		inter->heapenv = env;
	}else{
		env->next = inter->heapenv;
		inter->heapenv = env;
	}
}



ExecuteEnvironment*
get_last_not_null_outter_env(ExecuteEnvironment* env){
	while(NULL != env){
		if(NULL == env->outter){
			return env;
		}else{
			env = env->outter;
		}
	}
	return NULL;
}




