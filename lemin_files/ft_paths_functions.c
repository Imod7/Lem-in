/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_paths_functions.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 14:18:09 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/06/27 17:59:02 by dominiquesa   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void				ft_paths_discovered(t_ant_farm *ant_farm)
{
	t_paths			*temp;

	temp = ant_farm->paths;
	while (temp->next != NULL)
	{
		temp = temp->next;
		ant_farm->discovered_paths += 1;
	}
}

t_room				*ft_get_start_room(t_room *temp)
{
	while (temp != NULL)
	{
		if (temp->position == START)
			break ;
		temp = temp->next;
	}
	return (temp);
}
