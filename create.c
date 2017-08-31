#include "js.h"
#include "memory.h"
#include "util.h"
#include <string.h>
#include <stdio.h>
#include "interprete.h"


JsInterpreter*
JS_create_interpreter(){
    Memory*  inter_memory = MEM_open_storage();
    if(NULL == inter_memory){
        return NULL;
    }
    JsInterpreter* interpreter =  MEM_alloc(inter_memory,sizeof(JsInterpreter),0);
    if(NULL == interpreter){
        MEM_close_storage(inter_memory);
        return NULL;
    }
    interpreter->excute_memory = MEM_open_storage();
    if(NULL == interpreter->excute_memory){
        MEM_close_storage(inter_memory);
        return NULL;
    }
    interpreter->statement_list = NULL;
	interpreter->heapenv = NULL;
    interpreter->interpreter_memory = inter_memory;
	interpreter->heap = NULL;
	interpreter->env.outter = NULL;
	interpreter->env.vars = NULL;
	interpreter->env.funcs = NULL;
	interpreter->stack.sp = 0 ;
	interpreter->stack.alloc = 1024 * 1024;
	interpreter->stack.vs = MEM_alloc(interpreter->excute_memory, sizeof(JsValue) * interpreter->stack.alloc, 0);
	if(NULL == interpreter->stack.vs){
		MEM_close_storage(inter_memory);
		MEM_close_storage(interpreter->excute_memory);
		return NULL;
	}
    return interpreter;
}

char* CREATE_identifier(char * i){
    int length = strlen(i);
    char* identifier =(char*) MEM_alloc(current_interpreter->interpreter_memory,length + 1,get_line_number());
    if(NULL == identifier){
        return NULL;
    }
    strncpy(identifier,i,length);
    identifier[length] = 0;
    return identifier;
}


Expression* CREATE_alloc_expression(EXPRESSION_TYPE typ){
    Expression* e =(Expression*) MEM_alloc(current_interpreter->interpreter_memory,sizeof(Expression),get_line_number());
    if(NULL == e){
        return NULL;
    }
    e->typ = typ;
	e->line = get_line_number();
    return e;
}



StatementList* CREATE_chain_statement_list(StatementList* list,Statement* s){
	if(NULL == s){
		return list;
	}
    if(NULL == list){
       StatementList* list = MEM_alloc(current_interpreter->interpreter_memory,sizeof(StatementList),get_line_number());
       if(NULL == list){
           return NULL;
       }
       list->next = NULL;
       list->statement = s;
       return list;
    }
    StatementList* new = MEM_alloc(current_interpreter->interpreter_memory,sizeof(StatementList),get_line_number());
    if(NULL == new){
        return list;/*this time faild,but return old list*/
    }
    new->statement = s;
    new->next = NULL;
	StatementList* listp = list;
	while(NULL != listp->next){
		listp = listp->next;
	}
	listp->next = new;
	return list;
}


JsFunction* CREATE_function(char* name,ParameterList* parameterlist,Block* block){
    JsFunction* f = MEM_alloc(current_interpreter->interpreter_memory,sizeof(JsFunction),get_line_number());
    if(NULL == f){
        return NULL;
    }
	f->typ = JS_FUNCTION_TYPE_USER;
    f->block = block;
    f->parameter_list = parameterlist;
    f->name = name;
	f->env = NULL;
    return f;
}



Expression* CREATE_function_expression(char* name,ParameterList* parameterlist,Block* block){
	Expression* new = MEM_alloc(current_interpreter->interpreter_memory, sizeof(Expression) + sizeof(JsFunction), get_line_number());
	new->line = get_line_number();
	new->typ = EXPRESSION_TYPE_CREATE_FUNCTION;
	new->u.func = (JsFunction*)(new + 1);
	new->u.func->name = name;
	new->u.func->parameter_list = parameterlist;
	new->u.func->block = block;
	new->u.func->typ = JS_FUNCTION_TYPE_USER;
	new->u.func->env = NULL;
	return new;
}



ParameterList* CREATE_parameter_list(char* identifier){
    ParameterList* list= MEM_alloc(current_interpreter->interpreter_memory,sizeof(ParameterList),get_line_number());
    if(NULL == list){
        return NULL;
    }
    list->identifier = identifier;
    list->next = NULL;
    return list;
}


