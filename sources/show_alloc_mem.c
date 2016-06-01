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
	char	buffer[12];
	char	hex[17];
	int		len;
	int		i;
	size_t	laddr;

	i = 0;
	len = 8;
	hex[16] = 0;
	laddr = (size_t)addr;
	ft_strcpy(hex, "0123456789ABCDEF");
	ft_bzero(buffer, 12);
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

static void print_memory(t_block *b, char *zone_name, size_t *total)
{
	t_block	*tmp;

	tmp = b;
	while (tmp)
	{
		if (IS_START_HEAP(tmp))
		{
			ft_putstr(zone_name);
			ft_putstr(" : ");
			print_addr(tmp, 1);
		}
		if (!IS_FREE(tmp))
		{
			print_addr(tmp->data, 0);
			ft_putstr(" - ");
			print_addr(tmp->data + tmp->size, 0);
			ft_putstr(" : ");
			print_size_t(tmp->size);
			ft_putendl(" octets");
			*total += tmp->size;
		}
		tmp = tmp->next;
	}
}

void 	show_alloc_mem(void)
{
	size_t		total;

	total = 0;
	print_memory(g_base[TINY], "TINY", &total);
	print_memory(g_base[SMALL], "SMALL", &total);
	print_memory(g_base[LARGE], "LARGE", &total);
	ft_putstr("Total : ");
	print_size_t(total);
	ft_putendl(" octets");
}
