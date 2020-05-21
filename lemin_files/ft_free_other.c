/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_other.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/04 15:40:03 by dominique     #+#    #+#                 */
/*   Updated: 2020/05/16 08:32:29 by dominique     ########   odam.nl         */
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
