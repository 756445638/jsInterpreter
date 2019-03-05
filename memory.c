#include <stdio.h>
#include "memory.h"

void mem_binary_tree_insert(MemoryBinayTree *head, MemoryBinayTree *node)
{
	MemoryBinayTree *position = head;
	for (;;)
	{
		if (node->pointer < position->pointer)
		{
			if (NULL != position->left)
			{
				position = position->left;
			}
			else
			{
				position->left = node;
				node->parent = position;
				return;
			}
		}
		if (node->pointer > position->pointer)
		{
			if (NULL != position->right)
			{
				position = position->right;
			}
			else
			{
				position->right = node;
				node->parent = position;
				return;
			}
		}
	}
}

MemoryBinayTree *
mem_binary_tree_get_successor(MemoryBinayTree *node)
{
	if (NULL == node->right)
	{
		return NULL;
	}
	while (NULL != node->right)
	{
		node = node->right;
	}
	return node;
}

void mem_binary_tree_delete_tree(MemoryBinayTree *tree)
{
	if (NULL == tree)
	{
		return;
	}
	if (NULL != tree->left)
	{
		mem_binary_tree_delete_tree(tree->left);
	}
	if (NULL != tree->right)
	{
		mem_binary_tree_delete_tree(tree->right);
	}
	free(tree);
}

void mem_binary_tree_delete(MemoryBinayTree *head, char *p)
{
	MemoryBinayTree *position = head;
	char found = 0;
	for (;;)
	{
		if (position->pointer == p)
		{
			found = 1;
			break;
		}
		if (p < position->pointer)
		{
			if (NULL != position->left)
			{
				position = position->left;
			}
			else
			{
				break;
			}
		}
		if (p > position->pointer)
		{
			if (NULL != position->right)
			{
				position = position->right;
			}
			else
			{
				break;
			}
		}
	}
	if (0 == found)
	{
		return;
	}
	/*case leaf node*/
	if (NULL == position->left && NULL == position->right)
	{
		if (position->parent->left == position)
		{
			position->parent->left = NULL;
		}
		if (position->parent->right == position)
		{
			position->parent->right = NULL;
		}
		free(position);
		return;
	}
	/*case left child is not null*/
	if (NULL != position->left && NULL == position->right)
	{
		if (position->parent->left == position)
		{
			position->parent->left = position->left;
		}
		if (position->parent->right == position)
		{
			position->parent->right = position->left;
		}
		position->left->parent = position->parent;
		free(position);
		return;
	}

	/*case right child is not null*/
	if (NULL == position->left && NULL != position->right)
	{
		if (position->parent->left == position)
		{
			position->parent->left = position->right;
		}
		if (position->parent->right == position)
		{
			position->parent->right = position->right;
		}
		position->right->parent = position->parent;
		free(position);
		return;
	}
	/*case left and right child is not null*/
	MemoryBinayTree *successor = mem_binary_tree_get_successor(position->left);
	/*successor is null*/
	if (NULL == successor)
	{
		position->left->right = position->right;
		position->right->parent = position->left;
		position->left->parent = position->parent;
		if (position->parent->left == position)
		{
			position->parent->left = position->left;
		}
		if (position->parent->right == position)
		{
			position->parent->right = position->left;
		}
		free(position);
		return;
	}
	/* case successor is leaf node*/
	if (NULL == successor->left)
	{
		successor->parent->right = NULL;
		successor->parent = position->parent;
		if (position->parent->left == position)
		{
			position->parent->left = successor;
		}
		if (position->parent->right == position)
		{
			position->parent->right = successor;
		}
		successor->left = position->left;
		successor->right = position->right;
		free(position);
		return;
	}
	/*case successor has left child*/
	successor->left->parent = successor->parent;
	successor->parent->right = successor->left;
	successor->parent = position->parent;
	if (position->parent->left == position)
	{
		position->parent->left = successor;
	}
	if (position->parent->right == position)
	{
		position->parent->right = successor;
	}
	successor->left = position->left;
	successor->right = position->right;
	free(position);
}

Memory *MEM_open_storage()
{
	Memory *m = (Memory *)malloc(sizeof(Memory));
	if (NULL == m)
	{
		return NULL;
	}
	int i = 0;
	for (; i < MOD_NUMBER; i++)
	{
		m->table[i] = (MemoryBinayTree *)malloc(sizeof(MemoryBinayTree));
		m->table[i]->parent = NULL;
		m->table[i]->pointer = NULL;
		m->table[i]->left = NULL;
		m->table[i]->right = NULL;
		m->table[i]->line = -9999;
	}
	return m;
}

void MEM_close_storage(Memory *m)
{
	if (m == NULL)
	{
		return;
	}
	int i = 0;
	for (; i < MOD_NUMBER; i++)
	{
		mem_binary_tree_delete_tree(m->table[i]);
	}
	free(m);
}

char *MEM_alloc(Memory *m, int size, int line)
{
	MemoryBinayTree *new = (MemoryBinayTree *)malloc(sizeof(MemoryBinayTree) + size);
	if (NULL == new)
	{
		return NULL;
	}
	new->left = NULL;
	new->right = NULL;
	new->parent = NULL;
	new->line = line;
	new->pointer = (char *)(new + 1);
	unsigned long offset = (unsigned long)new->pointer;
	offset %= MOD_NUMBER;
	mem_binary_tree_insert(m->table[offset], new);
	return new->pointer;
}

void MEM_free(Memory *m, char *p)
{
	if (NULL == p)
	{
		printf("pointer value is NULL,strange!!");
		return;
	}
	unsigned long offset = (unsigned long)p;
	offset %= MOD_NUMBER;
	MemoryBinayTree *head = m->table[offset];
	mem_binary_tree_delete(head, p);
}
