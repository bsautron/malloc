#include <malloc_helpers.h>

void 	free(void *ptr)
{
	t_block		*b;
	size_t		align_size;

	if (valid_addr(ptr))
	{
		b = ptr - BLOCK_SIZE;
		align_size = ALIGNPAGE(b->size + BLOCK_SIZE, getpagesize());
		b->flag |= FLAG_FREE;
		if (b->prev && IS_FREE(b->prev))
			b = fusion(b->prev);
		if (IS_START_HEAP(b) && ((b->next && IS_START_HEAP(b->next)) || !b->next))
			munmap(b, align_size);
	}
}
