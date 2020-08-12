/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bfs_levels.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/21 13:24:38 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 18:47:14 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** Function that checks if it should enqueue the neighbors when
** traversing from source to sink and sink to source in the functions
** lvl_source and lvl_sink respectively.
** It is called from both function but with a different flag.
*/

int					ft_enqueue_condition(t_ant_farm *ant_farm, \
										t_neighbor *neighbors, size_t flag)
{
	if (flag == 0 && neighbors->hash_item->room->state == UNEXPLORED &&
	neighbors->hash_item->room->position != END)
	{
		if (ft_enqueue(ant_farm->queue, neighbors->hash_item->room) != SUCCESS)
			return (ERROR);
		neighbors->hash_item->room->parent = ant_farm->queue->front->room;
		if (neighbors->hash_item->room->level_source == 0)
			neighbors->hash_item->room->level_source = \
			neighbors->hash_item->room->parent->level_source + 1;
	}
	else if (flag == 1 && neighbors->hash_item->room->state == UNEXPLORED &&
	neighbors->hash_item->room->position != START)
	{
		if (ft_enqueue(ant_farm->queue, neighbors->hash_item->room) != SUCCESS)
			return (ERROR);
		neighbors->hash_item->room->parent = ant_farm->queue->front->room;
		if (neighbors->hash_item->room->level_sink == 0)
			neighbors->hash_item->room->level_sink = \
			neighbors->hash_item->room->parent->level_sink + 1;
	}
	return (SUCCESS);
}

void				levels_lastchecks(t_ant_farm *ant_farm, int flag)
{
	t_room			*temp;

	if (flag == 0)
	{
		temp = ft_get_start_room(ant_farm->rooms_lst);
		temp->level_source = -1;
		ft_free_queue(ant_farm->queue);
		ft_bfs_fullreset(ant_farm);
	}
	else
	{
		temp = ft_get_end_room(ant_farm);
		temp->level_sink = -1;
		ft_free_queue(ant_farm->queue);
		ft_bfs_fullreset(ant_farm);
	}
}

/*
** Function that traverses the graph from source (start room)
** to sink (end room) and sets the level_source of each room.
** The level_source of sink and all dead ends from sink are not
** set so they are zero. We set level_source of source to -1.
*/

int					lvl_source(t_ant_farm *ant_farm)
{
	t_room			*temp;
	t_neighbor		*neighbors;

	ant_farm->queue = (t_queue *)ft_memalloc(sizeof(t_queue));
	if (ant_farm->queue == NULL)
		return (ft_exit_msg(ant_farm, ERROR));
	temp = ft_get_start_room(ant_farm->rooms_lst);
	if (ft_enqueue(ant_farm->queue, temp) != SUCCESS)
		return (ERROR);
	temp->parent = NULL;
	while (!ft_queue_is_empty(ant_farm->queue))
	{
		neighbors = ant_farm->queue->front->room->neighbors;
		while (neighbors != NULL)
		{
			if (ft_enqueue_condition(ant_farm, neighbors, 0) != SUCCESS)
				return (ERROR);
			neighbors = neighbors->next;
		}
		ft_dequeue(ant_farm->queue);
	}
	levels_lastchecks(ant_farm, 0);
	return (SUCCESS);
}

/*
** Function that traverses the graph from sink (end room)
** to source (start room) and sets the level_sink of each room.
** The level_sink of source and all dead ends from source are not
** set so they are zero. We set level_sink of sink to -1.
*/

int					lvl_sink(t_ant_farm *ant_farm)
{
	t_room			*temp;
	t_neighbor		*neighbors;

	ant_farm->queue = (t_queue *)ft_memalloc(sizeof(t_queue));
	if (ant_farm->queue == NULL)
		return (ft_exit_msg(ant_farm, ERROR));
	temp = ft_get_end_room(ant_farm);
	if (ft_enqueue(ant_farm->queue, temp) != SUCCESS)
		return (ERROR);
	temp->parent = NULL;
	while (!ft_queue_is_empty(ant_farm->queue))
	{
		neighbors = ant_farm->queue->front->room->neighbors;
		while (neighbors != NULL)
		{
			if (ft_enqueue_condition(ant_farm, neighbors, 1) != SUCCESS)
				return (ERROR);
			neighbors = neighbors->next;
		}
		ft_dequeue(ant_farm->queue);
	}
	levels_lastchecks(ant_farm, 1);
	return (SUCCESS);
}
