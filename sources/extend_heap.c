/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_heap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 16:37:44 by bsautron          #+#    #+#             */
/*   Updated: 2016/06/03 16:37:45 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc_helpers.h>

static t_block	*fill_block(t_block *b, size_t align_size, size_t size)
{
	b->size = size;
	b->rest = align_size - size - BLOCK_SIZE;
	b->next = NULL;
	b->ptr = b->data;
	return (b);
}

t_block			*extend_heap(t_block **last, size_t size, int type_zone)
{
	t_block		*b;
	size_t		align_size;

	MALLOC_DEBUG("Need to extend the heap");
	align_size = ALIGNPAGE(size + BLOCK_SIZE, getpagesize());
	b = (t_block *)mmap(NULL, align_size, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	if (b == MAP_FAILED)
	{
		MALLOC_DEBUG("/!\\ mmap FAILED");
		return (NULL);
	}
	b = fill_block(b, align_size, size);
	b->flag = FLAG_FREE | FLAG_START_HEAP | type_zone;
	b->prev = *last;
	if (*last)
		(*last)->next = b;
	else
	{
		b->flag |= FLAG_FRIST_EXTEND;
		(*last) = b;
	}
	MALLOC_DEBUG("New zone");
	return (b);
}
