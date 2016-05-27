#include <malloc_helpers.h>

t_block			*find_block(t_block **last, size_t size, int type_zone)
{
	t_block	*b;
	size_t	align_size;

	b = g_base[type_zone];
	align_size = ALIGN4(size);
	// printf("finder %p\n", b);
	// printf("b = %p\nb is free: %d\nsize = %ld\nb->size = %ld\n", b, (b->flag & FLAG_FREE) != 0, size, b->size);
	while (b && (!IS_FREE(b) || align_size > b->size + b->rest)) // size+rest: need test
	{
		*last = b;
		b = b->next;
	}
	// printf("%p\n", b);
	// printf("%s search: %lu all: %lu\n", "Find size + rest =", align_size, b->size + b->rest);
	return (b);
}
