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

static void	*return_null(char *str)
{
	MALLOC_DEBUG(str);
	return (NULL);
}

static void	*get_new_zone(t_block **last, size_t size, int type_zone)
{
	t_block		*b;
	void		*not_first_expand;

	not_first_expand = *last;
	if (size <= 0)
		return (return_null("/!\\ Can't get zone with 0 size"));
	else if (type_zone == TINY)
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
	if (!(b = extend_heap(last, size, type_zone)))
		return (NULL);
	if (not_first_expand)
		(*last)->next = b;
	else
		g_base[type_zone] = b;
	return (b);
}

static void	prepare_block(t_block **b, size_t size, int type_zone)
{
	t_block		*tmp;

	tmp = *b;
	if (ALIGN4(size) + BLOCK_SIZE < tmp->size + tmp->rest && type_zone != LARGE)
		split_block(tmp, size);
	else
	{
		tmp->rest = (tmp->size + tmp->rest) - size;
		tmp->size = size;
	}
	tmp->flag ^= FLAG_FREE;
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

	MALLOC_DEBUG("-- MALLOC --");
	if (size <= 0)
		return (return_null("/!\\ size <= 0 -> return NULL"));
	else if (size <= TINY_ALLOC_SIZE)
	{
		MALLOC_DEBUG("Malloc to TINY_ZONE");
		last = g_base[TINY];
		b = get_block(&last, size, TINY);
	}
	else if (size <= SMALL_ALLOC_SIZE)
	{
		MALLOC_DEBUG("Malloc to SMALL_ZONE");
		last = g_base[SMALL];
		b = get_block(&last, size, SMALL);
	}
	else
	{
		MALLOC_DEBUG("Malloc to LARGE_ZONE");
		last = g_base[LARGE];
		b = get_block(&last, size, LARGE);
	}
	return ((b) ? b->data : return_null("/!\\ Malloc FAILED"));
}
