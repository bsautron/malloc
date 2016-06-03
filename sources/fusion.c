/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fusion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 16:42:44 by bsautron          #+#    #+#             */
/*   Updated: 2016/06/03 16:42:45 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc_helpers.h>

t_block		*fusion(t_block *b)
{
	if (b && b->next && IS_FREE(b->next) && !IS_START_HEAP(b->next))
	{
		MALLOC_DEBUG("Fusion block");
		b->size += b->rest + BLOCK_SIZE + b->next->size;
		b->rest = b->next->rest;
		b->next = b->next->next;
		if (b->next)
			b->next->prev = b;
		return (fusion(b));
	}
	return (b);
}
