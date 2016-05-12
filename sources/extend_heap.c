#include <malloc_helpers.h>

t_block	*extend_heap(t_block **last, size_t size, int type_zone)
{
	t_block		*b;
	size_t		align_size;

	align_size = ALIGNPAGE(size, getpagesize());
	printf("%lu\n", align_size);
	b = (t_block *)mmap(NULL, align_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (b == MAP_FAILED)
		return (NULL);
	b->size = size;
	b->rest = align_size - size - BLOCK_SIZE;
	b->next = NULL;
	b->flag = IS_FREE | IS_START_HEAP | type_zone;
	if (*last)
		(*last)->next = b;
	else
		(*last) = b;
	return (b);
}