ParameterList* CREATE_chain_parameter_list(ParameterList* list,char* identifier){
    if(NULL == list){
        return NULL;
    }
    ParameterList* new= MEM_alloc(current_interpreter->interpreter_memory,sizeof(ParameterList),get_line_number());
    if(NULL == new){
        return list;
    }
    new->next = NULL;
    new->identifier = identifier;
    ParameterList* next = list;
    while(NULL != next->next){
        next = next->next;
    }
    next->next = new;
    return list;
}


StatementList* CREATE_statement_list(Statement* s){
    StatementList* list = MEM_alloc(current_interpreter->interpreter_memory,sizeof(StatementList),get_line_number());
    if(NULL == list){
        return NULL;
    }
    list->statement = s ;
    list->next = NULL;
	s->line = get_line_number();
    return list;
}

Statement*
CREATE_expression_statement(Expression* e){
    Statement* s = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Statement),get_line_number());
    if(NULL == s){
        return NULL;
    }
    s->typ = STATEMENT_TYPE_EXPRESSION;
    s->u.expression_statement = e;
	s->line = get_line_number();
    return s;
}




Statement*
CREATE_break_statement(){
    Statement* s = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Statement),get_line_number());
    if(NULL == s){
        return NULL;
    }
    s->typ = STATEMENT_TYPE_BREAK;
	s->line = get_line_number();
    return s;
}

Statement*
CREATE_if_statement(Expression* condition,Block* then,StatementElsifList* elseiflist,Block* els){
    Statement* s = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Statement) + sizeof(StatementIf),get_line_number());
    if(NULL == s){
        return NULL;
    }
    s->typ = STATEMENT_TYPE_IF;
    s->u.if_statement = (StatementIf*)(s + 1);
    s->u.if_statement->condition = condition;
    s->u.if_statement->then = then;
    s->u.if_statement->elseIfList = elseiflist;
    s->u.if_statement->els = els;
	s->line = get_line_number();
    return s;
}


StatementElsifList*
CREATE_elsif_list(Expression* condition,Block* block){
    StatementElsifList* list =  MEM_alloc(current_interpreter->interpreter_memory,sizeof(StatementElsifList),get_line_number());
    if(NULL == list){
        return NULL;
    }
    list->next = NULL;
    list->elsif.condition = condition;
    list->elsif.block = block;
    return list;
}

StatementElsifList*
CREATE_chain_elsif_list(StatementElsifList* list,StatementElsifList* els){
    if(NULL == list){
        return NULL;
    }
    StatementElsifList* next = list;
    while(NULL != next->next){
        next = next->next;
    }
    next->next = els;
    els->next = NULL; 
    return list;
}

Statement* 
CREATE_while_statement(Expression* condition, Block* block,char isdo){
    Statement* s = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Statement) + sizeof(StatementWhile),get_line_number());
    if(NULL == s){
        return NULL;
    }
    s->typ = STATEMENT_TYPE_WHILE;
    s->u.while_statement = (StatementWhile*) (s + 1);
    s->u.while_statement->condition  = condition;
    s->u.while_statement->block = block;
	s->u.while_statement->isdo = isdo;
	s->line = get_line_number();
    return s;
}


Statement* 
CREATE_for_statement(Expression* init,Expression* condition,Expression* afterblock,Block* block){
    Statement* s = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Statement) + sizeof(StatementFor),get_line_number());
    if(NULL == s){
        return NULL;
    }
    s->typ = STATEMENT_TYPE_FOR;
    s->u.for_statement = (StatementFor*)(s+1);
    s->u.for_statement->init = init;
    s->u.for_statement->condition = condition;
    s->u.for_statement->afterblock = afterblock;
    s->u.for_statement->block = block;
	s->line = get_line_number();
    return s;
}

Statement* 
CREATE_for_in_statement(char* identifier,Expression* target,Block* block){
	Statement* s = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Statement) + sizeof(StatementForIn),get_line_number());
    if(NULL == s){
        return NULL;
    }
	s->typ = STATEMENT_TYPE_FOR_IN;
	s->u.forin_statement = (StatementForIn*)(s+1);
	s->u.forin_statement->identifer = identifier;
	s->u.forin_statement->target = target;
	s->u.forin_statement->block = block;
	s->line = get_line_number();
	return s;
}






