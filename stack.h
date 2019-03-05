#ifndef STACK_H
#define STACK_H

#include "js.h"

void push_stack(Stack *s, const JsValue *v);

JsValue pop_stack(Stack *s);

JsValue peek_stack(Stack *s, int index);

#endif
