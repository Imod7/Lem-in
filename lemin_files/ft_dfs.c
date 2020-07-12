/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dfs.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:37:33 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/12 19:31:48 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** In function delete_edge_from_item we iterate through all the neighbors
** (the neighbor_list) of the previous room from the bottleneck,
** we find the bottleneck room and we remove it.
*/

static void			delete_edge_from_item(t_hash_item *temp_item, char *btl_room)
{
	t_neighbor		*neigbors_lst;
	t_neighbor		*temp;

	ft_printf(" temp_item %s \n", temp_item->room_name);
	neigbors_lst = temp_item->room->neighbors;
	ft_printf(" delete it first from the neightbors list of %s \n", temp_item->room->neighbors->hash_item->room->name);
	while (neigbors_lst != NULL)
	{
		ft_printf(" neighbor %s \n", neigbors_lst->hash_item->room_name);
		if (ft_strcmp(btl_room, neigbors_lst->hash_item->room_name) == 0) 
		// if (temp_item->room_name == neigbors_lst->hash_item->room_name)
		{
			ft_printf("  Deleting neighbor %s \n", neigbors_lst->hash_item->room_name);
			temp = neigbors_lst->next;
			if (temp != NULL)
				ft_printf("  next %s \n", temp->hash_item->room->name);
			if (neigbors_lst->prev != NULL)
				neigbors_lst->prev->next = temp;
			else
			{
				temp_item->room->neighbors = temp;
				ft_printf("  prev is NULL %s \n", \
				temp_item->room->neighbors->hash_item->room->name);
			}
			if ((temp != NULL) && (neigbors_lst != NULL))
				temp->prev = neigbors_lst->prev;
			else if ((temp != NULL) && (neigbors_lst == NULL))
				temp->prev = NULL;
			free(neigbors_lst);
			neigbors_lst = temp;
			if (neigbors_lst != NULL)
				ft_printf("  so now i continue from %s \n", \
				neigbors_lst->hash_item->room_name);
		}
		// if (neigbors_lst != NULL)
		// 	neigbors_lst = neigbors_lst->next;
	}
	// ft_printf(" so now head is %s \n", temp_item->room->neighbors->hash_item->room->neighbors->hash_item->room->name);
	// ft_printf(" so now next of head is %s \n", temp_item->room->neighbors->hash_item->room->neighbors->next->hash_item->room->name);
	// ft_printf(" so now prev of head is %p \n", temp_item->room->neighbors->hash_item->room->neighbors->prev);
	// ft_printf(" so now next of next is %p \n", temp_item->room->neighbors->hash_item->room->neighbors->next->next);
	// ft_printf(" so now prev of next is %s \n", temp_item->room->neighbors->hash_item->room->neighbors->next->prev->hash_item->room->name);
}

/*
** In function cut_edge iterate through the path_list of the bottleneck path,
** finds the bottleneck room and get the previous one.
** I call function delete_edge_from_item to remove the bottleneck room
** from the neighbors of previous room.
*/

void				ft_cut_edge(t_ant_farm *ant_farm, \
								t_paths *tmp_path, \
								t_room *bottleneck_room)
{
	t_path_list		*tmp_pathlst;
	t_hash_item		*room_item;

	tmp_pathlst = tmp_path->path_lst;
	while (tmp_pathlst != NULL)
	{
		if (tmp_pathlst->room->name == bottleneck_room->name)
		{
			room_item = ft_retrieve_hash_item(ant_farm->hash_table, \
			tmp_pathlst->prev->room->name);
			delete_edge_from_item(room_item, bottleneck_room->name);
		}
		tmp_pathlst = tmp_pathlst->next;
	}
}

/*
** In function find_path_cut_edge finds the path_id of the path that the
** bottleneck room belongs to, passes this path to the ft_cut_edge
** function to remove the neighbor and then free this path
*/

void				find_path_cut_edge(t_ant_farm *ant_farm, \
							t_room *bottleneck_room)
{
	t_paths			*tmp_path;

	tmp_path = ant_farm->paths;
	while (tmp_path != NULL)
	{
		if (tmp_path->path_id == bottleneck_room->score)
			break ;
		tmp_path = tmp_path->next;
	}
	ft_cut_edge(ant_farm, tmp_path, bottleneck_room);
	ft_free_path_on_pathid(tmp_path->path_id);
}

/*
** In function ft_check_cut_edge I will add the neighbor if
** it is unexplored  AND (lvl_source bigger or lvl_sink smaller).
** If I couldn't add any neighbors I call function ft_check_cut_edge
*/

size_t				ft_check_cut_edge(t_ant_farm *ant_farm, \
									t_neighbor *neighbors, t_room *temp)
{
	size_t			flag;
	t_neighbor		*neighb_tmp;

	neighb_tmp = neighbors;
	flag = 0;
	while (neighb_tmp != NULL)
	{
		if (neighb_tmp->hash_item->room->state == UNEXPLORED && \
		(temp->level_source <= neighb_tmp->hash_item->room->level_source || \
		temp->level_sink >= neighb_tmp->hash_item->room->level_sink) && \
		neighb_tmp->hash_item->room->score != 0)
		{
			ft_push(&(ant_farm->stack), neighb_tmp->hash_item->room);
			find_path_cut_edge(ant_farm, neighb_tmp->hash_item->room);
			flag += 1;
		}
		neighb_tmp = neighb_tmp->next;
	}
	return (flag);
}

/*
** In function ft_push_neighbors I will add the neighbor if
** it is unexplored  AND (lvl_source bigger or lvl_sink smaller).
** If I couldn't add any neighbors I call function ft_check_cut_edge
*/

