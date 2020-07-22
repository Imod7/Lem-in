/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dfs_from_sink.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:37:33 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/21 11:51:04 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** In function ft_push_neighbors I will add the neighbor if
** it is unexplored  AND (lvl_source bigger or lvl_sink smaller).
** If I couldn't add any neighbors I call function ft_check_cut_edge
** First check if neighbor lvl_source > temp-lvl_source AND
** neighbor-lvl_source < temp_lvl_source
** and then the equals because we want to prioritize and take 
** first the ones that are closer to the start
*/

size_t				ft_push_neighbors_dfs_sink(t_ant_farm *ant_farm, \
									t_neighbor *neighbors, t_room *temp)
{
	size_t			flag;
	t_neighbor		*neighb_tmp;

	neighb_tmp = neighbors;
	ft_printf(" Neighbors of temp %s , level_source %d, lvl_sink %d\n", temp->name, temp->level_source, temp->level_sink);
	if (temp->position == START)
		return (-1);
	flag = 0;
	while (neighb_tmp != NULL)
	{
		ft_printf("    neighb %s ", neighb_tmp->hash_item->room->name);
		ft_printf("    state %d ", neighb_tmp->hash_item->room->state);
		ft_printf("    level_source %d, ", neighb_tmp->hash_item->room->level_source);
		ft_printf("    level_sink %d, ", neighb_tmp->hash_item->room->level_sink);
		ft_printf("    score %d \n", neighb_tmp->hash_item->room->score);
		if (neighb_tmp->hash_item->room->position == START)
		{
			ft_push(&(ant_farm->stack), neighb_tmp->hash_item->room);
			flag += 1;
			break ;
		}
		else if ((neighb_tmp->hash_item->room->state == UNEXPLORED && \
		(temp->level_source > neighb_tmp->hash_item->room->level_source || \
		temp->level_sink < neighb_tmp->hash_item->room->level_sink) && \
		neighb_tmp->hash_item->room->score == 0) ||
		(neighb_tmp->hash_item->room->state == UNEXPLORED && \
		temp->position == END && neighb_tmp->hash_item->room->score == 0))
		{
			ft_printf("  neighbor pushed %s\n", neighb_tmp->hash_item->room->name);
			// neighbors->hash_item->room->parent = ant_farm->paths->path_lst->room;
			ft_push(&(ant_farm->stack), neighb_tmp->hash_item->room);
			// neighbors->hash_item->room->parent = ant_farm->stack->room;
			// if (neighbors->hash_item->room->parent)
			// 	neighbors->hash_item->room->level = neighbors->hash_item->room->parent->level + 1;
			flag += 1;
		}
		else if (neighb_tmp->hash_item->room->state == UNEXPLORED && \
		(temp->level_source >= neighb_tmp->hash_item->room->level_source || \
		temp->level_sink <= neighb_tmp->hash_item->room->level_sink) && \
		neighb_tmp->hash_item->room->score == 0)
		{
			ft_printf("  neighbor pushed %s\n", neighb_tmp->hash_item->room->name);
			// neighbors->hash_item->room->parent = ant_farm->paths->path_lst->room;
			ft_push(&(ant_farm->stack), neighb_tmp->hash_item->room);
			// neighbors->hash_item->room->parent = ant_farm->stack->room;
			// if (neighbors->hash_item->room->parent)
			// 	neighbors->hash_item->room->level = neighbors->hash_item->room->parent->level + 1;
			flag += 1;
		}
		neighb_tmp = neighb_tmp->next;
	}
	if (flag == 0)
		return (ft_check_cut_edge_dfs_sink(ant_farm, neighbors, temp));
	// ft_printf("flag = %d \n", flag);
	return (flag);
}

void				ft_save_room_to_dfs_path_from_sink(t_path_list **path_lst, \
											t_room *room)
{
	t_path_list		*path;
	t_path_list		*last_node;
	t_path_list		*prevlast_node;

	last_node = *path_lst;
	prevlast_node = *path_lst;
	ft_printf("Saving room %s to path\n", room->name);
	// while (last_node != NULL)
	// {
	// 	prevlast_node = last_node;
	// 	// ft_printf("prev room  %s \n", prevlast_node->room->name);
	// 	last_node = last_node->next;
	// }
	path = (t_path_list *)ft_memalloc(sizeof(t_path_list));
	path->room = room;
	// if (prevlast_node != NULL)
	// 	path->room->parent = prevlast_node->room;
	// else
	// 	path->room->parent = NULL;
	// ft_pathlst_addend(path_lst, path);
	ft_pathlst_addstart(path_lst, path);
	// ft_pathlst_addend(&(new_path->path_lst), path_list);
}

