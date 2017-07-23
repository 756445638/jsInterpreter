#ifndef STACK_H
#define STACK_H

#include "js.h"

/*runtime stack*/
typedef struct Stack_tag{
	JsValue vs;
	int sp;/*sp pointer*/
	int alloc; /*total length*/
} Stack;




void push_stack(Stack* s,JsValue *v);

JsValue* pop_stack(Stack* s);





#endif 







