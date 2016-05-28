#include <malloc_helpers.h>

t_block	*extend_heap(t_block **last, size_t size, int type_zone)
{
	t_block		*b;
	size_t		align_size;

	align_size = ALIGNPAGE(size + BLOCK_SIZE, getpagesize());
	b = (t_block *)mmap(NULL, align_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (b == MAP_FAILED)
		return (NULL);
	b->size = size;
	b->rest = align_size - size - BLOCK_SIZE;
	b->next = NULL;
	b->prev = *last;
	b->flag = FLAG_FREE | FLAG_START_HEAP | type_zone;
	b->ptr = b->data;
	if (*last)
		(*last)->next = b;
	else
		(*last) = b;
		// printf("%p, expand size %lu\n", b, b->size + b->rest + BLOCK_SIZE);
	return (b);
}
