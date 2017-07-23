#include "heap.h"



void
push_heap(Heap* head,Heap* h){
	if(NULL == head || NULL == h){
		return ;
	}
	Heap* oldlast = head->prev;
	head->prev = h;
	h->next = head;
	if(NULL == oldlast){
		oldlast = head;
	}	
	oldlast->next = h;
	h->prev = oldlast;
}
















