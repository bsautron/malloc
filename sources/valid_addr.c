#include <malloc_helpers.h>

static t_block	*get_block(void *p)
{
	if (p)
		return (p -= BLOCK_SIZE);
	return (NULL);
}

// Attention faut voir avec ->ptr et ->data;
int	valid_addr(void *p)
{
	t_block		*meta_block;

	meta_block = get_block(p);
	if (meta_block)
		return (meta_block->ptr == p);
	return (0);
}
