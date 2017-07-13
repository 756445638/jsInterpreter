#include <stdio.h>
#include <malloc.h>

#ifndef MEMORY_H
#define MEMORY_H

/*it is a linked list,first node is not for use*/
typedef struct Memory_s {
    void* pointer;
    int line;
    struct Memory_s* prev;
    struct Memory_s* next;
    
} Memory;


void* MEM_alloc(Memory *m,int size,int line);
void MEM_free(Memory *head,void* p);
void MEM_dump(Memory *head);
Memory* MEM_open_storage();
void MEM_close_storage(Memory* m);


#endif

