/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 17:35:54 by bsautron          #+#    #+#             */
/*   Updated: 2016/06/04 17:35:55 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc_helpers.h>

static void	print_addr(void *addr, int end_line)
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

static void	print_line_memory(t_block *b)
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
	ft_putsize_t(b->size);
	ft_putendl(" octets");
}

static void	print_and_count(t_block *b, size_t *total)
{
	if (getenv("MALLOC_DEBUG"))
	{
		ft_putchar('\t');
		ft_putstr((IS_FREE(b)) ? "[free] " : "[    ] ");
		print_line_memory(b);
		if (!IS_FREE(b))
			*total += b->size;
	}
	else if (!IS_FREE(b))
	{
		print_line_memory(b);
		*total += b->size;
	}
}

void		print_memory(t_block *b, size_t *total)
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
		print_and_count(tmp, total);
		tmp = tmp->next;
		if (tmp && IS_START_HEAP(tmp))
			break ;
	}
}
