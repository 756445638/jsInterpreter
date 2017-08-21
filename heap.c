#include "error.h"
#include "heap.h"


void
push_heap(Heap* head,Heap* h){
	if(NULL == head || NULL == h){
		return ;
	} 
	Heap* oldlast = head->prev;
	head->prev = h;
	h->next = head;
	
	oldlast->next = h;
	h->prev = oldlast;
}


void print_heap(Heap* head){
	Heap* next = head->next;
	while(next != head){
		printf("typ:%d line:%d\n",next->typ,next->line);
		next = next->next;
	}
}





void gc_mark_value(JsValue* const v){
	int i ;
	JsKvList * kvlist ;
	JsString* string;
	JsArray* array;
	switch(v->typ){
		case JS_VALUE_TYPE_STRING:
			string = *v->u.string;
			string->mark = 1;
			break;
		case JS_VALUE_TYPE_ARRAY:
			array = *v->u.array;
			array->mark = 1;
			for(i = 0;i<array->length;i++){
				gc_mark_value(array->elements + i);
			}
			break;
		case JS_VALUE_TYPE_OBJECT:
			kvlist = v->u.object->eles;
			v->u.object->mark = 1;
			while(NULL != kvlist){
				gc_mark_value(&kvlist->kv.value);
				kvlist = kvlist->next;
			}
			break;
	}
}

void gc_mark_env(ExecuteEnvironment* env){
	VariableList* list = env->vars;
	while(NULL != list){
			gc_mark_value(&list->var.value);
			list = list->next;
	}
}



void gc_mark(ExecuteEnvironment* env){

	while(NULL != env){
		gc_mark_env(env);
		env = env->outter;
	}
}



void gc_sweep_object(JsInterpreter* inter,JsObject* object){
	JsKvList* list = object->eles;
	JsKvList* next = list;
	while(NULL != list){
		next = list->next;
		MEM_free(inter->excute_memory,list);
		list = next;
	}
}




int gc_sweep_get_mark(const Heap* h,int line){
	switch(h->typ){
		case JS_VALUE_TYPE_STRING:
			return h->u.string->mark;
		case JS_VALUE_TYPE_ARRAY:
			return h->u.array->mark;
		case JS_VALUE_TYPE_OBJECT:
			return h->u.object->mark;
		default:
			ERROR_runtime_error(RUNTIME_ERROR_NORMAL_VALUE_ON_HEAP,"",line);
	}
}


void gc_sweep(JsInterpreter* inter){
	if(NULL == inter->heap){
		return ;
	}
	Heap* head = inter->heap;
	Heap* index = inter->heap->prev;
	Heap* prev;
	Heap* next;
	while(index != head){
		if(1 == gc_sweep_get_mark(index,index->line)){ /*reset mark*/
			switch(index->typ){
				case JS_VALUE_TYPE_STRING:
					index->u.string->mark = 0;
					break;
				case JS_VALUE_TYPE_ARRAY:
					index->u.array->mark = 0;
					break;
				case JS_VALUE_TYPE_OBJECT:
					index->u.object->mark = 0;
					break;
				default:
					ERROR_runtime_error(RUNTIME_ERROR_NORMAL_VALUE_ON_HEAP,"",index->line);
			}
			index = index->prev;
			continue;
		}
		/*let`s sweep*/
		if(JS_VALUE_TYPE_OBJECT == index->typ){
			gc_sweep_object(inter,index->u.object);
		}
		/*remove*/
		prev = index->prev;
		next = index->next;
		prev->next = next;
		next->prev = prev;
		MEM_free(inter->excute_memory,index);
		index = prev;
	}
	
}


















