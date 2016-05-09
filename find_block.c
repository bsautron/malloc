#include <malloc_helpers.h>

t_block			*find_block(t_block **last, size_t size)
{
	t_block	*b;

	b = g_base[0];
	while (b && !b->flag.free && size > b->size)
	{
		*last = b;
		b = b->next;
	}
	return (b);
}
