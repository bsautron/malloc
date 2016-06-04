/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 16:51:21 by bsautron          #+#    #+#             */
/*   Updated: 2016/06/03 16:51:22 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_block		*g_base[3];
t_thread_safe	g_thread_safe = {
	.mutex_malloc = PTHREAD_MUTEX_INITIALIZER,
	.mutex_realloc = PTHREAD_MUTEX_INITIALIZER,
	.mutex_free = PTHREAD_MUTEX_INITIALIZER,
	.mutex_show_alloc_mem = PTHREAD_MUTEX_INITIALIZER,
};

static void	*return_malloc(t_block *b, char *str)
{
	pthread_mutex_unlock(&g_thread_safe.mutex_malloc);
	if (b)
		return (b->data);
	if (str)
		MALLOC_DEBUG(str);
	return (NULL);
}

static void	get_new_zone(t_block **last, size_t size, int type_zone)
{
	t_block		*b;
	void		*not_first_expand;

	not_first_expand = *last;
	if (type_zone == TINY)
	{
		MALLOC_DEBUG("Get zone for TINY");
		size = TINY_ZONE_SIZE;
	}
	else if (type_zone == SMALL)
	{
		MALLOC_DEBUG("Get zone for SMALL");
		size = SMALL_ZONE_SIZE;
	}
	else
		MALLOC_DEBUG("Get zone for LARGE");
	if ((b = extend_heap(last, size, type_zone)))
	{
		if (not_first_expand)
			(*last)->next = b;
		else
			g_base[type_zone] = b;
	}
}

static void	prepare_block(t_block **b, size_t size, int type_zone)
{
	t_block		*tmp;

	tmp = *b;
	if (*b)
	{
		if (ALIGN4(size) + BLOCK_SIZE < tmp->size + tmp->rest
			&& type_zone != LARGE)
			split_block(tmp, size);
		else
		{
			tmp->rest = (tmp->size + tmp->rest) - size;
			tmp->size = size;
		}
		tmp->flag ^= FLAG_FREE;
	}
}

static void	*get_block(t_block **last, size_t size, int type_zone)
{
	t_block		*b;

	if (*last == NULL)
		get_new_zone(last, size, type_zone);
	b = find_block(last, size, type_zone);
	if (b)
		prepare_block(&b, size, type_zone);
	else
	{
		get_new_zone(last, size, type_zone);
		b = find_block(last, size, type_zone);
		prepare_block(&b, size, type_zone);
	}
	return (b);
}

void		*malloc(size_t size)
{
	t_block		*b;
	t_block		*last;

	pthread_mutex_lock(&g_thread_safe.mutex_malloc);
	MALLOC_DEBUG("-- MALLOC --");
	if (size > 0 && size <= TINY_ALLOC_SIZE)
	{
		MALLOC_DEBUG("Malloc to TINY_ZONE");
		last = g_base[TINY];
		b = get_block(&last, size, TINY);
	}
	else if (size > 0 && size <= SMALL_ALLOC_SIZE)
	{
		MALLOC_DEBUG("Malloc to SMALL_ZONE");
		last = g_base[SMALL];
		b = get_block(&last, size, SMALL);
	}
	else if (size > 0)
	{
		MALLOC_DEBUG("Malloc to LARGE_ZONE");
		last = g_base[LARGE];
		b = get_block(&last, size, LARGE);
	}
	return ((size <= 0) ? return_malloc(NULL, "/!\\ size <= 0 -> return NULL")
		: return_malloc(b, "/!\\ Malloc FAILED"));
}
