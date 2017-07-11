#include <stdio.h>
#include "memory.h"


void* memory_alloc(Memory *m,int size){
    Memory* new = (Memory*)malloc(sizeof(Memory));
    if(newm == NULL){
        return NULL;
    }
    void* p = malloc(size);
    if(p == NULL){
        free(new);
        return NULL;
    }
    new.pointer = p ;
    Memory* last = m.prev;
    m.prev = new;
    new.next = m ;
    if last == NULL{
       last = m ;
    }
    last.next = new ;
    new.prev = new;
    return p ;
}


void memory_free(Memory *head,void* p){
    Memory* next = head.next;
    int found = 0 ;
    while(next != head && next != NULL){
        if(next.pointer == p){
            found  = 1;
            break;
        }
    }
    if(0 == found){
        return ;
    }
    free(p);
    free(next);
}


void memory_dump(Memory *head){
    Memory* next = head.next;
    while(next != head && next != NULL){
        printf("memofy@%x\n",next.pointer);
    }
}
