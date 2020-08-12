/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bfs.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:12:05 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 14:51:16 by dsaripap      ########   odam.nl         */
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
	if (front_room->position == END)
		return (-1);
	while (neighb_tmp != NULL)
	{
		if (neighb_tmp->hash_item->room->state == UNEXPLORED && \
		neighb_tmp->hash_item->room->score == 0 && \
		neighb_tmp->hash_item->room->level_sink != 0)
		{
			if (ft_enqueue(ant_farm->queue, neighb_tmp->hash_item->room) != \
			SUCCESS)
				return (ERROR);
			neighb_tmp->hash_item->room->parent = ant_farm->queue->front->room;
			neighb_tmp->hash_item->room->parent->run = current_run;
			flag += 1;
		}
		neighb_tmp = neighb_tmp->next;
	}
	if (flag == 0)
	{
		return (ft_check_min_cut(ant_farm, neighbors, front_room, current_run));
	}
	return (flag);
}

/*
** Implementing the enqueuing and dequeuing of the BFS algorithm
*/

static size_t		ft_bfs(t_ant_farm *ant_farm, size_t run, size_t flag)
{
	t_neighbor		*neighbors;
	int				result;

	neighbors = ant_farm->queue->front->room->neighbors;
	ft_sort_neighbors(&neighbors, &(ant_farm->queue->front->room), 0);
	ft_sort_neighbors(&neighbors, &(ant_farm->queue->front->room), 1);
	result = ft_add_neighbors_of_room(ant_farm, neighbors, \
							ant_farm->queue->front->room, run);
	if (result == -1)
		flag = 1;
	ft_dequeue(ant_farm->queue);
	return (flag);
}

static int			bfs_alg_loop(t_ant_farm *ant_farm, size_t run)
{
	size_t			i;
	int				flag;
	t_room			*temp;

	i = 0;
	while (i < ant_farm->max_paths)
	{
		flag = 0;
		while (!ft_queue_is_empty(ant_farm->queue))
			flag = ft_bfs(ant_farm, run, flag);
		if (flag == 1)
			ft_save_paths_bfs(ant_farm, 1, run);
		ft_bfs_reset(ant_farm);
		temp = ft_get_start_room(ant_farm->rooms_lst);
		if (temp->state == COMPLETED)
		{
			if (ft_enqueue(ant_farm->queue, temp) != SUCCESS)
				return (ERROR);
		}
		i += 1;
	}
	return (SUCCESS);
}

/*
** We run the bfs algorithm traversing the graph from source to sink,
** find the shortest paths and save them.
** Also we set the level_source of all the rooms(leveling from source to sink).
** Before adding the neighbors of each room to the queue I sort
** the neighbors based on the level_sink
*/

int					ft_bfs_algorithm(t_ant_farm *ant_farm, size_t run)
{
	t_room			*temp;

	ant_farm->max_paths = ft_find_maxpaths(ant_farm);
	ant_farm->queue = (t_queue *)ft_memalloc(sizeof(t_queue));
	if (ant_farm->queue == NULL)
		return (ERROR);
	temp = ft_get_start_room(ant_farm->rooms_lst);
	if (ft_enqueue(ant_farm->queue, temp) != SUCCESS)
		return (ERROR);
	temp->parent = NULL;
	if (bfs_alg_loop(ant_farm, run) != SUCCESS)
		return (ERROR);
	ft_paths_discovered(ant_farm);
	ft_free_queue(ant_farm->queue);
	return (ant_farm->discovered_paths);
}
