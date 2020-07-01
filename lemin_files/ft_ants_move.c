/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ants_move.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:11:32 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/01 14:01:23 by svan-der      ########   odam.nl         */
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

void	ft_put_ant_to_room(t_paths **path, t_path_list **path_lst)
{
	t_ants *temp;

	(*path)->ants_amount -= 1;
	temp = (t_ants *)ft_memalloc(sizeof(t_ants));
	temp->ant_id = (*path)->ants_lst->ant_id;
	temp->path = *path;
	ft_add_ants_to_list(&((*path_lst)->room->ants_lst), temp);
	// (*path_lst)->room->ant_id = (*path)->ants_lst->ant_id;
	ft_printf("L:%i-%s\n", (*path_lst)->room->ants_lst->ant_id, (*path_lst)->room->name);
}

void				ft_add_ants_to_list(t_ants **lst, t_ants *new)
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

void		print_ants_to_rooms(t_ant_farm *ant_farm)
{
	t_paths *temp;
	t_path_list *temp_lst;

	temp = ant_farm->paths;
	ft_print_ants(ant_farm);
	while (temp != NULL)
	{
		temp_lst = temp->path_lst;
		// if (temp_lst->room->ants_lst == NULL)
		// 	break ;
		ft_printf("\npath_id:%i", temp->path_id);
		while (temp_lst != NULL)
		{
			if (temp_lst->room->position != END)
			{
				if (temp_lst->room->ants_lst == NULL)
					ft_printf(ANSI_COLOR_GREEN_EMER"|%s:%i|->"ANSI_COLOR_RESET, temp_lst->room->name, 0);
				else
					ft_printf(ANSI_COLOR_GREEN_EMER"|%s:%i|->"ANSI_COLOR_RESET, temp_lst->room->name, temp_lst->room->ants_lst->ant_id);
			}
			else
			{
				if (temp_lst->room->ants_lst == NULL)
					ft_printf(ANSI_COLOR_GREEN_EMER"|%s:%i|"ANSI_COLOR_RESET, temp_lst->room->name, 0);
				else
					ft_printf(ANSI_COLOR_GREEN_EMER"|%s:%i|"ANSI_COLOR_RESET, temp_lst->room->name, temp_lst->room->ants_lst->ant_id);
			}
			temp_lst = temp_lst->next;
		}
		temp = temp->next;
	}
	ft_printf("\n");
	ft_printf("finished printing\n"ANSI_COLOR_RESET);
}

int			get_ant(t_paths *path, int ant_id, t_path_list **path_lst)
{
	t_ants *temp;

	temp = path->ants_lst;
	while (temp->next != NULL)
	{
		// ft_printf("ant_id:%i\n", path->ants_lst->ant_id);
		if (temp->ant_id == ant_id)
		{
			ft_put_ant_to_room(&path, path_lst);
			// path->ants_amount -= 1;
			return (temp->next->ant_id);
		}
		temp = temp->next;
	}
	return (0);
}

void		push_ant(t_paths *path, t_path_list **path_lst)
{
	t_path_list *tail;
	int			ant_id;

	(void)path_lst;
	tail = path->tail;
	ft_printf("\n\n");
	ft_printf("  inside push ant\n");
	// ft_printf("ptr tail:%p\n", tail);
	// ft_printf("tail:%s\n", tail->room->name);
	while (tail->room->position != START)
	{
		ft_printf("position:%i\n", tail->room->position);
		// ft_printf("tail:%s\n", tail->room->name);
		// ft_printf("room->ant_id:%i\n", tail->room->ants_lst->ant_id);
		if (tail->room->ants_lst != NULL)
		{
			ft_printf("  hello\n");
			ft_printf("  room name:%s\n", tail->room->name);
			if (tail->room->position != END)
			{
				tail->next->room->ants_lst = tail->room->ants_lst;
				ft_printf(ANSI_COLOR_BLUE"  current ant:%i at current room:%s\n", tail->room->ants_lst->ant_id, tail->room->name);
				// ft_printf("  ant:%i at prev room:%s\n", tail->prev->room->ants_lst->ant_id, tail->prev->room->name);
				// ft_printf("  pushed ant:%i to room:%s\n"ANSI_COLOR_RESET, tail->next->room->ants_lst->ant_id, tail->next->room->name);
				if (tail->prev->room->ants_lst == NULL)
				{
					ant_id = get_ant(path, tail->room->ants_lst->ant_id, path_lst);
					// ft_printf("path->ants_amount:%i\n", path->ants_amount);
					ft_printf("  ant_id received:%i\n", ant_id);
					tail->room->ants_lst->ant_id = ant_id;
					ft_printf("  replaced w/ new ant:%i to current room:%s\n", tail->room->ants_lst->ant_id, tail->room->name);
				}
				else if (tail->prev->room->ants_lst != NULL)
				{
					// tail->room->ant_id = tail->prev->room->ant_id;
					tail->room->ants_lst->ant_id = 0;
					ft_printf("  replaced w/ prev ant:%i to current room:%s\n", tail->room->ants_lst->ant_id, tail->room->name);
				}
			}
		}
		tail = tail->prev;
	}
}

void	find_tail(t_paths *path)
{
	t_path_list		*tail;

	tail = path->path_lst;
	while (tail && tail->next != NULL)
	{
		tail = tail->next;
	}
	path->tail = tail;
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
	int				i;

	i = 0;
	ft_print_paths_list(ant_farm);
	ft_print_paths_list_detail(ant_farm);
	path = ant_farm->paths;
	head = ant_farm->paths;
	path_lst = ant_farm->paths->path_lst->next;
	while (i < 7)
	{
		path = head;
		while (path != NULL)
		{
			/* need a function that goes to the end
			**
			*/
			path_lst = path->path_lst->next;
			if (path_lst->room->ants_lst != NULL && (path_lst->room->ants_lst->ant_id != 0 || path->ants_amount == 0))
			{
				ft_printf("going to push ant\n");
				// ft_printf("current room:%s in path:%i\n", path_lst->room->name, path->path_id);
				push_ant(path, &path_lst);
				// ft_printf("path_lst->room->ant_id:%i\n", path_lst->room->ant_id);
				// ft_printf("path_lst->room->next->ant_id:%i\n", path_lst->next->room->ant_id);
			}
			else
			{
				ft_printf("put ant\n");
				ft_put_ant_to_room(&path, &path_lst);
			}
			// ft_printf(ANSI_COLOR_YELLOW"room:%s now occupied by ant:%i\n"ANSI_COLOR_RESET, path_lst->room->name, path_lst->room->ant_id);
			find_tail(path);
			path = path->next;
		}
		ft_printf("\n\n");
		print_ants_to_rooms(ant_farm);
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
// 		ft_printf("L%d-%s ", temp_lst->room->ants->ant_id,
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
// 				ft_printf("L%d-%s ", path_lst->room->ants->ant_id,
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
