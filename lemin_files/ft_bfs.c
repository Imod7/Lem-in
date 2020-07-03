/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bfs.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:12:05 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/06/29 20:55:15 by dsaripap      ########   odam.nl         */
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

// static int					ft_add_neighbors_in_queue(t_ant_farm *ant_farm, \
// 														t_neighbor *neighbors)
// {
// 	t_neighbor		*temp;

// 	while (neighbors != NULL)
// 	{
// 		if (neighbors->hash_item->room->state == UNEXPLORED)
// 		{
// 			// ft_printf("neighbor room %s state : %d\n", neighbors->hash_item->room->name, neighbors->hash_item->room->state);
// 			ft_enqueue(ant_farm->queue, neighbors->hash_item->room);
// 			ft_printf("enqueud room %s \n", neighbors->hash_item->room->name);
// 			ft_print_queue(ant_farm->queue);
// 			ft_printf("neighbors of room %s \n", ant_farm->queue->front->room->name);
// 			neighbors->hash_item->room->parent = ant_farm->queue->front->room;
// 			if (neighbors->hash_item->room->level == 0)
// 				neighbors->hash_item->room->level = neighbors->hash_item->room->parent->level + 1;
// 			ft_printf("neighbor room %s level : %d , parent : %s level : %d \n", neighbors->hash_item->room->name, neighbors->hash_item->room->level, neighbors->hash_item->room->parent->name, neighbors->hash_item->room->parent->level);
// 			// ft_print_paths(ant_farm);
// 			// ft_printf("level : %d\n", neighbors->hash_item->room->level);
// 		}
// 		neighbors = neighbors->next;
// 	}
// }

void				ft_bfs(t_ant_farm *ant_farm)
{
	t_room			*temp;
	t_neighbor		*neighbors;
	// t_room			*parent_room;
	size_t			i;

	ant_farm->max_paths = ft_find_maxpaths(ant_farm);
	ant_farm->queue = (t_queue *)ft_memalloc(sizeof(t_queue));
	temp = ft_get_start_room(ant_farm->rooms_lst);
	temp->level = 0;
	ft_enqueue(ant_farm->queue, temp);
	i = 0;
	while (i < ant_farm->max_paths)
	{
		while (!ft_queue_is_empty(ant_farm->queue))
		{
			// parent_room = 
			neighbors = ant_farm->queue->front->room->neighbors;
			// ft_add_neighbors_of_room(ant_farm->queue, neighbors)
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
					if (neighbors->hash_item->room->level == 0)
						neighbors->hash_item->room->level = neighbors->hash_item->room->parent->level + 1;
					// ft_printf("neighbor room %s level : %d , parent : %s level : %d \n", neighbors->hash_item->room->name, neighbors->hash_item->room->level, neighbors->hash_item->room->parent->name, neighbors->hash_item->room->parent->level);
					// ft_print_paths(ant_farm);
					// ft_printf("level : %d\n", neighbors->hash_item->room->level);
				}
				neighbors = neighbors->next;
			}
			// ft_printf("Enqueued all neighbors that are not explored of room %s\n", ant_farm->queue->front->room->name);
			// ft_print_queue(ant_farm->queue);
			ft_dequeue(ant_farm->queue);
			// ft_printf("Removing front of queue \n");
			// ft_print_queue(ant_farm->queue);
		}
		ft_save_paths_bfs(ant_farm);
		ft_reset(ant_farm);
		temp = ft_get_start_room(temp);
		temp = ft_get_start_room(ant_farm->rooms_lst);
		if (temp->state == COMPLETED)
			ft_enqueue(ant_farm->queue, temp);
		i += 1;
	}
	ft_fullreset(ant_farm);
	// ft_print_paths_list_detail(ant_farm);
	// print_rooms_list(ant_farm->rooms_lst);
	ft_paths_discovered(ant_farm);
	// print_neighbors_list_debug(ant_farm->hash_table);
	// ft_printf("Max Paths in Graph %d\n", ant_farm->max_paths);
}
