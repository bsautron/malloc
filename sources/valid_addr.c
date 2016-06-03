#include <malloc_helpers.h>

static t_block	*get_block(void *p)
{
	if (p)
		return (p - BLOCK_SIZE);
	return (NULL);
}

int	valid_addr(void *p)
{
	t_block		*meta_block;
	int			ret;

	ret = 0;
	meta_block = get_block(p);
	if (meta_block)
		ret = (meta_block->ptr == p);
	MALLOC_DEBUG((ret) ? "Addr valid" : "/!\\ Addr not valid");
	return (ret);
}
