/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_paths_functions.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 14:18:09 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/20 18:43:55 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void				ft_paths_discovered(t_ant_farm *ant_farm)
{
	t_paths			*temp;

	temp = ant_farm->paths;
	ant_farm->discovered_paths = 0;
	while (temp != NULL) //&& temp->run == ant_farm->best_run)
	{
		// ft_printf("path id %d path run %d\n", temp->path_id, temp->run);
		// ft_printf("current run %d \n", ant_farm->best_run);
		if (temp->run == ant_farm->best_run)
			ant_farm->discovered_paths += 1;
		temp = temp->next;
	}
	// ant_farm->discovered_paths += 1;
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

t_room				*ft_get_end_room(t_ant_farm *ant_farm)
{
	t_room			*temp;

	temp = ant_farm->rooms_lst;
	while (temp != NULL)
	{
		if (temp->position == END)
			break ;
		temp = temp->next;
	}
	return (temp);
}
