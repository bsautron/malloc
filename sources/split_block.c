#include <malloc_helpers.h>

void	split_block(t_block *b, size_t size)
{
	t_block		*new;
	size_t		align_size;

	MALLOC_DEBUG("Split block");
	align_size = ALIGN4(size);
	new = ((void *)b->data) + align_size;
	new->size = (b->size + b->rest) - align_size - BLOCK_SIZE;
	new->next = b->next;
	new->prev = b;
	new->flag = b->flag;
	if (IS_START_HEAP(new))
		new->flag ^= FLAG_START_HEAP;
	new->flag |= FLAG_FREE;
	new->ptr = new->data;
	b->size = size;
	b->rest = align_size - size;
	b->next = new;
	if (new->next)
		new->next->prev = new;
}
