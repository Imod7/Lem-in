/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bfs_sink.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:12:05 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/08 18:35:15 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** Adding all neighbors of the room that is in the front of our queue
** We also update the parent room at the same time and the level_source
** (leveling from source to sink) of the neighbor.
*/

static size_t		ft_add_neighbors_of_room(t_ant_farm *ant_farm, \
											t_neighbor *neighbors, \
											t_room *front_room, \
											size_t current_run)
{
	size_t			flag;
	t_neighbor		*neighb_tmp;

	flag = 0;
	neighb_tmp = neighbors;
	// ft_printf(" Neighbors of Front Room %s , lvl_source %d, lvl_sink %d, pos %d\n", front_room->name, front_room->level_source, front_room->level_sink, front_room->position);
	if (front_room->position == START)
		return (-1);
	while (neighb_tmp != NULL)
	{
		// ft_printf("    neighb %s ", neighb_tmp->hash_item->room->name);
		// ft_printf("    state %d ", neighb_tmp->hash_item->room->state);
		// ft_printf("    lvl_source %d, ", neighb_tmp->hash_item->room->level_source);
		// ft_printf("    lvl_sink %d, ", neighb_tmp->hash_item->room->level_sink);
		// ft_printf("    score %d ", neighb_tmp->hash_item->room->score);
		if (neighb_tmp->hash_item->room->state == UNEXPLORED && \
		neighb_tmp->hash_item->room->score == 0 && \
		neighb_tmp->hash_item->room->level_source != 0)
		{
			// ft_printf("neighbor room %s state : %d\n", neighbors->hash_item->room->name, neighbors->hash_item->room->state);
			ft_enqueue(ant_farm->queue, neighb_tmp->hash_item->room);
			// ft_printf(ANSI_COLOR_GREEN_BOLD"    -> Enqueued room %s state : %d"ANSI_COLOR_RESET, neighb_tmp->hash_item->room->name, neighb_tmp->hash_item->room->state);
			// ft_print_queue(ant_farm->queue);
			// ft_printf("neighbors of room %s \n", ant_farm->queue->front->room->name);
			neighb_tmp->hash_item->room->parent = ant_farm->queue->front->room;
			neighb_tmp->hash_item->room->parent->run = current_run;
			// ft_printf("\nparent of room %s is %s", neighb_tmp->hash_item->room->name, neighb_tmp->hash_item->room->parent->name);
			// if (neighb_tmp->hash_item->room->level_source == 0)
			// 		neighb_tmp->hash_item->room->level_source = \
			// 		neighb_tmp->hash_item->room->parent->level_source + 1;
			flag += 1;
		}
		// ft_printf(" \n");
		neighb_tmp = neighb_tmp->next;
	}
	if (flag == 0)
	{
		// ft_printf("\n final flag = %d \n", flag);
		// ft_printf(ANSI_COLOR_RED_CINA"  No neighbors that are not in a path added ! \n"ANSI_COLOR_RESET);
		// ft_printf(ANSI_COLOR_RED_CINA"  Will check if exist neighbors that are in a path ! \n"ANSI_COLOR_RESET);
		return (ft_check_min_cut_sink(ant_farm, neighbors, front_room, current_run));
	}
	return (flag);
}

/*
** We run the bfs algorithm traversing the graph from source to sink,
** find the shortest paths and save them and also to set the level_source
** of all the rooms (leveling from source to sink).
** Before adding the neighbors of each room to the queue I sort
** the neighbors based on the level_sink
*/

size_t				ft_bfs_sink(t_ant_farm *ant_farm, size_t run)
{
	t_room			*temp;
	t_neighbor		*neighbors;
	int				result;
	size_t			i;
	size_t			flag;

	ant_farm->max_paths = ft_find_maxpaths(ant_farm);
	ant_farm->queue = (t_queue *)ft_memalloc(sizeof(t_queue));
	temp = ft_get_end_room(ant_farm);
	ft_enqueue(ant_farm->queue, temp);
	temp->parent = NULL;
	i = 0;
	while (i < ant_farm->max_paths)
	{
		flag = 0;
		while (!ft_queue_is_empty(ant_farm->queue))
		{
			neighbors = ant_farm->queue->front->room->neighbors;
			ft_sort_neighbors(&neighbors, &(ant_farm->queue->front->room), 0);
			ft_sort_neighbors(&neighbors, &(ant_farm->queue->front->room), 1);
			result = ft_add_neighbors_of_room(ant_farm, neighbors, \
									ant_farm->queue->front->room, run);
			if (result == -1)
			{
				// ft_printf("\nArrived at %s room\n", ant_farm->queue->front->room->name);
				flag = 1;
			}
			ft_dequeue(ant_farm->queue);
			// ft_printf("Removing front of queue \n");
			// ft_print_queue(ant_farm->queue);
		}
		// ft_printf(ANSI_COLOR_RED_CINA"result from neighbors result = %d - flag %d\n"ANSI_COLOR_RESET, result, flag);
		if (flag == 1)
			ft_save_paths_bfs(ant_farm, 0, run);
		ft_bfs_reset(ant_farm);
		temp = ft_get_end_room(ant_farm);
		if (temp->state == COMPLETED)
			ft_enqueue(ant_farm->queue, temp);
		// ft_print_paths(ant_farm);
		i += 1;
	}
	ft_bfs_fullreset(ant_farm);
	ft_paths_discovered(ant_farm);
	return (ant_farm->discovered_paths);
}