Statement*
CREATE_return_statement(Expression* e){
    Statement* s = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Statement),get_line_number());
    if(NULL == s){
        return NULL;
    }
    s->typ = STATEMENT_TYPE_RETURN;
    s->u.return_expression =  e;
	s->line = get_line_number();
    return s;
}

Statement*
CREATE_continue_statement(){
    Statement* s = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Statement),get_line_number());
    if(NULL == s){
        return NULL;
    }
    s->typ = STATEMENT_TYPE_CONTINUE;
	s->line = get_line_number();
    return s;
}

Block*
CREATE_block(StatementList* list){
    Block* b = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Block),get_line_number());
    if(NULL == b){
        return NULL;
    }
    b->list = list;
    return b;
}

ExpressionList*
CREATE_expression_list(Expression* e){
    ExpressionList* list = MEM_alloc(current_interpreter->interpreter_memory,sizeof(ExpressionList),get_line_number());
    if(NULL == list){
        return NULL;
    }
    list->next = NULL;
    list->expression = e ;
    return list;
}

ExpressionList*
CREATE_chain_expression_list(ExpressionList* list,Expression* e){
    if(NULL == list){
        return NULL;
    }
    ExpressionList* new = CREATE_expression_list(e);
    if(NULL == new){
        return list;
    }
    new->next = NULL;
    ExpressionList* next = list ;
    while(NULL != next->next){
        next = next->next;
    }
    next->next = new;
    return list;
}


Expression*
CREATE_assign_expression(Expression* e1,Expression* e2){
    Expression* e= MEM_alloc(current_interpreter->interpreter_memory,sizeof(Expression) + sizeof(ExpressionBinary) , get_line_number()); 
    if(NULL == e){
        return NULL;
    }
    e->typ = EXPRESSION_TYPE_ASSIGN;
    e->u.binary = (ExpressionBinary*)(e + 1);
    e->u.binary->left = e1;
    e->u.binary->right = e2;
	e->line = get_line_number();
    return e;
}


Expression*
CREATE_self_assign_op_expression(EXPRESSION_TYPE typ,Expression* e1,Expression* e2){
    Expression* e= MEM_alloc(current_interpreter->interpreter_memory,sizeof(Expression) + sizeof(ExpressionBinary) , get_line_number()); 
    if(NULL == e){
        return NULL;
    }
    e->typ = typ;
    e->u.binary = (ExpressionBinary*)(e + 1);
    e->u.binary->left = e1;
    e->u.binary->right = e2;
	e->line = get_line_number();
    return e;
}



StatementSwitchCaseList*
CREATE_switch_case(Expression* match,StatementList* list){
	StatementSwitchCaseList* s = MEM_alloc(current_interpreter->interpreter_memory, sizeof(StatementSwitchCaseList), get_line_number());
	s->line = get_line_number();
	s->match = match;
	s->list = list;
	s->next = NULL;
	return s;
}


StatementSwitchCaseList*
CREATE_chain_switch_case(StatementSwitchCaseList* list,StatementSwitchCaseList* e){
	StatementSwitchCaseList* lis = list;
	while(NULL != lis->next){
		lis = lis->next;
	}
	lis->next = e ;
	return list;
}

Statement*
CREATE_switch_statement(Expression* condition,StatementSwitchCaseList* list,StatementList* d){
	Statement* s = MEM_alloc(current_interpreter->interpreter_memory, sizeof(StatementSwitch) + sizeof(Statement), get_line_number());
	s->typ = STATEMENT_TYPE_SWITCH;
	s->u.switch_statement = (StatementSwitch*)(s + 1);
	s->u.switch_statement->condition = condition;
	s->u.switch_statement->list = list;
	s->u.switch_statement->defaultpart = d;
	return s;
}





Expression*
CREATE_assign_function_expression(Expression* dest,char* identifier,JsFunction* func){
	Expression* e= MEM_alloc(current_interpreter->interpreter_memory,sizeof(Expression) + sizeof(ExpressionAssignFunction) , get_line_number()); 
    if(NULL == e){
        return NULL;
    }
	e->typ = EXPRESSION_TYPE_ASSIGN_FUNCTION;
    e->u.assign_function = (ExpressionAssignFunction*)(e + 1);
	e->u.assign_function->identifier = identifier;
    e->u.assign_function->dest = dest;
    e->u.assign_function->func = func;
	e->line = get_line_number();
    return e;
}











