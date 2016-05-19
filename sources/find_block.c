#include <malloc_helpers.h>

t_block			*find_block(t_block **last, size_t size, int type_zone)
{
	t_block	*b;

	b = g_base[type_zone];
	// printf("finder %p\n", b);
	// printf("b = %p\nb is free: %d\nsize = %ld\nb->size = %ld\n", b, (b->flag & FLAG_FREE) != 0, size, b->size);
	// printf("b->next = %p\n", b->next);
	while (b && (!IS_FREE(b) || size > (b->size + b->rest))) // size+rest: need test
	{
		*last = b;
		b = b->next;
	}
	printf("%s search: %lu all: %lu\n", "Find size + rest =", size + BLOCK_SIZE, b->size + b->rest);
	return (b);
}
