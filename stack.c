#include "js.h"
#include "util.h"
#include "js.h"
#include <stdio.h>

void push_stack(Stack* s,JsValue* v){
	if(s->sp >= s->alloc -1){ //TODO:: alloc more memory
		printf("stach overflow\n");
		_exit(3);
	}
	s->sp++;
	s->vs[s->sp] = *v;
}


JsValue* pop_stack(Stack* s){
	JsValue* v =  &s->vs[s->sp];
	s->sp--;
	return v;
}

JsValue* peek_stack(Stack* s,int index){
	JsValue* v =  &s->vs[s->sp-index];
	return v;
}














