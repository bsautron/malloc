#include <malloc_helpers.h>

int	valid_add(void *p)
{
	char	*tmp;

	tmp = p;
	if (p)
		return (p == ((t_block *)(tmp - BLOCK_SIZE))->data);
	return (0);
}
