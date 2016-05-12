#include <malloc_helpers.h>

void	split_block(t_block *b, size_t size)
{
	t_block		*new;
	size_t		align_size;

	// printf("BEFOR SPLIT: b->size = %ld\n", b->size);
	align_size = ALIGN(size);
	new = ((void *)b->data) + align_size;
	new->size = b->size - align_size - BLOCK_SIZE;
	new->next = b->next;
	new->flag = b->flag;
	if ((new->flag & IS_START_HEAP) != 0)
		new->flag ^= IS_START_HEAP;
	new->flag |= IS_FREE;
	b->size = size;
	b->rest = align_size - size;
	b->next = new;
	// printf("%ld\n", BLOCK_SIZE);
	// printf("AFTER SPLIT: b->size = %ld\n", b->size);
	// printf("b = %p b->data = %p new = %p: diff = %ld\n", b, b->data, new, (size_t)new - (size_t)b->data);
	// printf("b = %p and b->next = %p\n", b, b->next);
}
