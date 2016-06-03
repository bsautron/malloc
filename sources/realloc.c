/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 16:53:09 by bsautron          #+#    #+#             */
/*   Updated: 2016/06/03 16:53:10 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc_helpers.h>

static void	copy_block(t_block *src, t_block *dst)
{
	int			*sdata;
	int			*ddata;
	size_t		i;

	MALLOC_DEBUG("Copy to new block");
	i = 0;
	sdata = src->ptr;
	ddata = dst->ptr;
	while (i * 4 < src->size && i * 4 < dst->size)
	{
		ddata[i] = sdata[i];
		i++;
	}
}

static void	*bigger_malloc(void *ptr, t_block *b, size_t size)
{
	void	*newp;

	MALLOC_DEBUG("New size > current size");
	newp = malloc(size);
	copy_block(b, newp - BLOCK_SIZE);
	free(ptr);
	return (newp);
}

void		*realloc(void *ptr, size_t size)
{
	t_block	*b;

	MALLOC_DEBUG("-- REALLOC --");
	if (!ptr)
		return (malloc(size));
	if (valid_addr(ptr))
	{
		if (size <= 0)
			return (ptr);
		b = ptr - BLOCK_SIZE;
		if (ALIGN4(size) <= b->size + b->rest)
		{
			MALLOC_DEBUG("New size <= current size");
			b->rest = b->size + b->rest - size;
			b->size = size;
			if (b->size + b->rest > BLOCK_SIZE
				&& ALIGN4(size) < b->size + b->rest - BLOCK_SIZE)
				split_block(b, size);
			return (b->data);
		}
		else
			return (bigger_malloc(ptr, b, size));
	}
	return (NULL);
}
