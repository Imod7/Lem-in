/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ants_move.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:11:32 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/06/26 18:04:13 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

// void				ft_ants_to_rooms(t_ant_farm *ant_farm, t_paths *tmp)
// {
	
// }

// void	ft_print_move(t_ant_farm *ant_farm)
// {
// 	ft_printf("movements\n");
// 	while (ant_farm->room)
// }

void		push_ant(t_paths *path, t_path_list **path_lst)
{
	int	i;

	i = 0;
	(void)path;
	// ft_printf("path_lst->room->ant_id:%i\n", (*path_lst)->room->ant_id);
	// ft_printf("path_lst->room->next->ant_id:%i\n", (*path_lst)->next->room->ant_id);
	(*path_lst)->next->room->ant_id = (*path_lst)->room->ant_id;
	ft_printf("L:%i-%s\n", (*path_lst)->next->room->ant_id, (*path_lst)->next->room->name);
	while (path->ants_lst != NULL)
	{
		if ((size_t)path->ants_lst->ant_id == (*path_lst)->room->ant_id)
			break ;
		path->ants_lst = path->ants_lst->next;
	}
	(*path_lst)->room->ant_id = path->ants_lst->next->ant_id;
	ft_printf("L:%i-%s\n", (*path_lst)->room->ant_id, (*path_lst)->room->name);
	// ft_printf("after\n\n");
}


/*
** Iterate through all the paths
** In each path call the ft_ants_to_rooms function
** to assign ants to the correct rooms
** When the iteration through paths is over
** print the move
*/

void				ft_move_ants(t_ant_farm *ant_farm)
{
	t_paths			*path;
	t_path_list		*path_lst;
	t_paths			*head;
	t_path_list		*tail;
	int				i;

	i = 0;
	ft_print_paths_list(ant_farm);
	ft_print_paths_list_detail(ant_farm);
	path = ant_farm->paths;
	head = ant_farm->paths;
	path_lst = ant_farm->paths->path_lst->next;
	tail = path->path_lst;
	while (tail && tail->next != NULL)
	{
		tail = tail->next;
	}
	path->tail = tail;
	while (i < 3)
	{
		path = head;
		while (path != NULL)
		{
			/* need a function that goes to the end
			**
			*/
			// ft_printf("the end room:%s\n", path_lst->tail->room->name);
			// ft_printf("room:%s\n", path->tail->room->name);
			// ft_printf("room:%s\n", path->tail->prev->room->name);
			tail = path->tail->prev;
			// path_lst = path->path_lst->next;
			ft_printf("current room:%s in path:%i with ant:%i\n", path_lst->room->name, path->path_id, path_lst->room->ant_id);
			if (tail->room->ant_id != 0)
			{
				// ft_printf("before path_lst->room->ant_id:%i\n", path_lst->room->ant_id);
				push_ant(path, &tail);
				// ft_printf("path_lst->room->ant_id:%i\n", path_lst->room->ant_id);
				// ft_printf("path_lst->room->next->ant_id:%i\n", path_lst->next->room->ant_id);
			}
			else
			{
				path_lst->room->ant_id = path->ants_lst->ant_id;
				ft_printf("L:%i-%s\n", path_lst->room->ant_id, path_lst->room->name);
			}
			// ft_printf(ANSI_COLOR_YELLOW"room:%s now occupied by ant:%i\n"ANSI_COLOR_RESET, path_lst->room->name, path_lst->room->ant_id);
			path = path->next;
		}
		ft_printf("\n\n");
		i++;
	}
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
