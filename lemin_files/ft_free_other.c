/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_other.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:37:56 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/06/23 13:19:11 by dominiquesa   ########   odam.nl         */
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

void			ft_free_ants_lst(t_ants **ants_lst)
{
	t_ants		*curr_node;
	t_ants		*next_node;

	curr_node = *ants_lst;
	while (curr_node != NULL)
	{
		// ft_printf(" freeing ant %d \n", curr_node->ant_id);
		next_node = curr_node->next;
		free(curr_node);
		curr_node = next_node;
	}
	*ants_lst = NULL;
}