Expression* 
CREATE_binary_expression(EXPRESSION_TYPE typ,Expression* left,Expression* right){
    Expression* e= MEM_alloc(current_interpreter->interpreter_memory,sizeof(Expression) + sizeof(ExpressionBinary) , get_line_number()); 
    if(NULL == e){
        return NULL;
    }
    e->typ = typ;
    e->u.binary = (ExpressionBinary*)(e + 1);
    e->u.binary->left = left;
    e->u.binary->right = right;
	e->line = get_line_number();
    return e;
}

Expression* 
CREATE_minus_expression(Expression* e){
    Expression* new= MEM_alloc(current_interpreter->interpreter_memory,sizeof(Expression) , get_line_number()); 
    if(NULL == new){
        return NULL;
    }
    new->typ = EXPRESSION_TYPE_NEGATIVE;
    new->u.unary = e;
	new->line = get_line_number();
    return new;
}

Expression* 
CREATE_not_expression(Expression* e){
	Expression* new= MEM_alloc(current_interpreter->interpreter_memory,sizeof(Expression) , get_line_number()); 
    if(NULL == new){
        return NULL;
    }
    new->typ = EXPRESSION_TYPE_NOT;
    new->u.unary = e;
	new->line = get_line_number();
    return new;
}







Expression* 
CREATE_index_expression(Expression* e,INDEX_TYPE typ,Expression* index,char* identifier){
    Expression* new= MEM_alloc(current_interpreter->interpreter_memory,sizeof(Expression)  + sizeof(ExpressionIndex), get_line_number()); 
    if(NULL == new){
        return NULL;
    }
    new->typ = EXPRESSION_TYPE_INDEX;
    new->u.index = (ExpressionIndex*) (new + 1);
    new->u.index->e = e;
    new->u.index->index = index;
	new->u.index->typ = typ;
	new->u.index->identifier = identifier;
	new->line = get_line_number();
    return new;
}



Expression* 
CREATE_method_call_expression(Expression* e,char* method,ArgumentList* args){
    Expression* new= MEM_alloc(current_interpreter->interpreter_memory,sizeof(Expression) + sizeof(ExpressionMethodCall) , get_line_number()); 
    if(NULL == new){
        return NULL;
    }
    new->typ = EXPRESSION_TYPE_METHOD_CALL;
    new->u.method_call = (ExpressionMethodCall*)(new + 1);
    new->u.method_call->e = e;
    new->u.method_call->method = method;
    new->u.method_call->args= args ;
	new->line = get_line_number();
    return new;
}

Expression* 
CREATE_incdec_expression(Expression* e,EXPRESSION_TYPE typ){
    Expression* new= MEM_alloc(current_interpreter->interpreter_memory,sizeof(Expression) , get_line_number()); 
    if(NULL == new){
        return NULL;
    }
    new->typ = typ;
    new->u.unary = e;
	new->line = get_line_number();
    return new;
}

ExpressionList*
CREATE_argument_list(Expression* e){
    ExpressionList* list= MEM_alloc(current_interpreter->interpreter_memory,sizeof(ExpressionList) , get_line_number()); 
    if(NULL == list){
        return NULL;
    }
    list->next = NULL;
    list->expression = e;
    return list;
}
ExpressionList*
CREATE_chain_argument_list(ExpressionList* list, Expression* e){
    if(NULL == list){
        return NULL;
    }
    ExpressionList* new= MEM_alloc(current_interpreter->interpreter_memory,sizeof(ExpressionList) , get_line_number()); 
    if(NULL == new){
        return list;
    }
    new->next = NULL;
    new->expression = e;
    ExpressionList* next = list;
    while(NULL != next->next){
        next = next->next;
    } 
    next->next = new;
    return list;
}

