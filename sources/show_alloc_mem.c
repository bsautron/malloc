#include <malloc.h>

static void print_size_t(size_t n)
{
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
	}
	else
		ft_putchar(n + '0');
}

static void print_addr(void *addr, int end_line)
{
	char	buffer[128];
	char	hex[17];
	int		len;
	int		i;
	size_t	laddr;

	i = 0;
	len = 8;
	hex[16] = 0;
	laddr = (size_t)addr;
	ft_strcpy(hex, "0123456789ABCDEF");
	ft_bzero(buffer, 128);
	while (laddr)
	{
		buffer[i] = hex[laddr % 16];
		laddr /= 16;
		i++;
	}
	ft_putstr("0x");
	ft_putstr(ft_reverse(buffer));
	if (end_line)
		ft_putchar('\n');
}

static void print_line_memory(t_block *b)
{
	print_addr(b->data, 0);
	ft_putstr(" - ");
	print_addr(b->data + b->size, 0);
	if (getenv("MALLOC_DEBUG"))
	{
		ft_putstr(" (+ ");
		ft_putnbr(b->rest);
		ft_putstr(")");
	}
	ft_putstr(" : ");
	print_size_t(b->size);
	ft_putendl(" octets");
}

static void print_memory(t_block *b, size_t *total)
{
	t_block	*tmp;

	tmp = b;
	while (tmp)
	{
		if (IS_START_HEAP(tmp))
		{
			if (GET_ZONE(tmp) == TINY)
				ft_putstr("TINY");
			else if (GET_ZONE(tmp) == SMALL)
				ft_putstr("SMALL");
			else
				ft_putstr("LARGE");
			ft_putstr(" : ");
			print_addr(tmp, 1);
		}
		if (getenv("MALLOC_DEBUG"))
		{
			ft_putchar('\t');
			ft_putstr((IS_FREE(tmp)) ? "[free] " : "[    ] ");
			print_line_memory(tmp);
			if (!IS_FREE(tmp))
				*total += tmp->size;
		}
		else if (!IS_FREE(tmp))
		{
			print_line_memory(tmp);
			*total += tmp->size;
		}
		tmp = tmp->next;
		if (tmp && IS_START_HEAP(tmp))
			break ;
	}
}

static int	count_start_heap(t_block *b)
{
	int		ret;
	t_block	*tmp;

	ret = 0;
	tmp = b;
	while (tmp)
	{
		if (IS_START_HEAP(tmp))
			ret++;
		tmp = tmp->next;
	}
	return (ret);
}

static void get_start_heap(size_t *start_heap, t_block *b)
{
	int		i;
	t_block	*tmp;

	i = 0;
	while (start_heap[i])
		i++;
	tmp = b;
	while (tmp)
	{
		if (IS_START_HEAP(tmp))
			start_heap[i++] = (size_t)tmp;
		tmp = tmp->next;
	}
}

static void size_t_sort(size_t *tab, int len)
{
	int		i;
	int		j;
	size_t	tmp;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (tab[i] > tab[j])
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void show(int len, size_t *total)
{
	size_t	start_heap[len];
	int		i;

	ft_bzero(start_heap, sizeof(size_t) * len);
	get_start_heap(start_heap, g_base[TINY]);
	get_start_heap(start_heap, g_base[SMALL]);
	get_start_heap(start_heap, g_base[LARGE]);
	size_t_sort(start_heap, len);
	i = 0;
	while (i < len)
		print_memory((t_block *)start_heap[i++], total);

}

void 	show_alloc_mem(void)
{
	size_t		total;
	int			len;

	total = 0;
	len = count_start_heap(g_base[TINY]) + count_start_heap(g_base[SMALL]) + count_start_heap(g_base[LARGE]);
	show(len, &total);
	ft_putstr("Total : ");
	print_size_t(total);
	ft_putendl(" octets");
}
