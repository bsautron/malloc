#include <malloc_helpers.h>

t_block			*find_block(t_block **last, size_t size)
{
	t_block	b;

	b = g_base;
	while (b && !b->free && size > b->size)
	{
		*last = b;
		b = b->next;
	}
	return (b);
}