size_t				ft_push_neighbors(t_ant_farm *ant_farm, \
									t_neighbor *neighbors, t_room *temp)
{
	size_t			flag;
	t_neighbor		*neighb_tmp;

	neighb_tmp = neighbors;
	// ft_printf(" Neighbors of temp %s , level %d\n", temp->name, temp->level);
	if (temp->position == END)
		return (-1);
	flag = 0;
	while (neighb_tmp != NULL)
	{
		if (neighb_tmp->hash_item->room->position == END)
		{
			ft_push(&(ant_farm->stack), neighb_tmp->hash_item->room);
			flag += 1;
			break ;
		}
		// ft_printf("    neighb %s ", neighb_tmp->hash_item->room->name);
		// ft_printf("    state %d ", neighb_tmp->hash_item->room->state);
		// ft_printf("    level %d \n", neighb_tmp->hash_item->room->level);
		// ft_printf("    position %d \n", neighbors->hash_item->room->position);
		else if (neighb_tmp->hash_item->room->state == UNEXPLORED && \
		(temp->level_source <= neighb_tmp->hash_item->room->level_source || \
		temp->level_sink >= neighb_tmp->hash_item->room->level_sink) && \
		neighb_tmp->hash_item->room->score == 0)
		{
			// ft_printf("neighbor pushed \n");
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
		return (ft_check_cut_edge(ant_farm, neighbors, temp));
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
	// ft_printf("   Last room in the last path : %s \n", path_temp->room->name);
	if (path_temp->room->position != START)
	{
		path_temp->prev->next = NULL;
		free(path_temp);
	}
	// ft_printf(ANSI_COLOR_RESET);
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
	while ((i < ant_farm->max_paths) || \
	(ant_farm->discovered_paths == ant_farm->max_paths))
	// while (i < 2)
	{
		temp = ft_get_start_room(ant_farm->rooms_lst);
		temp->level_source = 0;
		ft_push(&(ant_farm->stack), temp);
		path = ft_create_path(ant_farm);
		// ft_printf("path id %d", path->path_id);
		while (!ft_stack_empty(ant_farm->stack))
		{
			neighbors = ant_farm->stack->room->neighbors;
			ant_farm->stack->room->state = EXPLORED;
			// ft_printf("\n\n >>> i = %d \n", i);
			// ft_printf("  Set room '%s' as explored\n", temp->name);
			// ft_print_stack(ant_farm->stack);
			// ft_printf("  ROOM LIST \n");
			// print_rooms_list(ant_farm->rooms_lst);
			temp = ant_farm->stack->room;
			temp->path = path;
			// ft_printf("Sort neighbors");
			// print_neighbors_list(ant_farm->hash_table);
			ft_sort_neighbors(&neighbors, &temp);
			// ft_printf(" AFTER Sort neighbors");
			// print_neighbors_list(ant_farm->hash_table);
			// exit(0);
			// ft_printf("Next Loop --> i = %d\n", i);
			ft_print_stack(ant_farm->stack);
			ft_printf("  [1] Removing '%s' from top of the stack\n", ant_farm->stack->room->name);
			ft_pop(&(ant_farm->stack));
			result = ft_push_neighbors(ant_farm, neighbors, temp);
			// ft_print_stack(ant_farm->stack);
			if (result > 0)
			{
				ft_printf("  [2.1] Saving '%s' in path\n", temp->name);
				ft_save_room_to_dfs_path(&(path->path_lst), temp);
				path->path_size += 1;
				// ft_printf("path_size %d\n", path->path_size);
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
				// ft_printf("path_size %d room %s\n", path->path_size, temp->name);
				temp->state = UNEXPLORED;
				ft_save_room_to_dfs_path(&(path->path_lst), temp);
				path->path_size += 1;
				while (!ft_stack_empty(ant_farm->stack))
					ft_pop(&(ant_farm->stack));
				break ;
			// }
			}
			else
			{
				ft_printf("BACK TRACKING \n");
				// print_neighbors_list_debug(ant_farm->hash_table);
				// exit(0);
				temp = ft_backtrack(ant_farm);
				ft_printf("  I am in Backtracking '%s' to stack\n", temp->name);
				if ((temp != NULL) && (temp->position != START))
				{
					ft_push(&(ant_farm->stack), temp);
					path->path_size -= 1;
				}
				else if ((temp != NULL) && (temp->position == START))
					path->path_size = 1;
				// else
				// 	ft_printf(ANSI_COLOR_RED_CINA"i %d path id %d path size %d \n"ANSI_COLOR_RESET, i, path->path_id, path->path_size);
				// {
				// 	path->path_size = 0;
				// 	ft_printf("path_size %d room %s\n", path->path_size, temp->name);
				// }
				// ft_printf(ANSI_COLOR_SAND"stack empty? \n"ANSI_COLOR_RESET);
				// ft_print_paths(ant_farm);
			}
			// ft_printf("  [3] Added all neighbors of %s \n", temp->name);
		}
		// ft_printf(ANSI_COLOR_RED_CINA"i %d path id %d path size %d \n"ANSI_COLOR_RESET, i, path->path_id, path->path_size);
		if (((path->path_size == 1) && ((path->path_lst == NULL) || \
		(path->path_lst->room->position != END))) || \
		((path->path_size == 0) && (path->path_lst == NULL)))
			ft_path_del_last(ant_farm);
		// else
		// 	check_if_valid_path(ant_farm);
		// ft_print_paths(ant_farm);
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
