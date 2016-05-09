#include <malloc.h>

t_block		*g_base[3];

void 	*malloc(size_t size)
{
	t_block		*b;
	t_block		*last;

	(void)last;
	(void)b;
	if (size <= 0)
	{
		MALLOC_DEBUG("size <= 0 -> return NULL");
		return (NULL);
	}
	else if (size <= TINY_ALLOC_SIZE)
	{
		MALLOC_DEBUG("Malloc to TINY_ZONE");
		if (g_base[TINY])
		{
			MALLOC_DEBUG("later");
			last = g_base[TINY];
			b = find_block(&last, size);
		}
		else
		{
			MALLOC_DEBUG("First time malloc TINY");
			b = extend_heap(NULL, size, TINY);
			if (!b)
				return (NULL);
			g_base[TINY] = b;
		}
	}
	else if (size <= SMALL_ALLOC_SIZE)
	{
		MALLOC_DEBUG("Malloc to SMALL_ZONE");
		return (NULL);
	}
	else
	{
		MALLOC_DEBUG("Malloc to LARGE_ZONE");
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
