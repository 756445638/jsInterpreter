
#include "statement.h"
#include "expression.h"
#include "js.h"




StamentResult statement_execute(JsInterpreter * inter,ExecuteEnvironment * env,Statement *s){
		
}

StamentResult statement_execute_if(JsInterpreter * inter,ExecuteEnvironment * env,StatementIf* s){
	eval_expression(inter,env,s->condition);
	s->condition
		
}


















