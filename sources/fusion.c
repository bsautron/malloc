#include <malloc_helpers.h>

t_block		*fusion(t_block *b)
{
	if (b && b->next && IS_FREE(b->next) && !IS_START_HEAP(b->next))
	{
		MALLOC_DEBUG("Fusion block");
		b->size += b->rest + BLOCK_SIZE + b->next->size;
		b->rest = b->next->rest;
		b->next = b->next->next;
		if (b->next)
			b->next->prev = b;
		return (fusion(b));
	}
	return (b);
}
