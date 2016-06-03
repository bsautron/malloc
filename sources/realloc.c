#include <malloc_helpers.h>

static void copy_block(t_block *src, t_block *dst)
{
	int			*sdata;
	int			*ddata;
	size_t		i;

	MALLOC_DEBUG("Copy to new block");
	i = 0;
	sdata = src->ptr;
	ddata = dst->ptr;
	while (i * 4 < src->size && i * 4 < dst->size)
	{
		ddata[i] = sdata[i];
		i++;
	}
}

void 	*realloc(void *ptr, size_t size)
{
	size_t	align_size;
	t_block	*b;
	void	*newp;

	MALLOC_DEBUG("-- REALLOC --");
	align_size = ALIGN4(size);
	if (!ptr)
		return (malloc(size));
	if (valid_addr(ptr))
	{
		if (size <= 0)
			return (ptr);
		b = ptr - BLOCK_SIZE;
		if (align_size <= b->size + b->rest)
		{
			MALLOC_DEBUG("New size <= current size");
			b->rest = b->size + b->rest - size;
			b->size = size;
			if (b->size + b->rest > BLOCK_SIZE && align_size < b->size + b->rest - BLOCK_SIZE)
				split_block(b, size);
			return (b->data);
		}
		else
		{
			MALLOC_DEBUG("New size > current size");
			newp = malloc(size);
			copy_block(b, newp - BLOCK_SIZE);
			free(ptr);
			return (newp);
		}
	}
	return (NULL);
}