Expression*
CREATE_function_call_expression(char* funcname,Expression* pre,ArgumentList* args){
    Expression* e = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Expression) + sizeof(ExpressionFunctionCall),get_line_number());
    if(NULL == e){
        return NULL;
    }
	if(NULL == e){
		 e->typ = EXPRESSION_TYPE_FUNCTION_CALL;
	}else{
		e->typ = EXPRESSION_TYPE_EXPRESSION_FUNCTION_CALL;
	}
   
    e->u.function_call = (ExpressionFunctionCall*)(e +1);
    e->u.function_call->func = funcname;
	e->u.function_call->e = pre;
    e->u.function_call->args = args;
	e->line = get_line_number();
    return e;
}







Expression*
CREATE_identifier_expression(char* identifier){ 
    Expression* new = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Expression),get_line_number());
    if(NULL == new){
        return NULL;
    }
    new->typ = EXPRESSION_TYPE_IDENTIFIER;
    new->u.identifier = identifier;
	new->line = get_line_number();
    return new;
}


Expression*
CREATE_localvariable_declare_expression(char* identifier,Expression* assignment){
    Expression* new = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Expression) + sizeof(ExpressionCreateLocalVarialbe),get_line_number());
    if(NULL == new){
        return NULL;
    }
    new->typ = EXPRESSION_TYPE_CREATE_LOCAL_VARIABLE;
    new->u.create_var = (ExpressionCreateLocalVarialbe*)(new+1);
	new->u.create_var->identifier = identifier;
	new->u.create_var->expression = assignment;
	new->line = get_line_number();
    return new;
}





Expression*
CREATE_boolean_expression(JSBool value){
    Expression* new = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Expression),get_line_number());
    if(NULL == new){
        return NULL;
    }
    new->typ = EXPRESSION_TYPE_BOOL;
    new->u.bool_value = value;
	new->line = get_line_number();
    return new;
}

Expression*
CREATE_null_expression(){
    Expression* new = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Expression),get_line_number());
    if(NULL == new){
        return NULL;
    }
    new->typ = EXPRESSION_TYPE_NULL;
	new->line = get_line_number();
    return new;
}

Expression*
CREATE_array_expression(ExpressionList* list){
    Expression* new = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Expression) ,get_line_number());
    if(NULL == new){
        return NULL;
    }
    new->typ = EXPRESSION_TYPE_ARRAY;
    new->line = get_line_number();
    new->u.expression_list = list;
    return new;
}



Expression*
CREATE_object_expression(ExpressionObjectKVList* list){
	Expression* new = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Expression) ,get_line_number());
    if(NULL == new){
        return NULL;
    }
	new->typ = EXPRESSION_TYPE_OBJECT;
	new->line = get_line_number();
	new->u.object_kv_list = list;
	return new;
}




Expression*
CREATE_new_expression(char* identifer,ExpressionList* args){
	Expression* new = MEM_alloc(current_interpreter->interpreter_memory,sizeof(Expression) + sizeof(ExpressionNew) ,get_line_number());
    if(NULL == new){
        return NULL;
    }
	new->typ = EXPRESSION_TYPE_NEW;
	new->u.new = (ExpressionNew*)(new+1);
	new->u.new->identifier = identifer;
	new->u.new->args = args;
	new->line = get_line_number();
	return new;
}




ExpressionObjectKV* CREATE_object_kv(char* identifier_key,Expression* expression_key,Expression* value,JsFunction* func){
	ExpressionObjectKV* new = MEM_alloc(current_interpreter->interpreter_memory,sizeof(ExpressionObjectKV) ,get_line_number());
	new->identifier_key = identifier_key;
	new->expression_key = expression_key;
	new->value = value;
	new->func = func;
	new->line = get_line_number();
	return new;
	
}

ExpressionObjectKVList* CREATE_object_kv_list(ExpressionObjectKV* kv){
	ExpressionObjectKVList* list = MEM_alloc(current_interpreter->interpreter_memory,sizeof(ExpressionObjectKVList) ,get_line_number());
	list->kv = kv;
	list->next = NULL;
	return list;
}


ExpressionObjectKVList* CREATE_chain_object_kv_list(ExpressionObjectKVList* list,ExpressionObjectKV* kv){
	
	ExpressionObjectKVList* newlist = CREATE_object_kv_list(kv);
	if(NULL == list){
		return newlist;
	}

	ExpressionObjectKVList* next = list;
	while(NULL != next->next){
			next = next->next;
	}
	next->next = newlist;
	return list;

}




