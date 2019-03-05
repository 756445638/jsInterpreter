#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <malloc.h>

#define MOD_NUMBER (13337)

typedef struct MemoryBinaryTree_s
{
	struct MemoryBinaryTree_s *parent;
	struct MemoryBinaryTree_s *left;
	struct MemoryBinaryTree_s *right;
	char *pointer;
	int line;
} MemoryBinaryTree;

typedef struct Memory_s
{
	MemoryBinaryTree *table[MOD_NUMBER];
} Memory;

char *MEM_alloc(Memory *m, int size, int line);
void MEM_free(Memory *head, char *p);
void MEM_dump(Memory *head);
Memory *MEM_open_storage();
void MEM_close_storage(Memory *m);


#endif
