#include <malloc_helpers.h>

t_block	*extend_heap(t_block *last, size_t size, int type_zone)
{
	t_block		*b;

	b = (t_block *)mmap(0, size + BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (b == MAP_FAILED)
		return (0);
	b->size = size;
	b->next = NULL;
	b->flag.all_flags = 0;
	b->flag.free = 1;
	b->flag.start_heap = 1;
	b->flag.type_zone = type_zone;
	if (last)
		last->next = b;
	else
		last = b;
	return (b);
}
