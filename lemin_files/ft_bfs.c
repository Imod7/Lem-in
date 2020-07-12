/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bfs.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:12:05 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/12 14:28:23 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void				ft_reset(t_ant_farm *ant_farm)
{
	t_room			*temp;

	temp = ant_farm->rooms_lst;
	while (temp != NULL)
	{
		if (temp->state != COMPLETED)
			temp->state = UNEXPLORED;
		temp = temp->next;
	}
}

void				ft_fullreset(t_ant_farm *ant_farm)
{
	t_room			*temp;

	temp = ant_farm->rooms_lst;
	while (temp != NULL)
	{
		temp->state = UNEXPLORED;
		temp = temp->next;
	}
}

/*
** Adding all neighbors of the room that is in the front of our queue
** We also update the parent room at the same time and the level
** of the neighbor
*/

static void					ft_add_neighbors_of_room(t_ant_farm *ant_farm, \
														t_neighbor *neighbors, \
														size_t flag)
{
	while (neighbors != NULL)
	{
		if (neighbors->hash_item->room->state == UNEXPLORED)
		{
			// ft_printf("neighbor room %s state : %d\n", neighbors->hash_item->room->name, neighbors->hash_item->room->state);
			ft_enqueue(ant_farm->queue, neighbors->hash_item->room);
			// ft_printf("enqueud room %s \n", neighbors->hash_item->room->name);
			// ft_print_queue(ant_farm->queue);
			// ft_printf("neighbors of room %s \n", ant_farm->queue->front->room->name);
			neighbors->hash_item->room->parent = ant_farm->queue->front->room;
			if (flag == 0 && neighbors->hash_item->room->level_source == 0)
					neighbors->hash_item->room->level_source = \
					neighbors->hash_item->room->parent->level_source + 1;
			else if (flag == 1 && neighbors->hash_item->room->level_sink == 0)
				neighbors->hash_item->room->level_sink = \
				neighbors->hash_item->room->parent->level_sink + 1;
			// ft_printf("neighbor room %s level : %d , parent : %s level : %d \n", neighbors->hash_item->room->name, neighbors->hash_item->room->level, neighbors->hash_item->room->parent->name, neighbors->hash_item->room->parent->level);
			// ft_print_paths(ant_farm);
			// ft_printf("level : %d\n", neighbors->hash_item->room->level);
		}
		neighbors = neighbors->next;
	}
}

/*
** If ft_bfs is called with flag = 0 then it means we run the bfs algorithm
** traversing the graph from source to sink, find the shortest paths and
** save them and also to set the level_source of all the rooms
** (leveling from source to sink).
** If ft_bfs is called with flag = 1 it means we run the bfs algorithm
** traversing the graph from sink to source and set the level_sink of all
** the rooms (leveling from sink to source)
*/

void				ft_bfs(t_ant_farm *ant_farm, size_t flag)
{
	t_room			*temp;
	t_neighbor		*neighbors;
	size_t			i;

	ant_farm->max_paths = ft_find_maxpaths(ant_farm);
	ant_farm->queue = (t_queue *)ft_memalloc(sizeof(t_queue));
	if (flag == 0)
		temp = ft_get_start_room(ant_farm->rooms_lst);
	else
		temp = ft_get_end_room(ant_farm);
	ft_enqueue(ant_farm->queue, temp);
	i = 0;
	// ft_printf("max paths = %d \n", ant_farm->max_paths);
	while (i < ant_farm->max_paths)
	// while (i < 1)
	{
		while (!ft_queue_is_empty(ant_farm->queue))
		{
			neighbors = ant_farm->queue->front->room->neighbors;
			ft_add_neighbors_of_room(ant_farm, neighbors, flag);
			ft_dequeue(ant_farm->queue);
			// ft_printf("Removing front of queue \n");
			// ft_print_queue(ant_farm->queue);
		}
		if (flag == 0)
			ft_save_paths_bfs(ant_farm);
		ft_reset(ant_farm);
		if (flag == 0)
			temp = ft_get_start_room(ant_farm->rooms_lst);
		else
			temp = ft_get_end_room(ant_farm);
		if (temp->state == COMPLETED)
			ft_enqueue(ant_farm->queue, temp);
		i += 1;
	}
	ft_fullreset(ant_farm);
	// ft_print_paths_list_detail(ant_farm);
	print_rooms_list(ant_farm->rooms_lst);
	ft_paths_discovered(ant_farm);
	// print_neighbors_list_debug(ant_farm->hash_table);
	// ft_printf("Max Paths in Graph %d\n", ant_farm->max_paths);
}
