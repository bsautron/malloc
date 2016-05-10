#include <malloc.h>


static void print_memory(t_block *b, char *zone_name)
{
	t_block	*tmp;

	tmp = b;
	while (tmp)
	{
		if ((tmp->flag & IS_START_HEAP) != 0)
			printf("%s : %p\n", zone_name, tmp);
		if ((tmp->flag & IS_FREE) == 0)
			printf("%p - %p : %lu octets\n", tmp->data, tmp->data + tmp->size, tmp->size);
		tmp = tmp->next;
	}
}

// sort by addr
void 	show_alloc_mem(void)
{
	(void)print_memory;
	// print_memory(g_base[0], "TINY");
	// print_memory(g_base[1], "SMALL");
	// print_memory(g_base[2], "LARGE");
}
