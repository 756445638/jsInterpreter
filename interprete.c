
#include <string.h>
#include "js_value.h"
#include "js.h"

int INTERPRETE_interprete(JsInterpreter* inter){
    if(NULL == inter->statement_list){
        return -1;/*no statement list*/
    }
    Statement* s = inter->statement_list->statement;
    StatementList *next = inter->statement_list;
    int result;
    while(next != inter->statement_list){
        result = INTERPRETE_execute_statement(s);
        if(-1 == result){

        }

        next = next->next;
    }
}

int INTERPRETE_execute_statement(Statement* s){
    if(s->typ == STATEMENT_TYPE_WHILE){
        return INTERPRETE_execute_statement_while(s->u.while_statement);
    }
	


    return -1 ;/*no such type*/
}

int INTERPRETE_execute_statement_while(StatementWhile* w){
	
	
	
}


/*create a global variable*/

Variable*  
INTERPRETE_creaet_global_variable(JsInterpreter* inter,char* name,JsValue* v,int line){
 	int length = strlen(name);
	VariableList* list;
 	if(NULL == inter->vars.var.name && 0 == strlen(inter->vars.var.name)){
		list = &inter->vars;
	}else{
		list = MEM_alloc(inter->excute_memory,sizeof(VariableList),line);
	}
	list.var.name = MEM_alloc(inter->excute_memory,length + 1,line);
	strncpy(list.var.name,name,length);
	list.var.value = *v;
	return &list.var;
}