void				ft_dfs_from_sink(t_ant_farm *ant_farm)
{
	t_room			*temp;
	t_neighbor		*neighbors;
	t_paths			*path;
	size_t			i;
	int				result;

	ant_farm->max_paths = ft_find_maxpaths(ant_farm);
	i = 0;
	while ((i < ant_farm->max_paths) || \
	(ant_farm->discovered_paths == ant_farm->max_paths))
	// while (i < 10)
	{
		// temp = ft_get_start_room(ant_farm->rooms_lst);
		temp = ft_get_end_room(ant_farm);
		temp->level_source = 0;
		ft_push(&(ant_farm->stack), temp);
		path = ft_create_path(ant_farm);
		path->run = ant_farm->paths->run + 1;
		ft_printf("\n\n >>> i = %d \n", i);
		ft_printf("dfs run>>path id %d", path->path_id);
		while (!ft_stack_empty(ant_farm->stack))
		{
			neighbors = ant_farm->stack->room->neighbors;
			ant_farm->stack->room->state = EXPLORED;
			ft_printf("\n\n >>> max paths = %d \n", ant_farm->max_paths);
			// ft_printf("  Set room '%s' as explored\n", temp->name);
			// ft_print_stack(ant_farm->stack);
			// ft_printf("  ROOM LIST \n");
			// print_rooms_list(ant_farm->rooms_lst);
			temp = ant_farm->stack->room;
			temp->path = path;
			// ft_printf("Sort neighbors");
			// print_neighbors_list(ant_farm->hash_table);
			ft_sort_neighbors(&neighbors, &temp, 1);
			ft_sort_neighbors(&neighbors, &temp, 0);
			// ft_printf(" AFTER Sort neighbors");
			// print_neighbors_list(ant_farm->hash_table);
			// exit(0);
			// ft_printf("Next Loop --> i = %d\n", i);
			// ft_print_stack(ant_farm->stack);
			ft_printf("  [1] Removing '%s' from top of the stack\n", ant_farm->stack->room->name);
			ft_pop(&(ant_farm->stack));
			result = ft_push_neighbors_dfs_sink(ant_farm, neighbors, temp);
			// ft_print_stack(ant_farm->stack);
			if (result > 0)
			{
				ft_printf("  [2.1] Saving '%s' in path\n", temp->name);
				ft_save_room_to_dfs_path_from_sink(&(path->path_lst), temp);
				ft_print_paths(ant_farm);
				path->path_size += 1;
				// ft_printf("path_size %d\n", path->path_size);
				// ft_print_paths(ant_farm);
				// if (ft_strcmp("f1", temp->name) == 0)
				// {
					// print_rooms_list(ant_farm->rooms_lst);
				// 	print_neighbors_list(ant_farm->hash_table);
				// }
			}
			else if (result == -1)
			{
			// 	if (temp->position == END)
			// {
				// ft_printf(ANSI_COLOR_SAND"end room \n"ANSI_COLOR_RESET);
				// ft_printf("path_size %d room %s\n", path->path_size, temp->name);
				temp->state = UNEXPLORED;
				ft_save_room_to_dfs_path_from_sink(&(path->path_lst), temp);
				path->path_size += 1;
				while (!ft_stack_empty(ant_farm->stack))
					ft_pop(&(ant_farm->stack));
				break ;
			// }
			}
			// else
			// {
			// 	ft_printf("BACK TRACKING \n");
			// 	// print_neighbors_list_debug(ant_farm->hash_table);
			// 	// exit(0);
			// 	temp = ft_backtrack(ant_farm);
			// 	ft_printf("  I am in Backtracking '%s' to stack\n", temp->name);
			// 	if ((temp != NULL) && (temp->position != START))
			// 	{
			// 		ft_push(&(ant_farm->stack), temp);
			// 		path->path_size -= 1;
			// 	}
			// 	else if ((temp != NULL) && (temp->position == START))
			// 		path->path_size = 1;
			// 	// else
			// 	// 	ft_printf(ANSI_COLOR_RED_CINA"i %d path id %d path size %d \n"ANSI_COLOR_RESET, i, path->path_id, path->path_size);
			// 	// {
			// 	// 	path->path_size = 0;
			// 	// 	ft_printf("path_size %d room %s\n", path->path_size, temp->name);
			// 	// }
			// 	// ft_printf(ANSI_COLOR_SAND"stack empty? \n"ANSI_COLOR_RESET);
			// 	// ft_print_paths(ant_farm);
			// }
			// ft_printf("  [3] Added all neighbors of %s \n", temp->name);
		}
		// ft_printf(ANSI_COLOR_RED_CINA"i %d path id %d path size %d \n"ANSI_COLOR_RESET, i, path->path_id, path->path_size);
		// if (((path->path_size == 1) && ((path->path_lst == NULL) || \
		// (path->path_lst->room->position != END))) || \
		// ((path->path_size == 0) && (path->path_lst == NULL)))
		if (path->path_size == 1 || path->path_lst == NULL || \
		path->path_lst->room->position != END || \
		(path->path_size == 0 && path->path_lst == NULL))
		{
			ft_printf("Deleting last path \n");
			ft_path_del_last(ant_farm);
		}
		// else
		// 	check_if_valid_path(ant_farm);
		ft_sort_paths_on_size(ant_farm);
		ft_printf("Print DFS paths \n");
		ft_print_paths(ant_farm);
		ft_printf("Print DFS paths sizes\n");
		ft_print_paths_sizes(ant_farm);
		// ft_print_stack(ant_farm->stack);
		ft_paths_discovered(ant_farm);
		i += 1;
		// ft_print_paths(ant_farm);
	}
	// ft_printf("END of DFS");
	// ft_print_paths(ant_farm);
	ft_sort_paths_on_size(ant_farm);
	// ft_print_paths(ant_farm);
	ft_paths_discovered(ant_farm);
	// ft_printf("Max Paths in Graph %d\n", ant_farm->max_paths);
}
