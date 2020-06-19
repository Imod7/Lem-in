/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_other.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:37:56 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/06/19 10:37:58 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void		ft_free_line(char **line_items, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(line_items[i]);
		line_items[i] = NULL;
		i += 1;
	}
	free(line_items);
}
