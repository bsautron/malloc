#include <malloc_helpers.h>

static void 	delete_one(t_block **b)
{
	t_block		*tmp;

	tmp = *b;
	if (tmp)
	{
		if (tmp->prev)
			tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		if (!tmp->prev)
			g_base[tmp->flag & 111] = tmp->next;
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
		if (b->next)
			b = fusion(b);
		if (IS_START_HEAP(b) && ((b->next && IS_START_HEAP(b->next)) || !b->next))
		{
			if (!IS_FIRST_EXTEND(b))
			{
				delete_one(&b);
				munmap(b, align_size);
			}
		}
	}
}
