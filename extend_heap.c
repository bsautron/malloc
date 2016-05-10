#include <malloc_helpers.h>

t_block	*extend_heap(t_block **last, size_t size, int type_zone)
{
	t_block		*b;

	b = (t_block *)mmap(NULL, size + BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (b == MAP_FAILED)
		return (NULL);
	b->size = size;
	b->next = NULL;
	b->flag = IS_FREE | IS_START_HEAP | type_zone;
	if (*last)
		(*last)->next = b;
	else
		(*last) = b;
	return (b);
}
