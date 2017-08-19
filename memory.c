#include <stdio.h>
#include "memory.h"


Memory* MEM_open_storage(){
    Memory* m= (Memory*)malloc(sizeof(Memory));
    if(NULL == m){
        return NULL;
    }
    m->pointer = NULL;
    m->line = -1 ;
    m->next = m;
    m->prev = m;
    return m;
}

void MEM_close_storage(Memory* m){
    if(m == NULL){
        return ;
    }
    Memory* next = m->next;
    Memory* p = next;
    while(next != m){
        p = next->next;
        free(next);
        next = p;
    }
    free(m);
}


char* MEM_alloc(Memory *m,int size,int line){
    Memory* new = (Memory*)malloc(sizeof(Memory) + size);
    if(NULL == new){
        return NULL;
    }
    Memory* last = m->prev;
    new->pointer =(char*)(new + 1) ;
    new->line = line;
    m->prev = new;
    new->next = m ;
    last->next = new;
    new->prev = last;
    return new->pointer;
}


void MEM_free(Memory *head,char* p){
	Memory * next = head->next;
	while(next != head){
		if(next->pointer == p){ /*found*/
			next->prev->next = next->next;
			next->next->prev = next->prev;
			free(next);
			return ;
		}
		next = next->next;
	}
}


void MEM_dump(Memory *head){
    Memory* next = head->next;
    while(next != head && next != NULL){
        printf("memory:%p line:%d\n",next->pointer,next->line);
    }
}
