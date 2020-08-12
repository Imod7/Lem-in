/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_other.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:37:56 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 13:48:09 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			ft_free_string(char **string, size_t size)
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
}

void			ft_free_ants_lst(t_ants **ants_lst)
{
	t_ants		*curr_node;
	t_ants		*next_node;

	curr_node = *ants_lst;
	while (curr_node != NULL)
	{
		next_node = curr_node->next;
		free(curr_node);
		curr_node = next_node;
	}
	*ants_lst = NULL;
}
