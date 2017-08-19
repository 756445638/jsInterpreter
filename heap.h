#ifndef HEAP_H
#define HEAP_H
#include "js.h"


void
push_heap(Heap* head,Heap* h);

void gc_mark(ExecuteEnvironment* env);
void gc_sweep(JsInterpreter* inter);






#endif



