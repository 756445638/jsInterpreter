
#include <string.h>
#include "js_value.h"
#include "js.h"
#include "interprete.h"
#include "stack.h"
#include "heap.h"

int INTERPRETE_interprete(JsInterpreter* inter){
    if(NULL == inter->statement_list){
        return -1;/*no statement list*/
    }
    Statement* s = inter->statement_list->statement;
    StatementList *next = inter->statement_list;
    int result;
    while(next != inter->statement_list){
        result = INTERPRETE_execute_statement(s);
       	

        next = next->next;
    }
}

StamentResult INTERPRETE_execute_statement(Statement* s){
    if(s->typ == STATEMENT_TYPE_WHILE){
        return INTERPRETE_execute_statement_while(s->u.while_statement);
    }
    return -1 ;/*no such type*/
}

int INTERPRETE_execute_statement_while(StatementWhile* w){
		
}


#in



Variable*  
INTERPRETE_creaet_variable(JsInterpreter* inter,VariableList* list,char* name,JsValue* v,int line){
	if(NULL == list){
		return NULL;
	}
	int length = strlen(name);
	VariableList* newlist =(VariableList* ) MEM_alloc(inter->excute_memory,sizeof(VariableList) + length + 1,line);
	if(NULL == newlist){
		return NULL;
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
	push_heap(&inter->heap,h);
	h->value.u.alloc = (char*)(h+1);
	return &h->obj;
}










