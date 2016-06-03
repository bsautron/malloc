/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 16:38:11 by bsautron          #+#    #+#             */
/*   Updated: 2016/06/03 16:38:12 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc_helpers.h>

t_block			*find_block(t_block **last, size_t size, int type_zone)
{
	t_block	*b;
	size_t	align_size;

	b = g_base[type_zone];
	align_size = ALIGN4(size);
	while (b && (!IS_FREE(b) || align_size > b->size + b->rest))
	{
		*last = b;
		b = b->next;
	}
	if (!b)
		MALLOC_DEBUG("/!\\ No block found");
	else
		MALLOC_DEBUG("New block found");
	return (b);
}
