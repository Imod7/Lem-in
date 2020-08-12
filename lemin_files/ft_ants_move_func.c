/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ants_move_func.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/12 12:15:17 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 12:21:19 by dsaripap      ########   odam.nl         */
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

int				check_ant_vs_room(t_paths *path, t_room *room, int ant_id)
{
	if (room->ants_lst == NULL)
		return (add_ant_to_room(path, room, ant_id));
	else
	{
		if ((room->position == END) && \
		(path->path_id != room->ants_lst->path->path_id))
			return (add_ant_to_room(path, room, ant_id));
		else if ((room->position == END) && \
		(path->path_id == room->ants_lst->path->path_id))
		{
			ft_free_ants_lst(&(room->ants_lst));
			return (add_ant_to_room(path, room, ant_id));
		}
		else
		{
			room->ants_lst->ant_id = ant_id;
			room->ants_lst->path = path;
		}
	}
	return (SUCCESS);
}

int				choose_and_check(t_paths *path, t_path_list *path_lst)
{
	int			id;

	id = choose_ant(path, path_lst->room->ants_lst->ant_id);
	return (check_ant_vs_room(path, path_lst->room, id));
	return (SUCCESS);
}
