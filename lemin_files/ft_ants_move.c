/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ants_move.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:11:32 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/29 10:22:13 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** This function checks the ant_id, room and the path that
** are given as parameters and decides what to do :
** 1) If the ants_lst of the room is NULL we just add the ant to the room
** 2) If the ants_lst is NOT NULL we check if the room is the END room
**  2.1) and the path given == path of ants_list then first free ants_list
** and then add the ant
**  2.2) and the path given != path of ants_list then add the ant to room
*/

void				check_ant_vs_room(t_paths *path, t_room *room, int ant_id)
{
	if (room->ants_lst == NULL)
		add_ant_to_room(path, room, ant_id);
	else
	{
		if ((room->position == END) && \
		(path->path_id != room->ants_lst->path->path_id))
			add_ant_to_room(path, room, ant_id);
		else if ((room->position == END) && \
		(path->path_id == room->ants_lst->path->path_id))
		{
			// ft_printf(" FREE the previous ants_lst and create a new one\n");
			ft_free_ants_lst(&(room->ants_lst));
			add_ant_to_room(path, room, ant_id);
		}
		else
		{
			// ft_printf("ants_lst is NOT NULL \n");
			room->ants_lst->ant_id = ant_id;
			room->ants_lst->path = path;
		}
	}
}

/*
** For the given path we go to the end
** and we iterate it in reverse
*/

void				push_ant_to_next_room(t_paths *path)
{
	t_path_list		*path_lst;
	int				id;

	// ft_printf(" pushing ants through path %d \n", path->path_id);
	path_lst = path->path_lst;
	while (path_lst->next != NULL)
		path_lst = path_lst->next;
	while (path_lst->prev != NULL)
	{
		if ((path_lst->room->ants_lst != NULL) && (path_lst->next != NULL))
		{
			// ft_printf("ant %d found in room %s\n", 
			// path_lst->room->ants_lst->ant_id, path_lst->room->name);
			// path_lst->next->room->ant = path_lst->room->ant;
			check_ant_vs_room(path, path_lst->next->room, path_lst->room->ants_lst->ant_id);
			// if ((path_lst->prev != NULL) && 
			if (path_lst->prev->room->ants_lst == NULL)
			{
				id = choose_ant(path, path_lst->room->ants_lst->ant_id);
				// ft_printf(" chosen ant : %d for room %s\n", id, path_lst->room->name);
				check_ant_vs_room(path, path_lst->room, id);
			}
			// else if ((path_lst->prev != NULL) && 
			else if (path_lst->prev->room->ants_lst != NULL)
			{
				// ft_printf(">ant %d for room %s\n", path_lst->prev->room->ants_lst->ant_id, path_lst->room->name);
				// path_lst->room->ant = path_lst->prev->room->ant;
				check_ant_vs_room(path, path_lst->room, path_lst->prev->room->ants_lst->ant_id);
			}
			// else
			// 	path_lst->room->ants_lst->ant_id = 0;
		}
		path_lst = path_lst->prev;
	}
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

void				ft_move_ants(t_ant_farm *ant_farm)
{
	t_paths			*path;
	t_path_list		*path_lst;
	t_ants			*ant_lst;
	size_t			i;

	i = 0;
	while (i < ant_farm->lines)
	{
		path = ant_farm->paths;
		while (path != NULL && path->run != ant_farm->best_run)
			path = path->next;
		// ft_printf("Ant farm best run%d \n", ant_farm->best_run);
		// ft_printf("path id %d - path run %d\n", path->path_id, path->run);
		while (path != NULL && path->run == ant_farm->best_run)
		{
			// ft_printf("path id %d - path run %d\n", path->path_id, path->run);
			// ft_print_ants_in_rooms(ant_farm);
			ant_lst = path->ants_lst;
			path_lst = path->path_lst->next;
			if ((path_lst != NULL) && (path->ants_lst != NULL) && \
			(path_lst->room->ants_lst == NULL) && (i == 0))
			{
				// ft_printf(" 0. Ants list of room in path %d is NULL\n", path->path_id);
				check_ant_vs_room(path, path_lst->room, ant_lst->ant_id);
			}
			else
			{
				// ft_printf(" -. Moving ants on path - room %s\n", path_lst->room->name);
				push_ant_to_next_room(path);
			}
			path = path->next;
		}
		// ft_printf(ANSI_COLOR_YELLOW_PAST);
		(ant_farm->options & OPTION_A) ? : ft_print_move(ant_farm);
		// ft_print_ants_in_rooms(ant_farm);
		// ft_printf("lines i = %d ant_farm->lines = %d\n"ANSI_COLOR_RESET, i, ant_farm->lines);
		i += 1;
	}
}
