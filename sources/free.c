#include <malloc_helpers.h>

void 	delete_one(t_block **b)
{
	t_block		*tmp;

	tmp = *b;
	printf("*b = %p\n", *b);
	printf("--- %p\n", tmp->next);
	printf("*b->next = %p\n", tmp->next);
	printf("*b->prev = %p\n", tmp->prev);
	if (tmp)
	{
		if (tmp->prev)
			tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		
	}
	*b = NULL;
}

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
		if (b->next) // the condition with the next is in fusion
			b = fusion(b);
		if (IS_START_HEAP(b) && ((b->next && IS_START_HEAP(b->next)) || !b->next))
		{
			delete_one(&b);
			munmap(b, align_size);
		}
	}
}
