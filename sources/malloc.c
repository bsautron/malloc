#include <malloc.h>

t_block		*g_base[3];

static void 	*get_new_zone(t_block **last, size_t size, int type_zone)
{
	t_block		*b;
	void 		*not_first_expand;

	not_first_expand = *last;
	if (size <= 0)
	{
		MALLOC_DEBUG("Can't get zone with 0 size");
		return (NULL);
	}
	else if (type_zone == TINY)
	{
		MALLOC_DEBUG("Get zone for TINY");
		size = TINY_ZONE_SIZE;
	}
	else if (type_zone == SMALL)
	{
		MALLOC_DEBUG("Get zone for SMALL");
		size = SMALL_ZONE_SIZE;
	}
	else
		MALLOC_DEBUG("Get zone for LARGE");
	b = extend_heap(last, size, type_zone);
	if (!b)
		return (NULL);

	if (not_first_expand)
		(*last)->next = b;
	else
		g_base[type_zone] = b;
	return (b);
}

static void	prepare_block(t_block **b, size_t size, int type_zone)
{
	t_block		*tmp;

	tmp = *b;
	if (ALIGN4(size) + BLOCK_SIZE < tmp->size + tmp->rest && type_zone != LARGE)
		split_block(tmp, size);
	else
	{
		tmp->rest = (tmp->size + tmp->rest) - size;
		tmp->size = size;
	}
	tmp->flag ^= FLAG_FREE;
}

static void *get_block(t_block **last, size_t size, int type_zone)
{
	t_block		*b;

	// printf("\tdebut get block, *last = g_base = %p\n", *last);
	// if (*last) printf("\tdebut get block, *last->next = %p\n", (*last)->next);
	if (*last == NULL)
		get_new_zone(last, size, type_zone);
	b = find_block(last, size, type_zone);
	// printf("\t\tfind %p\n", b);

	// printf("find %p\n", b);
	if (b)
		prepare_block(&b, size, type_zone);
	else
	{
		get_new_zone(last, size, type_zone);
		b = find_block(last, size, type_zone);
		prepare_block(&b, size, type_zone);
	}
	return (b);
}

void 	*malloc(size_t size)
{
	t_block		*b;
	t_block		*last;

	// printf("-- %s: %ld --\n", "new malloc", size);
	if (size <= 0)
	{
		MALLOC_DEBUG("size <= 0 -> return NULL");
		return (NULL);
	}
	else if (size <= TINY_ALLOC_SIZE)
	{
		MALLOC_DEBUG("Malloc to TINY_ZONE");
		last = g_base[TINY];
		// printf("last %p\n", last);
		b = get_block(&last, size, TINY);
	}
	else if (size <= SMALL_ALLOC_SIZE)
	{
		MALLOC_DEBUG("Malloc to SMALL_ZONE");
		last = g_base[SMALL];
		b = get_block(&last, size, SMALL);
	}
	else
	{
		MALLOC_DEBUG("Malloc to LARGE_ZONE");
		last = g_base[LARGE];
		b = get_block(&last, size, LARGE);
		// return (NULL);
	}
	return ((b) ? b->data : NULL);
}
