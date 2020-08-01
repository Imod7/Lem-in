/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_other.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:37:56 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/01 15:37:24 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void		ft_free_string(char **string, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(string[i]);
		string[i] = NULL;
		i += 1;
	}
	free(string);
	// string = NULL;
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
	// free(ants_lst);
	*ants_lst = NULL;
}
