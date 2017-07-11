#include <stdio.h>
#include <malloc.h>

#ifndef MEMORY_H
#define MEMORY_H
//it is a liked list,first node is not for use

typedef struct Memory_s {
    void* pointer;
    struct Memory_s* prev;
    struct Memory_s* next;
    
} Memory;

void* memory_alloc(Memory *m,int size);
void memory_free(Memory *head,void* p);
memory_dump(Memory *head);



#endif

