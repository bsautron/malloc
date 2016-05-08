#include <malloc.h>

void 	*malloc(size_t size)
{
	if (!g_base)
		g_base = NULL;
	(void)size;
	ft_putendl("holla");
	return (NULL);
}
