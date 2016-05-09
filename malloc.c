#include <malloc.h>

t_block		*g_base[3];

void 	*malloc(size_t size)
{
	t_block		*b;
	t_block		*last;

	if (size <= 0)
		return (NULL);
	else if (size <= TINY_ALLOC_SIZE)
	{
		malloc_debug("size <= TYNY_ALLOC_SIZE");
		if (g_base[TINY])
		{
			last = g_base[TINY];
			b = find_block(&last, size);
			malloc_debug("later");
		}
		else
		{
			malloc_debug("First time malloc TINY");
			b = extend_heap(NULL, size, TINY);
			if (!b)
				return (NULL);
			g_base[TINY] = b;
		}
	}
	else
	{
		(void)last;
		(void)b;
		return (NULL);
	}
	// else if (size <= SMALL_ALLOC_SIZE)
	// {
	//
	// }
	// else
	// {
	//
	// }
	//
	// extend_heap(g_base[TINY], TINY_ZONE_SIZE);
	// extend_heap(g_base[SMALL], SMALL_ZONE_SIZE);
	// extend_heap(g_base[LARGE], size);
	return (b->data);
}
