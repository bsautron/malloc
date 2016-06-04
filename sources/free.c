/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 16:38:28 by bsautron          #+#    #+#             */
/*   Updated: 2016/06/03 16:38:29 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc_helpers.h>

static void		delete_one(t_block **b)
{
	t_block		*tmp;

	tmp = *b;
	if (tmp)
	{
		if (tmp->prev)
			tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		if (!tmp->prev)
			g_base[GET_ZONE(tmp)] = tmp->next;
	}
	*b = NULL;
}

static void		delete_munmap(t_block **b, size_t align_size)
{
	delete_one(b);
	if (munmap(*b, align_size) == 0)
		MALLOC_DEBUG("munmap ZONE");
	else
		MALLOC_DEBUG("/!\\ munmap FAILED");
}

void			free(void *ptr)
{
	t_block		*b;
	size_t		align_size;

	pthread_mutex_lock(&g_thread_safe.mutex_free);
	MALLOC_DEBUG("-- FREE --");
	if (valid_addr(ptr))
	{
		b = ptr - BLOCK_SIZE;
		align_size = ALIGNPAGE(b->size + BLOCK_SIZE, getpagesize());
		b->flag |= FLAG_FREE;
		if (b->prev && IS_FREE(b->prev))
			b = fusion(b->prev);
		if (b->next)
			b = fusion(b);
		if ((IS_START_HEAP(b) && ((b->next && IS_START_HEAP(b->next))
			|| !b->next)) && !IS_FIRST_EXTEND(b))
			delete_munmap(&b, align_size);
		else
			MALLOC_DEBUG("No munmap");
	}
	pthread_mutex_unlock(&g_thread_safe.mutex_free);
}
