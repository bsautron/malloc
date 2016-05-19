#include <malloc_helpers.h>

void	split_block(t_block *b, size_t size)
{
	t_block		*new;
	size_t		align_size;

	// printf("BEFOR SPLIT: b->size = %ld\n", b->size);
	align_size = ALIGN4(size);
	new = ((void *)b->data) + align_size;
	new->size = (b->size + b->rest) - align_size - BLOCK_SIZE;
	new->next = b->next;
	new->prev = b;
	new->flag = b->flag;
	if (IS_START_HEAP(new))
		new->flag ^= FLAG_START_HEAP;
	new->flag |= FLAG_FREE;
	b->size = size;
	b->rest = align_size - size;
	b->next = new;
	if (new->next)
		new->next->prev = new;
	// printf("%ld\n", BLOCK_SIZE);
	// printf("AFTER SPLIT: b->size = %ld\n", b->size);
	// printf("b = %p b->data = %p new = %p: diff = %ld\n", b, b->data, new, (size_t)new - (size_t)b->data);
	// printf("b = %p and b->next = %p\n", b, b->next);
}
