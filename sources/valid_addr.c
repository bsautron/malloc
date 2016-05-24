#include <malloc_helpers.h>

static t_block	*get_block(void *p)
{
	char	*tmp;

	tmp = p;
	return (p = tmp -= BLOCK_SIZE);
}

// Attention faut voir avec ->ptr et ->data;
int	valid_addr(void *p)
{
	char	*tmp;

	tmp = p;
	if (p)
		return (p == ((t_block *)(tmp - BLOCK_SIZE))->data);
	return (0);
}
