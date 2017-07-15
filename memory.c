#include <stdio.h>
#include "memory.h"


Memory* MEM_open_storage(){
    Memory* m= (Memory*)malloc(sizeof(Memory));
    if(m == NULL){
        return NULL;
    }
    m->pointer = NULL;
    m->line = -1 ;
    m->next = NULL;
    m->prev = NULL;
    return m;
}

void MEM_close_storage(Memory* m){
    if(m == NULL){
        return ;
    }
    Memory* next = m->next;
    Memory* p = next;
    while(next != NULL && next != m){
        p = next->next;
        free(next);
        next = p;
    }
    free(m);
}


void* MEM_alloc(Memory *m,int size,int line){
    Memory* new = (Memory*)malloc(sizeof(Memory) + size);
    if(new == NULL){
        return NULL;
    }
    new->pointer =(void*)(new + 1) ;
    new->line = line;
    m->prev = new;
    new->next = m ;
    Memory* last = m->prev;
    if (last == NULL){
       last = m ;
    }
    last->next = new;
    new->prev = new;
    return new->pointer;
}


void MEM_free(Memory *head,void* p){
    Memory* next = head->next;
    int found = 0 ;
    while(next != head && next != NULL){
        if(next->pointer == p){
            found  = 1;
            break;
        }
        next = next->next;
    }
    if(0 == found){
        return ;
    }
    free(next);
}


void MEM_dump(Memory *head){
    Memory* next = head->next;
    while(next != head && next != NULL){
        printf("memory:%x line:%d\n",next->pointer,next->line);
    }
}
