/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dfs.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:37:33 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/06/19 14:16:16 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

size_t				ft_push_neighbors(t_ant_farm *ant_farm, \
									t_neighbor *neighbors, t_room *temp)
{
	size_t			flag;

	// print_rooms_list(ant_farm->rooms_lst);
	// ft_printf(ANSI_COLOR_GREEN_EMER"temp %s , level %d\n"ANSI_COLOR_RESET, temp->name, temp->level);
	if (temp->position == END)
		return (-1);
	flag = 0;
	while (neighbors != NULL)
	{
		// ft_printf(ANSI_COLOR_GREEN_EMER"neighb %s "ANSI_COLOR_RESET, neighbors->hash_item->room->name);
		// ft_printf("state %d ", neighbors->hash_item->room->state);
		// ft_printf("level %d \n", neighbors->hash_item->room->level);
		// ft_printf("position %d \n"ANSI_COLOR_RESET, neighbors->hash_item->room->position);
		// neighbors->hash_item->room->parent = temp;
		// if (neighbors->hash_item->room->parent)
		// 	ft_printf("neighbor room %s --> parent : %s, state : %d, level : %d, temp lev : %d\n", neighbors->hash_item->room->name, neighbors->hash_item->room->parent->name, neighbors->hash_item->room->state, neighbors->hash_item->room->level, temp->level);
		if (((neighbors->hash_item->room->state == UNEXPLORED) && \
		(temp->level <= neighbors->hash_item->room->level)) || \
		(neighbors->hash_item->room->position == END))
		{
			// ft_printf("neighbor pushed \n");
			// neighbors->hash_item->room->parent = ant_farm->paths->path_lst->room;
			ft_push(&(ant_farm->stack), neighbors->hash_item->room);
			// neighbors->hash_item->room->parent = ant_farm->stack->room;
			// if (neighbors->hash_item->room->parent)
			// 	neighbors->hash_item->room->level = neighbors->hash_item->room->parent->level + 1;
			flag += 1;
		}
		neighbors = neighbors->next;
	}
	// ft_printf("flag = %d \n", flag);
	return (flag);
}

t_room				*ft_remove_last_room_from_path(t_ant_farm *ant_farm)
{
	t_path_list		*path_temp;
	// t_hash_item		*room_item;
	t_room			*room;
	t_paths			*paths;

	paths = ant_farm->paths;
	while (paths != NULL)
	{
		// ft_printf("Path ID %d : ", paths->path_id);
		path_temp = paths->path_lst;
		while (path_temp != NULL)
		{
			// ft_printf("path list not NULL  \n");
			if (path_temp->next == NULL)
				break ;
			else
				path_temp = path_temp->next;
		}
		paths = paths->next;
		// ft_printf("\n");
		// ft_printf("next path %p \n", paths);
	}
	// ft_printf("----------------------\n");
	// ft_printf("Last room in the last path : %s \n", path_temp->room->name);
	if (path_temp->room->position != START)
	{
		path_temp->prev->next = NULL;
		free(path_temp);
	}
	ft_printf(ANSI_COLOR_RESET);
	// room_item = ft_retrieve_hash_item(ant_farm->hash_table, path_temp->room->name);
	room = path_temp->room;
	// ft_printf("Returning room : %s \n", room->name);
	// ft_print_paths(ant_farm);
	return (room);
}

t_room				*ft_backtrack(t_ant_farm *ant_farm)
{
	if (ant_farm->stack == NULL)
		return (NULL);
	// ft_print_stack(ant_farm->stack);
	// ft_printf(ANSI_COLOR_RED_CINA"   [2.2] It's DEAD END : %s ~~ %s \n"ANSI_COLOR_RESET, temp->name, ant_farm->stack->room->name);
	// ft_print_paths(ant_farm);
	// Remove the last node from the last path
	return (ft_remove_last_room_from_path(ant_farm));
	// Push it to the stack
}

void				ft_dfs(t_ant_farm *ant_farm)
{
	t_room			*temp;
	t_neighbor		*neighbors;
	t_paths			*path;
	size_t			i;
	int				result;

	ant_farm->max_paths = ft_find_maxpaths(ant_farm);
	i = 0;
	// print_neighbors_list_debug(ant_farm->hash_table);
	while (i < ant_farm->max_paths)
	{
		temp = ft_get_start_room(ant_farm->rooms_lst);
		temp->level = 0;
		ft_push(&(ant_farm->stack), temp);
		path = ft_create_path_list(ant_farm);
		while (!ft_stack_empty(ant_farm->stack))
		{
			neighbors = ant_farm->stack->room->neighbors;
			ant_farm->stack->room->state = EXPLORED;
			temp = ant_farm->stack->room;
			temp->path = path;
			ft_sort_neighbors(&neighbors, &temp);
			// ft_printf("Next Loop --> i = %d\n", i);
			// ft_print_stack(ant_farm->stack);
			// ft_printf("  [1] Removing '%s' from top of the stack\n", ant_farm->stack->room->name);
			ft_pop(&(ant_farm->stack));
			result = ft_push_neighbors(ant_farm, neighbors, temp);
			// ft_print_stack(ant_farm->stack);
			if (result > 0)
			{
				// ft_printf("  [2.1] Saving '%s' in path\n", temp->name);
				ft_save_room_to_dfs_path(&(path->path_lst), temp);
				path->path_size += 1;
				// ft_print_paths(ant_farm);
				// if (ft_strcmp("f1", temp->name) == 0)
				// {
				// 	print_rooms_list(ant_farm->rooms_lst);
				// 	print_neighbors_list(ant_farm->hash_table);
				// }
			}
			else if (result == -1)
			{
			// 	if (temp->position == END)
			// {
				// ft_printf(ANSI_COLOR_SAND"end room \n"ANSI_COLOR_RESET);
				temp->state = UNEXPLORED;
				ft_save_room_to_dfs_path(&(path->path_lst), temp);
				while (!ft_stack_empty(ant_farm->stack))
					ft_pop(&(ant_farm->stack));
				break ;
			// }
			}
			else
			{
				// ft_printf(ANSI_COLOR_SAND"BACK TRACKING \n"ANSI_COLOR_RESET);
				// exit(0);
				temp = ft_backtrack(ant_farm);
				// ft_printf("  Pushing '%s' to stack\n", temp->name);
				if ((temp != NULL) && (temp->position != START))
					ft_push(&(ant_farm->stack), temp);
				// ft_printf(ANSI_COLOR_SAND"stack empty? \n"ANSI_COLOR_RESET);
				// ft_print_stack(ant_farm->stack);
			}
			// ft_printf("  [3] Added all neighbors of %s \n", temp->name);
			// ft_print_stack(ant_farm->stack);
		}
		// ft_print_paths(ant_farm);
		i += 1;
	}
	ft_print_paths(ant_farm);
	ft_paths_discovered(ant_farm);
	ft_printf("Max Paths in Graph %d\n", ant_farm->max_paths);
}
