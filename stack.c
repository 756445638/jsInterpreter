#include "js.h"
#include "js_value.h"
#include "util.h"
#include <stdio.h>
#include "stack.h"


void push_stack(Stack* s,JsValue* v){
	if(s->sp >= s->alloc -1){ /*TODO:: alloc more memory*/
		printf("stack overflow\n");
		_exit(3);
	}
	s->vs[s->sp] = *v;
	s->sp++;
}


JsValue pop_stack(Stack* s){
	s->sp--;
	return  s->vs[s->sp];
}

JsValue* peek_stack(Stack* s,int index){
	JsValue* v =  s->vs + s->sp-index-1;
	return v;
}


/*
int main(){
	Stack s;
	s.alloc = 1024;
	s.sp = 0;
	s.vs =(JsValue*) malloc(100 * sizeof(JsValue));
	int i = 0;
	JsValue v;
	v.typ = JS_VALUE_TYPE_INT;
	for(;i<100;i++){
		v.u.intvalue = i;
		push_stack( &s,  &v);
	}
	i= 0;
	JsValue* vp;
	for(;i<100;i++){
		vp = pop_stack(&s);
		printf("%d\n",vp->u.intvalue);
	}
	s.sp = 50;
	i = 0;
	for(;i<49;i++){
		vp = pop_stack(&s);
		printf("%d\n",vp->u.intvalue);
	}
	
	

}


*/












