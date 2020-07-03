/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ants_move.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:11:32 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/02 11:43:13 by svan-svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void		print_line(t_ant_farm *ant_farm)
{
	t_paths *temp;
	t_ants *end_lst;
	t_path_list *temp_lst;

	temp = ant_farm->paths;
	while (temp != NULL)
	{
		temp_lst = temp->tail;
		while (temp_lst != NULL)
		{
			if (temp_lst->room->ants_lst != NULL && temp_lst->room->position != END)
				ft_printf(ANSI_COLOR_GREEN_EMER"L%i-%s "ANSI_COLOR_RESET, temp_lst->room->ants_lst->ant_id, temp_lst->room->name);
			else if (temp_lst->room->ants_lst != NULL)
			{
				end_lst = temp_lst->room->ants_lst;
				while (end_lst != NULL)
				{
					if (end_lst->path->path_id == temp->path_id)
						ft_printf(ANSI_COLOR_YELLOW"L%i-%s "ANSI_COLOR_RESET, end_lst->ant_id, temp_lst->room->name);
					end_lst = end_lst->next;
				}
			}
			temp_lst = temp_lst->prev;
		}
		temp = temp->next;
	}
	if (ant_farm->paths->tail->room->ants_lst != NULL)
	{
		free(ant_farm->paths->tail->room->ants_lst);
		ant_farm->paths->tail->room->ants_lst = NULL;
	}
	ft_printf("\n");
	// ft_printf("finished printing\n"ANSI_COLOR_RESET);
}


void	ft_put_ant_to_room(t_paths **path, t_path_list **path_lst)
{
	t_ants *temp;

	(*path)->ants_amount -= 1;
	temp = (t_ants *)ft_memalloc(sizeof(t_ants));
	temp->ant_id = (*path)->ants_lst->ant_id;
	temp->path = *path;
	ft_printf(" >>> we are adding ant %d to room %s \n", temp->ant_id, (*path_lst)->room->name);
	ft_add_ants_to_list(&((*path_lst)->room->ants_lst), temp);
	// (*path_lst)->room->ant_id = (*path)->ants_lst->ant_id;
	// ft_printf("L:%i-%s\n", (*path_lst)->room->ants_lst->ant_id, (*path_lst)->room->name);
}

void				ft_add_ants_to_list(t_ants **lst, t_ants *new)
{
	t_ants			*temp;

	if (*lst == NULL)
	{
		// ft_printf("adding ant id %d to antslst\n", new->ant_id);
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

t_ants		*get_ant(t_paths *path, int ant_id, t_path_list **path_lst)
{
	t_ants *temp;
	t_ants *temp1;

	temp = path->ants_lst;
	while (temp->next != NULL)
	{
		// ft_printf("ant_id:%i\n", path->ants_lst->ant_id);
		if (temp->ant_id == ant_id)
		{
			ft_printf(" >>> we found ant %d to room %s \n", temp->ant_id, (*path_lst)->room->name);
			path->ants_amount -= 1;
			temp1 = (t_ants *)ft_memalloc(sizeof(t_ants));
			temp1->ant_id = temp->next->ant_id;
			temp1->path = path;
			// ft_put_ant_to_room(&path, path_lst);
			// path->ants_amount -= 1;
			return (temp1);
		}
		temp = temp->next;
	}
	return (NULL);
}

void		push_ant(t_paths *path, t_path_list **path_lst, t_ant_farm *ant_farm)
{
	t_path_list *tail;
	t_ants		*ant;

	(void)path_lst;
	tail = path->tail;
	ft_printf("\n\n");
	ft_printf("  inside push ant path_id:%i\n", path->path_id);
	(void)ant_farm;
	// ft_printf("ptr tail:%p\n", tail);
	// ft_printf("tail:%s\n", tail->room->name);
	while (tail->room->position != START)
	{
		// ft_printf("position:%i\n", tail->room->position);
		// ft_printf("tail:%s\n", tail->room->name);
		// ft_printf("room->ant_id:%i\n", tail->room->ants_lst->ant_id);
		if (tail->room->ants_lst != NULL)
		{
			// ft_printf("  room name:%s\n", tail->room->name);
			if (tail->room->position != END)
			{
				ft_printf("we are adding this room's %s list %p to next %s that has ants_lst %p ", tail->room->name,tail->room->ants_lst, tail->next->room->name, tail->next->room->ants_lst);
				ft_add_ants_to_list(&(tail->next->room->ants_lst), tail->room->ants_lst);
				ft_printf(ANSI_COLOR_BLUE"  ant:%i at next room:%s\n", tail->next->room->ants_lst->ant_id, tail->next->room->name);
				ft_printf("  current ant:%i at current room:%s\n", tail->room->ants_lst->ant_id, tail->room->name);
				if (tail->prev->room->ants_lst == NULL)
				{
					ft_print_ants(ant_farm);
					ant = get_ant(path, tail->room->ants_lst->ant_id, path_lst);
					if (ant)
						ft_printf("get ant %d \n", ant->ant_id);
					ft_print_ants(ant_farm);
					// ft_printf("path->ants_amount:%i\n", path->ants_amount);
					// ft_printf("  ant_id received:%i\n", ant_id);
					tail->room->ants_lst = ant;
					if (ant)
						ft_printf("  replaced w/ new ant:%i to current room:%s\n", tail->room->ants_lst->ant_id, tail->room->name);
				}
				else if (tail->prev->room->ants_lst != NULL)
				{
					// tail->room->ants_lst->ant_id = tail->prev->room->ant_id;
					tail->room->ants_lst = NULL;
					ft_printf("  replaced w/ prev antlst: NULL to current room:%s\n", tail->room->name);
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
		ft_printf("ITERATION %d\n", i + 1);
		if (i == 7)
			exit(1);
		path = ant_farm->paths;
		while (path != NULL)
		{
			/* need a function that goes to the end
			**
			*/
			path_lst = path->path_lst->next;
			ft_printf("room:%s ptr:%p\n", path_lst->room->name, path_lst->room->ants_lst);
			if (i != 0)
			{
				ft_printf("inside move ants path_id:%i\n", path->path_id);
				ft_printf("going to push ant\n");
				// ft_printf("current room:%s in path:%i\n", path_lst->room->name, path->path_id);
				push_ant(path, &path_lst, ant_farm);
			}
			else if (i == 0)
			{
				ft_printf("put ant\n");
				ft_put_ant_to_room(&path, &path_lst);
			}
			// ft_printf(ANSI_COLOR_YELLOW"room:%s now occupied by ant:%i\n"ANSI_COLOR_RESET, path_lst->room->name, path_lst->room->ant_id);
			find_tail(path);
			path = path->next;
		}
		ft_printf("\n");
		print_ants_to_rooms(ant_farm);
		print_line(ant_farm);
		i++;
	}
}
