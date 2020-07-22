/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bfs_levels.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/21 13:24:38 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/22 20:04:35 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** We run the bfs algorithm traversing the graph from sink to source
** and setting the level_sink of all the rooms (leveling from sink to source)
** without saving any paths. We only level from sink to source.
** When it finds room with parent the SOURCE it does not level it.
** That way I know the dead ends from source room.
** To distinguish from dead ends and the sink room, we set level_sink of
** sink room to -1 at the end of the leveling
*/

void				ft_bfs_level_sink(t_ant_farm *ant_farm)
{
	t_room			*temp;
	t_neighbor		*neighbors;
	// size_t			max;

	ant_farm->queue = (t_queue *)ft_memalloc(sizeof(t_queue));
	temp = ft_get_end_room(ant_farm);
	ft_enqueue(ant_farm->queue, temp);
	temp->parent = NULL;
	while (!ft_queue_is_empty(ant_farm->queue))
	{
		neighbors = ant_farm->queue->front->room->neighbors;
		while (neighbors != NULL)
		{
			if (neighbors->hash_item->room->state == UNEXPLORED &&
			neighbors->hash_item->room->position != START)
			{
				ft_enqueue(ant_farm->queue, neighbors->hash_item->room);
				neighbors->hash_item->room->parent = ant_farm->queue->front->room;
				if (neighbors->hash_item->room->level_sink == 0)
				// neighbors->hash_item->room->position == START
				// &&
				// neighbors->hash_item->room->position != START)
					neighbors->hash_item->room->level_sink = \
					neighbors->hash_item->room->parent->level_sink + 1;
			}
			// ft_printf(" neigh %s lvl sink %d \n", neighbors->hash_item->room->name, neighbors->hash_item->room->level_sink);
			neighbors = neighbors->next;
		}
		ft_dequeue(ant_farm->queue);
	}
	temp = ft_get_end_room(ant_farm);
	temp->level_sink = -1;
	// ft_printf("temp %s lvl sink %d \n", temp->name, temp->level_sink);
	ft_bfs_fullreset(ant_farm);
}

void				ft_bfs_level_source(t_ant_farm *ant_farm)
{
	t_room			*temp;
	t_neighbor		*neighbors;

	ant_farm->queue = (t_queue *)ft_memalloc(sizeof(t_queue));
	temp = ft_get_start_room(ant_farm->rooms_lst);
	ft_enqueue(ant_farm->queue, temp);
	temp->parent = NULL;
	while (!ft_queue_is_empty(ant_farm->queue))
	{
		neighbors = ant_farm->queue->front->room->neighbors;
		while (neighbors != NULL)
		{
			if (neighbors->hash_item->room->state == UNEXPLORED &&
				neighbors->hash_item->room->position != END)
			{
				ft_enqueue(ant_farm->queue, neighbors->hash_item->room);
				neighbors->hash_item->room->parent = ant_farm->queue->front->room;
				if (neighbors->hash_item->room->level_source == 0 )
				// neighbors->hash_item->room->position == END
					neighbors->hash_item->room->level_source = \
					neighbors->hash_item->room->parent->level_source + 1;
			}
			// ft_printf(" neigh %s lvl source %d \n", neighbors->hash_item->room->name, neighbors->hash_item->room->level_source);
			neighbors = neighbors->next;
		}
		ft_dequeue(ant_farm->queue);
	}
	temp = ft_get_start_room(ant_farm->rooms_lst);
	temp->level_source = -1;
	// ft_printf("temp %s lvl source %d \n", temp->name, temp->level_source);
	ft_bfs_fullreset(ant_farm);
}
