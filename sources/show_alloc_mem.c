/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 16:45:54 by bsautron          #+#    #+#             */
/*   Updated: 2016/06/03 16:45:55 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

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

static void	get_start_heap(size_t *start_heap, t_block *b)
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

static void	size_t_sort(size_t *tab, int len)
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

static void	show(int len, size_t *total)
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

void		show_alloc_mem(void)
{
	size_t		total;
	int			len;

	pthread_mutex_lock(&g_thread_safe.mutex_show_alloc_mem);
	total = 0;
	len = count_start_heap(g_base[TINY])
		+ count_start_heap(g_base[SMALL])
		+ count_start_heap(g_base[LARGE]);
	show(len, &total);
	ft_putstr("Total : ");
	ft_putsize_t(total);
	ft_putendl(" octets");
	pthread_mutex_unlock(&g_thread_safe.mutex_show_alloc_mem);
}
