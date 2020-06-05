/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ants_move.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/24 11:31:38 by dominique     #+#    #+#                 */
/*   Updated: 2020/06/02 10:26:57 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

// void				ft_ants_to_rooms(t_ant_farm *ant_farm, t_paths *tmp)
// {
		
// }

/*
** Iterate through all the paths
** In each path call the ft_ants_to_rooms function
** to assign ants to the correct rooms
** When the iteration through paths is over
** print the move
*/

void				ft_move_ants(t_ant_farm *ant_farm)
{
	t_paths			*tmp;

	tmp = ant_farm->paths;
	while (tmp != NULL)
	{
		// ft_ants_to_rooms(ant_farm, tmp);
		tmp = tmp->next;
	}
	// ft_print_move(ant_farm);
}

// void				ft_print_ants_end(t_paths *path)
// {
// 	t_path_list		*temp_lst;
// 	t_ants			*ants_lst;

// 	temp_lst = path->path_lst;
// 	while (temp_lst->room->position != END)
// 		temp_lst = temp_lst->next;
// 	ants_lst = temp_lst->room->ants;
// 	while (ants_lst != NULL)
// 	{
// 		ft_printf("L%d-%s ", temp_lst->room->ants->ant_id, \
// 			temp_lst->room->name);
// 		ants_lst = ants_lst->next;
// 	}
// }

// void				ft_print_move(t_ant_farm *ant_farm)
// {
// 	t_path_list		*path_lst;
// 	t_paths			*path;

// 	ft_printf("Print moves \n");
// 	path = ant_farm->paths;
// 	while (path != NULL)
// 	{
// 		path_lst = path->path_lst->next;
// 		while (path_lst->next != NULL)
// 			path_lst = path_lst->next;
// 		while (path_lst != NULL)
// 		{
// 			if (path_lst->room->position == END)
// 				ft_print_ants_end(path);
// 			if (path_lst->room->ants != NULL)
// 				ft_printf("L%d-%s ", path_lst->room->ants->ant_id, \
// 				path_lst->room->name);
// 			path_lst = path_lst->prev;
// 		}
// 		path = path->next;
// 	}
// 	ft_printf("\n");
// }

// void				ft_keep_ants_moving(t_ant_farm *ant_farm)
// {
// 	t_path_list		*path_lst;

// 	path_lst = ant_farm->paths->path_lst->next;
// 	ft_printf(" ASSIGN and MOVE\n");
// 	while (path_lst->next != NULL)
// 	{
// 		if (path_lst->room->ants != NULL)
// 			path_lst = path_lst->next;
// 		else
// 			break ;
// 	}
// 	// path_lst = path_lst->prev;
// 	while (path_lst != NULL)
// 	{
// 		if (path_lst->room->position == END)
// 		{
// 			ft_printf(" END room\n");
// 			// ft_ants_addend(&(path_lst->room->ants), ant);
// 		}
// 		if (path_lst->room->ants != NULL)
// 		{
// 			ft_printf("   ant %d moves to room %s", path_lst->room->ants->ant_id, path_lst->next->room->name);
// 			path_lst->next->room->ants = path_lst->room->ants;
// 			ft_printf(" ant %d moves to room %s\n", path_lst->prev->room->ants->ant_id, path_lst->room->name);
// 			path_lst->room->ants = path_lst->prev->room->ants;
// 			// ft_printf("ant %d, room %s \n",path_lst->room->ant_id, path_lst->room->name);
// 		}
// 		else
// 		{
// 			break ;
// 		}
// 		path_lst = path_lst->prev;
// 	}
// }
