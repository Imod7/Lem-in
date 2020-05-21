/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dfs.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/12 16:39:32 by dominique     #+#    #+#                 */
/*   Updated: 2020/05/21 07:31:28 by dominique     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

size_t				ft_push_neighbors(t_ant_farm *ant_farm, \
									t_neighbor *neighbors, t_room *temp)
{
	size_t			flag;

	if (temp->position == END)
		flag = 1;
	else
		flag = 0;
	while (neighbors != NULL)
	{
		// neighbors->hash_item->room->parent = temp;
		// if (neighbors->hash_item->room->parent)
		// 	ft_printf("neighbor room %s --> parent : %s, state : %d, level : %d, temp lev : %d\n", neighbors->hash_item->room->name, neighbors->hash_item->room->parent->name, neighbors->hash_item->room->state, neighbors->hash_item->room->level, temp->level);
		if ((neighbors->hash_item->room->state == UNEXPLORED) && \
		((neighbors->hash_item->room->level == 0) || \
		(temp->level <= neighbors->hash_item->room->level)))
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
	return (flag);
}

void				ft_dfs(t_ant_farm *ant_farm)
{
	t_room			*temp;
	t_neighbor		*neighbors;
	t_paths			*path;
	size_t			i;

	ant_farm->max_paths = ft_find_maxpaths(ant_farm);
	i = 0;
	// print_rooms_list(ant_farm->rooms_lst);
	// print_neighbors_list(ant_farm->hash_table);
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
			// print_neighbors_list_debug(ant_farm->hash_table);
			// ft_printf("  [2] Removed '%s' from top of the stack\n", ant_farm->stack->room->name);
			ft_pop(&(ant_farm->stack));
			if (ft_push_neighbors(ant_farm, neighbors, temp))
			{
				ft_save_paths_dfs(&(path->path_lst), temp);
				// ft_printf("  [1] Saved '%s' in path\n", temp->name);
			}
			else
			{
				ft_printf(ANSI_COLOR_RED"It's DEAD END : %s ~~ %s \n"ANSI_COLOR_RESET, temp->name, ant_farm->stack->room->name);
			}
			if (temp->position == END)
			{
				temp->state = UNEXPLORED;
				while (!ft_stack_empty(ant_farm->stack))
					ft_pop(&(ant_farm->stack));
				break ;
			}
			// ft_printf("  [3] Added all neighbors of %s \n", temp->name);
			// ft_print_stack(ant_farm->stack);
		}
		i += 1;
	}
	ft_print_paths(ant_farm);
	ft_printf("Max Paths in Graph %d\n", ant_farm->max_paths);
}
