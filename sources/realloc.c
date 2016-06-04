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

static void	*return_realloc(void *ptr, char *str)
{
	pthread_mutex_unlock(&g_thread_safe.mutex_realloc);
	if (ptr)
		return (ptr);
	if (str)
		MALLOC_DEBUG(str);
	return (NULL);
}

void		*realloc(void *ptr, size_t size)
{
	t_block	*b;

	pthread_mutex_lock(&g_thread_safe.mutex_realloc);
	MALLOC_DEBUG("-- REALLOC --");
	if (!ptr)
		return (return_realloc(malloc(size), NULL));
	if (valid_addr(ptr))
	{
		if (size <= 0)
			return (return_realloc(ptr, NULL));
		b = ptr - BLOCK_SIZE;
		if (ALIGN4(size) <= b->size + b->rest)
		{
			MALLOC_DEBUG("New size <= current size");
			b->rest = b->size + b->rest - size;
			b->size = size;
			if (b->size + b->rest > BLOCK_SIZE
				&& ALIGN4(size) < b->size + b->rest - BLOCK_SIZE)
				split_block(b, size);
			return (return_realloc(b->data, NULL));
		}
		else
			return (return_realloc(bigger_malloc(ptr, b, size), NULL));
	}
	return (return_realloc(NULL, NULL));
}
