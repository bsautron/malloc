#include <malloc_helpers.h>

t_block			*find_block(t_block **last, size_t size, int type_zone)
{
	t_block	*b;

	b = g_base[type_zone];
	while (b && !b->flag.free && size > b->size)
	{
		*last = b;
		b = b->next;
	}
	return (b);
}
