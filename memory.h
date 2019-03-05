#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <malloc.h>

#define MOD_NUMBER (13337)

typedef struct MemoryBinayTree_s
{
	struct MemoryBinayTree_s *parent;
	struct MemoryBinayTree_s *left;
	struct MemoryBinayTree_s *right;
	char *pointer;
	int line;
} MemoryBinayTree;

typedef struct Memory_s
{
	MemoryBinayTree *table[MOD_NUMBER];
} Memory;

char *MEM_alloc(Memory *m, int size, int line);
void MEM_free(Memory *head, char *p);
void MEM_dump(Memory *head);
Memory *MEM_open_storage();
void MEM_close_storage(Memory *m);

#endif
