#include <malloc_helpers.h>

int	valid_addr(void *p)
{
	char	*tmp;

	tmp = p;
	if (p)
		return (p == ((t_block *)(tmp - BLOCK_SIZE))->data);
	return (0);
}
