/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ants_move.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:11:32 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 12:43:52 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int					push_ants_next_check(t_paths *path, t_path_list *path_lst)
{
	if (check_ant_vs_room(path, path_lst->next->room, \
	path_lst->room->ants_lst->ant_id) != SUCCESS)
		return (ERROR);
	if (path_lst->prev->room->ants_lst == NULL)
		choose_and_check(path, path_lst);
	else if (path_lst->prev->room->ants_lst != NULL)
	{
		if (check_ant_vs_room(path, path_lst->room, \
		path_lst->prev->room->ants_lst->ant_id) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

/*
** For the given path we go to the end
** and we iterate it in reverse
*/

int					push_ant_to_next_room(t_paths *path)
{
	t_path_list		*path_lst;

	path_lst = path->path_lst;
	while (path_lst->next != NULL)
		path_lst = path_lst->next;
	while (path_lst->prev != NULL)
	{
		if ((path_lst->room->ants_lst != NULL) && (path_lst->next != NULL))
		{
			if (push_ants_next_check(path, path_lst) != SUCCESS)
				return (ERROR);
		}
		else if (path_lst->room->ants_lst != NULL && path_lst->next == NULL && \
		path_lst->prev->prev == NULL)
			choose_and_check(path, path_lst);
		path_lst = path_lst->prev;
	}
	return (SUCCESS);
}

static int			ants_move_loop(t_ant_farm *ant_farm, t_paths *path, \
									size_t i)
{
	t_path_list		*p_lst;
	t_ants			*a_lst;

	while (path != NULL && path->run == ant_farm->best_run)
	{
		a_lst = path->ants_lst;
		p_lst = path->path_lst->next;
		if ((p_lst != NULL) && (path->ants_lst != NULL) && \
		(p_lst->room->ants_lst == NULL) && (i == 0))
		{
			if (check_ant_vs_room(path, p_lst->room, a_lst->ant_id) != SUCCESS)
				return (ERROR);
		}
		else
		{
			if (push_ant_to_next_room(path) != SUCCESS)
				return (ERROR);
		}
		path = path->next;
	}
	return (SUCCESS);
}

/*
** Iterate through all the paths
** In each path call we check if there are ants on the path already
** by checking if the ants_lst is NULL or not
** If there are not we just add the first ant
** If there are ants already we have to push the ant to next room
** before adding a new one
** If option -a was selected then it does not print_the_move
** If option -a was not selected then it prints the ants moves
*/

int					ft_move_ants(t_ant_farm *ant_farm)
{
	t_paths			*path;
	size_t			i;

	i = 0;
	while (i < ant_farm->lines)
	{
		path = ant_farm->paths;
		while (path != NULL && path->run != ant_farm->best_run)
			path = path->next;
		if (ants_move_loop(ant_farm, path, i) != SUCCESS)
			return (ERROR);
		(ant_farm->options & OPTION_A) ? : ft_print_move(ant_farm);
		i += 1;
	}
	return (SUCCESS);
}
