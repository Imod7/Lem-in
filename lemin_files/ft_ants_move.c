/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ants_move.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:11:32 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/06/21 16:48:28 by dominiquesa   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int					choose_ant(t_paths *path, int ant_id)
{
	t_ants			*ant_lst;

	ft_printf(ANSI_COLOR_GREEN_EMER);
	// ft_printf(" choose next ant than %d \n", ant_id);
	ant_lst = path->ants_lst;
	while (ant_lst != NULL)
	{
		if ((ant_lst->next != NULL) && (ant_id == ant_lst->ant_id))
			return (ant_lst->next->ant_id);
		ant_lst = ant_lst->next;
	}
	return (0);
}

void				ft_add_ants_to_antslist(t_ants **lst, t_ants *new)
{
	t_ants			*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

void				add_ant_to_room(t_paths *path, t_room *room, int ant_id)
{
	t_ants			*ant;

	// ft_printf(ANSI_COLOR_RED_CINA" ant_id %d path of the room %s is ##### %d \n"ANSI_COLOR_RESET, ant_id, room->name, room->path->path_id);
	if (room->ants_lst == NULL)
	{
		// ft_printf("ants_lst is NULL - ant %d\n", ant_id);
		ant = (t_ants *)ft_memalloc(sizeof(t_ants));
		ant->ant_id = ant_id;
		ant->path = path;
		ft_add_ants_to_antslist(&(room->ants_lst), ant);
	}
	else
	{
		if ((room->position == END) && \
		(path->path_id != room->ants_lst->path->path_id))
		{
			// in this case we only add to the ants_list of the room end
			ant = (t_ants *)ft_memalloc(sizeof(t_ants));
			ant->ant_id = ant_id;
			ant->path = path;
			ft_add_ants_to_antslist(&(room->ants_lst), ant);
		}
		else if ((room->position == END) && \
		(path->path_id == room->ants_lst->path->path_id))
		{
			// we have to free the previous ants_lst and create a new one
			room->ants_lst->ant_id = ant_id;
			room->ants_lst->path = path;
		}
		else
		{
			// ft_printf("ants_lst is NOT NULL \n");
			room->ants_lst->ant_id = ant_id;
			room->ants_lst->path = path;
		}
	}
}

void				push_ant_to_next_room(t_paths *path)
{
	t_path_list		*path_lst;
	int				id;

	ft_printf(ANSI_COLOR_GREEN_EMER);
	// ft_printf(" pushing ants through path %d \n", path->path_id);
	path_lst = path->path_lst;
	while (path_lst->next != NULL)
		path_lst = path_lst->next;
	while (path_lst->prev != NULL)
	{
		if ((path_lst->room->ants_lst != NULL) && (path_lst->next != NULL))
		{
			// ft_printf("ant %d found room %s\n", 
			// path_lst->room->ants_lst->ant_id, path_lst->room->name);
			// path_lst->next->room->ant = path_lst->room->ant;
			add_ant_to_room(path, path_lst->next->room, path_lst->room->ants_lst->ant_id);
			if ((path_lst->prev != NULL) && \
			(path_lst->prev->room->ants_lst == NULL))
			{
				// ft_printf("we are in room %s\n", path_lst->room->name);
				id = choose_ant(path, path_lst->room->ants_lst->ant_id);
				// ft_printf(" chosen ant : %d for room %s\n", id, path_lst->room->name);
				add_ant_to_room(path, path_lst->room, id);
			}
			else if ((path_lst->prev != NULL) && \
			(path_lst->prev->room->ants_lst != NULL))
			{
				// ft_printf(" Ant : %d for room %s\n", path_lst->prev->room->ants_lst->ant_id, path_lst->room->name);
				// path_lst->room->ant = path_lst->prev->room->ant;
				add_ant_to_room(path, path_lst->room, path_lst->prev->room->ants_lst->ant_id);
			}
			else
				path_lst->room->ants_lst->ant_id = 0;
		}
		path_lst = path_lst->prev;
	}
}

/*
** Iterate through all the paths
** In each path call the ft_ants_to_rooms function
** to assign ants to the correct rooms
** When the iteration through paths is over
** print the move
** PSEUDOCODE
** first try to move ants through 1 path
** while (paths != NULL) && (path->path_lst != NULL)
** if (room is empty)
**    add_ant_to_room
** else
**    push_ant_to_next_room
**    add_ant_to_room
**   print the path_id and ant_id
**
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
		while (path != NULL)
		{
			// ft_print_ants_in_rooms(ant_farm);
			ant_lst = path->ants_lst;
			// if (ant_lst != NULL)
			// {
			// 	ft_printf("1 case path %d\n", path->path_id);
			// 	// ft_printf("L%d", ant_lst->ant_id);
			// }
			path_lst = path->path_lst->next;
			if ((path_lst != NULL) && (path_lst->room->ants_lst == NULL) && (i == 0))
			{
				// ft_printf("ants list of path %d is NULL\n", path->path_id);
				add_ant_to_room(path, path_lst->room, ant_lst->ant_id);
			}
			else
			{
				// ft_printf("moving ants on path - room %s\n", path_lst->room->name);
				push_ant_to_next_room(path);
			}
				// ft_ants_to_rooms(ant_farm, tmp);
			path = path->next;
		}
		ft_printf(ANSI_COLOR_YELLOW_PAST);
		ft_print_move(ant_farm);
		ft_print_ants_in_rooms(ant_farm);
		ft_printf("\n"ANSI_COLOR_RESET);
		i += 1;
	}
}
