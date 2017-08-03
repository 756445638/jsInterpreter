
#include <string.h>
#include "js_value.h"
#include "js.h"
#include "interprete.h"
#include "stack.h"
#include "heap.h"
#include "js_value.h"
#include "error.h"


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
				ERROR_runtime_error(RUNTIME_ERROR_CONTINUE_RETURN_BREAK_CAN_NOT_BE_IN_THIS_SCOPE,next->statement->line);
		} 
        next = next->next;
    }
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
	eval_expression(inter,env,f->init);
	pop_stack(&inter->stack);
	StamentResult result;
	JsValue* v;
	JSBool istrue;
	StatementList* list;
	for(;;){
		eval_expression(inter,env,f->condition);
		pop_stack(&inter->stack);
		eval_expression(inter,env,f->condition);
		v = pop_stack(&inter->stack);
		istrue = is_js_value_true(v);
		if(JS_BOOL_FALSE == istrue){
			goto end;
		}
		list = f->block->list;
		while(NULL != list){
			result = INTERPRETE_execute_statement(inter,env,list->statement);
			switch(result.typ){
				case STATEMENT_RESULT_TYPE_NORMAL:
					break;
				case STATEMENT_RESULT_TYPE_CONTINUE:
					break;
				case STATEMENT_RESULT_TYPE_RETURN:
					goto end;
				case STATEMENT_RESULT_TYPE_BREAK:
					goto end;
			}
			eval_expression(inter,env,f->afterblock);
			pop_stack(&inter->stack);
			list = list->next;
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



StamentResult INTERPRETE_execute_statement_if(JsInterpreter* inter,ExecuteEnvironment* env,StatementIf* i){
	StamentResult ret;
	ret.typ = STATEMENT_RESULT_TYPE_NORMAL;
	eval_expression(inter,env,i->condition);
	JsValue* v = pop_stack(&inter->stack);
	JSBool istrue = is_js_value_true(v);
	StatementList* list;
	StamentResult result;
	char else_if_matched = 0;
	StatementElsifList* elsifnext;
	if(JS_BOOL_TRUE == istrue){
		list = i->then->list;
		while(NULL != list){
			result = INTERPRETE_execute_statement(inter,env,list->statement);
			switch(result.typ){
				case STATEMENT_RESULT_TYPE_NORMAL:
					break;
				case STATEMENT_RESULT_TYPE_CONTINUE:/*I can`t handle continue*/
					ret.typ = STATEMENT_RESULT_TYPE_CONTINUE;
					goto end;
				case STATEMENT_RESULT_TYPE_RETURN:
					ret.typ = STATEMENT_RESULT_TYPE_RETURN;
					goto end;
				case STATEMENT_RESULT_TYPE_BREAK:
					ret.typ = STATEMENT_RESULT_TYPE_BREAK;
					goto end;
			}
		}


	}else{  /*handle else if*/
		if(NULL != i->elseIfList){
			elsifnext = i->elseIfList;
			while(NULL != elsifnext){
				eval_expression(inter,env,elsifnext->elsif.condition);
				v = pop_stack(&inter->stack);
				istrue = is_js_value_true(v);
				if(JS_BOOL_TRUE == istrue){
					else_if_matched = 1;
					list = elsifnext->elsif.block->list;
					result = INTERPRETE_execute_statement(inter,env,list->statement);
					switch(result.typ){
						case STATEMENT_RESULT_TYPE_NORMAL:
							break;
						case STATEMENT_RESULT_TYPE_CONTINUE:/*I can`t handle continue*/
							ret.typ = STATEMENT_RESULT_TYPE_CONTINUE;
							goto end;
						case STATEMENT_RESULT_TYPE_RETURN:
							ret.typ = STATEMENT_RESULT_TYPE_RETURN;
							goto end;
						case STATEMENT_RESULT_TYPE_BREAK:
							ret.typ = STATEMENT_RESULT_TYPE_BREAK;
							goto end;
					}
				}
				elsifnext = elsifnext->next;
			}
		}

		if(NULL != i->els && 0 == else_if_matched){
			list = i->els->list;
			while(NULL != list){
				result = INTERPRETE_execute_statement(inter,env,list->statement);
				switch(result.typ){
						case STATEMENT_RESULT_TYPE_NORMAL:
							break;
						case STATEMENT_RESULT_TYPE_CONTINUE:/*I can`t handle continue*/
							ret.typ = STATEMENT_RESULT_TYPE_CONTINUE;
							goto end;
						case STATEMENT_RESULT_TYPE_RETURN:
							ret.typ = STATEMENT_RESULT_TYPE_RETURN;
							goto end;
						case STATEMENT_RESULT_TYPE_BREAK:
							ret.typ = STATEMENT_RESULT_TYPE_BREAK;
							goto end;
				}
				list= list->next;
			}
			
		}
	

		
		
	}

	

	


	
	


end:
		return ret;

	
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
		eval_expression(inter,env,w->condition);
		JsValue* v = pop_stack(&inter->stack);
		JSBool is_true = is_js_value_true(v);
		if(JS_BOOL_FALSE == is_true){
				break;
		}
		list = w->block->list;
		while(NULL != list){
			result = INTERPRETE_execute_statement(inter,env,list->statement);
			switch(result.typ){
				case STATEMENT_RESULT_TYPE_NORMAL:
					break;
				case STATEMENT_RESULT_TYPE_CONTINUE:
					continue;
				case STATEMENT_RESULT_TYPE_RETURN:
					ret.typ = STATEMENT_RESULT_TYPE_RETURN;
					goto end;
				case STATEMENT_RESULT_TYPE_BREAK:
					goto end;
			}
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
		while(NULL != t){
			t = t->next;
		}
		t->next = newlist;
	}
	newlist->var.name= (char*)(newlist + 1);
	strncpy(newlist->var.name,name,length);/*copy name*/
	newlist->var.name[length] = 0 ;
	newlist->var.value = *v;
	return &newlist->var;
}


JsValue*
INTERPRETE_creaet_heap(JsInterpreter* inter,int size,int line){
	Heap * h = MEM_alloc(inter->excute_memory,sizeof(Heap) + size,line);
	if(NULL == h){
		return NULL;
	}
	push_heap(inter->heap,h);
	h->value.u.alloc = (char*)(h+1);
	return &h->value;
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




