/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bfs_again.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/13 16:01:56 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/29 19:06:12 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static size_t		ft_add_neighbors_of_room_again(t_ant_farm *ant_farm, \
													t_neighbor *neighbors, \
													t_room *front_room)
{
	size_t			flag;
	t_neighbor		*neighb_tmp;

	flag = 0;
	neighb_tmp = neighbors;
	ft_printf(" Neighbors of Front Room %s , lvl_source %d, lvl_sink %d, pos %d\n", front_room->name, front_room->level_source, front_room->level_sink, front_room->position);
	if (front_room->position == START)
		return (-1);
	while (neighb_tmp != NULL)
	{
		// if (neighbors->hash_item->room->state == UNEXPLORED)
		if (neighb_tmp->hash_item->room->state == UNEXPLORED && \
		(front_room->level_source >= neighb_tmp->hash_item->room->level_source || \
		front_room->level_sink <= neighb_tmp->hash_item->room->level_sink) && \
		neighb_tmp->hash_item->room->score == 0)
		{
			// ft_printf("    neighb %s ", neighb_tmp->hash_item->room->name);
			// ft_printf("    state %d ", neighb_tmp->hash_item->room->state);
			// ft_printf("    lvl_source %d, ", neighb_tmp->hash_item->room->level_source);
			// ft_printf("    lvl_sink %d, ", neighb_tmp->hash_item->room->level_sink);
			// ft_printf("    score %d ", neighb_tmp->hash_item->room->score);
			// ft_printf("    -> Enqueued room %s state : %d\n", neighbors->hash_item->room->name, neighbors->hash_item->room->state);
			ft_enqueue(ant_farm->queue, neighb_tmp->hash_item->room);
			neighb_tmp->hash_item->room->parent = ant_farm->queue->front->room;
			flag += 1;
			ft_printf("parent of room %s is %s\n", neighb_tmp->hash_item->room->name, neighb_tmp->hash_item->room->parent->name);
			// ft_print_queue(ant_farm->queue);
			// ft_printf("neighbors of room %s \n", ant_farm->queue->front->room->name);
			// neighbors->hash_item->room->parent = ant_farm->queue->front->room;
			// if (flag == 0 && neighbors->hash_item->room->level_source == 0)
			// 		neighbors->hash_item->room->level_source = \
			// 		neighbors->hash_item->room->parent->level_source + 1;
			// else if (flag == 1 && neighbors->hash_item->room->level_sink == 0)
			// 	neighbors->hash_item->room->level_sink = \
			// 	neighbors->hash_item->room->parent->level_sink + 1;
			// ft_printf("neighbor room %s level : %d , parent : %s level : %d \n", neighbors->hash_item->room->name, neighbors->hash_item->room->level, neighbors->hash_item->room->parent->name, neighbors->hash_item->room->parent->level);
			// ft_print_paths(ant_farm);
			// ft_printf("level : %d\n", neighbors->hash_item->room->level);
		}
		neighb_tmp = neighb_tmp->next;
	}
	if (flag == 0)
	{
		return (ft_check_cut_edge_bfs(ant_farm, neighbors, front_room));
		// if (flag == 0)
		// 	return (flag);
	}
	return (flag);
}

void				ft_bfs_again(t_ant_farm *ant_farm, size_t flag)
{
	t_room			*temp;
	t_neighbor		*neighbors;
	size_t			i;
	int				result;

	ant_farm->max_paths = ft_find_maxpaths(ant_farm);
	ant_farm->queue = (t_queue *)ft_memalloc(sizeof(t_queue));
	if (flag == 0)
		temp = ft_get_start_room(ant_farm->rooms_lst);
	else
		temp = ft_get_end_room(ant_farm);
	ft_enqueue(ant_farm->queue, temp);
	// if (ant_farm->queue->front->room->position == START)
	// 	ant_farm->queue->front->room->parent = NULL;
	ft_printf("parent is %p of END room %s\n", ant_farm->queue->front->room->parent, ant_farm->queue->front->room->name);
	i = 0;
	// ft_printf("max paths = %d \n", ant_farm->max_paths);
	// while (i < ant_farm->max_paths)
	while (i < 5)
	{
		while (!ft_queue_is_empty(ant_farm->queue))
		{
			neighbors = ant_farm->queue->front->room->neighbors;
			result = ft_add_neighbors_of_room_again(ant_farm, neighbors, \
									ant_farm->queue->front->room);
			if (result == -1)
				ft_printf("\nArrived at start\n");
			ft_printf("Removing front of queue %s\n", ant_farm->queue->front->room->name);
			ft_dequeue(ant_farm->queue);
			// ft_print_queue(ant_farm->queue);
		}
		if (flag == 2)
		{
			ft_printf("Saves the path\n");
			ft_save_paths_bfs(ant_farm, 2);
		}
		ft_bfs_reset(ant_farm);
		if (flag == 0)
			temp = ft_get_start_room(ant_farm->rooms_lst);
		else
			temp = ft_get_end_room(ant_farm);
		if (temp->state == COMPLETED)
			ft_enqueue(ant_farm->queue, temp);
		i += 1;
	}
	ft_bfs_fullreset(ant_farm);
	ft_paths_discovered(ant_farm);
	// print_neighbors_list_debug(ant_farm->hash_table);
	// ft_printf("Max Paths in Graph %d\n", ant_farm->max_paths);
}
