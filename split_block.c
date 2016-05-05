#include <malloc_helpers.h>

void	split_block(t_block *b, size_t size)
{
	t_block		*new;

	new = b->data + size;
	new->size = b->size - size - BLOCK_SIZE;
	new->next = b->next;
	b->size = size;
	b->next = new;
}
