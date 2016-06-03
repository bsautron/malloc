/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 16:43:01 by bsautron          #+#    #+#             */
/*   Updated: 2016/06/03 16:43:03 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc_helpers.h>

void	malloc_debug(int line, char *file, char *str)
{
	if (getenv("MALLOC_DEBUG"))
	{
		ft_putstr("[MALLOC DEBUG]: ");
		if (getenv("MALLOC_DEBUG_FILE"))
		{
			ft_putstr("[malloc_debug] Line ");
			ft_putnbr(line);
			ft_putstr(" on file ");
			ft_putstr(file);
			ft_putstr(": ");
		}
		ft_putstr(str);
		ft_putchar('\n');
	}
}
