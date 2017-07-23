#include "js.h"
#include "js_value.h"
#include "util.h"
#include <stdio.h>
#include "stack.h"


void push_stack(Stack* s,JsValue* v){
	if(s->sp >= s->alloc -1){ //TODO:: alloc more memory
		printf("stack overflow\n");
		_exit(3);
	}
	s->vs[s->sp] = *v;
	s->sp++;
}


JsValue* pop_stack(Stack* s){
	JsValue* v =  &s->vs[s->sp-1];
	s->sp--;
	return v;
}

JsValue* peek_stack(Stack* s,int index){
	JsValue* v =  &s->vs[s->sp-index-1];
	return v;
}














