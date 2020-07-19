/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bfs.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:12:05 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/19 10:50:39 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** This function sets the state of all rooms of the graph
** to state UNEXPLORED
*/

void				ft_bfs_reset(t_ant_farm *ant_farm)
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

/*
** This function sets the state of all rooms of the graph
** to state UNEXPLORED
*/

void				ft_bfs_fullreset(t_ant_farm *ant_farm)
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
** We also update the parent room at the same time and the level_source
** (leveling from source to sink) of the neighbor.
*/

static size_t		ft_add_neighbors_of_room(t_ant_farm *ant_farm, \
											t_neighbor *neighbors, \
											t_room *front_room)
{
	size_t			flag;
	t_neighbor		*neighb_tmp;

	flag = 0;
	neighb_tmp = neighbors;
	// ft_printf(" Neighbors of Front Room %s , lvl_source %d, lvl_sink %d, pos %d\n", front_room->name, front_room->level_source, front_room->level_sink, front_room->position);
	if (front_room->position == END)
		return (-1);
	while (neighb_tmp != NULL)
	{
		// ft_printf("    neighb %s ", neighb_tmp->hash_item->room->name);
		// ft_printf("    state %d ", neighb_tmp->hash_item->room->state);
		// ft_printf("    lvl_source %d, ", neighb_tmp->hash_item->room->level_source);
		// ft_printf("    lvl_sink %d, ", neighb_tmp->hash_item->room->level_sink);
		// ft_printf("    score %d ", neighb_tmp->hash_item->room->score);
		if (neighb_tmp->hash_item->room->state == UNEXPLORED && \
		neighb_tmp->hash_item->room->score == 0)
		// && 
		// neighb_tmp->hash_item->room->level_sink != 0) || 
		// (neighb_tmp->hash_item->room->position == END && 
		// neighb_tmp->hash_item->room->parent == NULL))
		{
			// ft_printf("neighbor room %s state : %d\n", neighbors->hash_item->room->name, neighbors->hash_item->room->state);
			ft_enqueue(ant_farm->queue, neighb_tmp->hash_item->room);
			// ft_printf(ANSI_COLOR_GREEN_BOLD"    -> Enqueued room %s state : %d"ANSI_COLOR_RESET, neighb_tmp->hash_item->room->name, neighb_tmp->hash_item->room->state);
			// ft_print_queue(ant_farm->queue);
			// ft_printf("neighbors of room %s \n", ant_farm->queue->front->room->name);
			neighb_tmp->hash_item->room->parent = ant_farm->queue->front->room;
			// ft_printf("\nparent of room %s is %s", neighb_tmp->hash_item->room->name, neighb_tmp->hash_item->room->parent->name);
			if (neighb_tmp->hash_item->room->level_source == 0)
					neighb_tmp->hash_item->room->level_source = \
					neighb_tmp->hash_item->room->parent->level_source + 1;
			// else if (flag == 0 && neighbors->hash_item->room->level_sink == 0)
			// 	neighbors->hash_item->room->level_sink = \
			// 	neighbors->hash_item->room->parent->level_sink + 1;
			// ft_printf("neighbor room %s level_source : %d , parent : %s level_source : %d \n", neighbors->hash_item->room->name, neighbors->hash_item->room->level_source, neighbors->hash_item->room->parent->name, neighbors->hash_item->room->parent->level_source);
			// ft_print_paths(ant_farm);
			// ft_printf("level : %d\n", neighbors->hash_item->room->level);
			flag += 1;
		}
		// ft_printf(" \n");
		neighb_tmp = neighb_tmp->next;
	}
	if (flag == 0)
	{
		// ft_printf(ANSI_COLOR_RED_CINA"  No neighbors that are not in a path added ! \n"ANSI_COLOR_RESET);
		// ft_printf(ANSI_COLOR_RED_CINA"  Will check if exist neighbors that are in a path ! \n"ANSI_COLOR_RESET);
		return (ft_check_min_cut(ant_farm, neighbors, front_room));
		// if (flag == 0)
		// 	return (flag);
	}
	return (flag);
}

/*
** We run the bfs algorithm traversing the graph from sink to source
** and setting the level_sink of all the rooms (leveling from sink to source)
** without saving any paths. We only level from sink to source.
** When it finds room with parent the SOURCE it does not level it.
** That way I know the dead ends from source room.
** To distinguish from dead ends and the sink room, we set level_sink of
** sink room to -1 at the end of the leveling
*/

void				ft_bfs_for_levels(t_ant_farm *ant_farm)
{
	t_room			*temp;
	t_neighbor		*neighbors;

	ant_farm->queue = (t_queue *)ft_memalloc(sizeof(t_queue));
	temp = ft_get_end_room(ant_farm);
	ft_enqueue(ant_farm->queue, temp);
	temp->parent = NULL;
	while (!ft_queue_is_empty(ant_farm->queue))
	{
		neighbors = ant_farm->queue->front->room->neighbors;
		while (neighbors != NULL)
		{
			if (neighbors->hash_item->room->state == UNEXPLORED)
			{
				ft_enqueue(ant_farm->queue, neighbors->hash_item->room);
				neighbors->hash_item->room->parent = ant_farm->queue->front->room;
				if (neighbors->hash_item->room->level_sink == 0 && \
				neighbors->hash_item->room->parent->position != START)
					neighbors->hash_item->room->level_sink = \
					neighbors->hash_item->room->parent->level_sink + 1;
			}
			neighbors = neighbors->next;
		}
		ft_dequeue(ant_farm->queue);
	}
	temp = ft_get_end_room(ant_farm);
	temp->level_sink = -1;
	ft_bfs_fullreset(ant_farm);
}

/*
** We run the bfs algorithm traversing the graph from source to sink,
** find the shortest paths and save them and also to set the level_source
** of all the rooms (leveling from source to sink).
** Before adding the neighbors of each room to the queue I sort
** the neighbors based on the level_sink
*/

size_t				ft_bfs(t_ant_farm *ant_farm, size_t run)
{
	t_room			*temp;
	t_neighbor		*neighbors;
	int				result;
	size_t			i;

	ant_farm->max_paths = ft_find_maxpaths(ant_farm);
	ant_farm->queue = (t_queue *)ft_memalloc(sizeof(t_queue));
	temp = ft_get_start_room(ant_farm->rooms_lst);
	ft_enqueue(ant_farm->queue, temp);
	temp->parent = NULL;
	i = 0;
	// ft_printf("max paths = %d \n", ant_farm->max_paths);
	// ft_printf(ANSI_COLOR_GREEN_EMER"\n ================ BFS ================ "ANSI_COLOR_RESET);
	while (i < ant_farm->max_paths)
	// while (i < 1)
	{
		// ft_printf(ANSI_COLOR_CYAN"\n ---- BFS Iter : %d ---- \n"ANSI_COLOR_RESET, i);
		while (!ft_queue_is_empty(ant_farm->queue))
		{
			neighbors = ant_farm->queue->front->room->neighbors;
			// ft_sort_neighbors(&neighbors, &temp);
			result = ft_add_neighbors_of_room(ant_farm, neighbors, \
									ant_farm->queue->front->room);
			// if (result == -1)
			// 	ft_printf("\nArrived at %s room\n", ant_farm->queue->front->room->name);
			ft_dequeue(ant_farm->queue);
			// ft_printf("Removing front of queue \n");
			// ft_print_queue(ant_farm->queue);
		}
		ft_save_paths_bfs(ant_farm, 1, run);
		ft_bfs_reset(ant_farm);
		temp = ft_get_start_room(ant_farm->rooms_lst);
		if (temp->state == COMPLETED)
			ft_enqueue(ant_farm->queue, temp);
		// ft_print_paths(ant_farm);
		i += 1;
		// ft_printf("i = %d\n", i);
		// print_rooms_list(ant_farm->rooms_lst);
	}
	ft_bfs_fullreset(ant_farm);
	// ft_print_paths_list_detail(ant_farm);
	// print_rooms_list(ant_farm->rooms_lst);
	ft_paths_discovered(ant_farm);
	return (ant_farm->discovered_paths);
	// print_neighbors_list_debug(ant_farm->hash_table);
	// ft_printf("Max Paths in Graph %d\n", ant_farm->max_paths);
}

void				ft_bfs_runs(t_ant_farm *ant_farm)
{
	size_t			i;

	i = 0;
	while (i < 4)
	{
		ft_printf(ANSI_COLOR_YELLOW_PAST"\n *****************************");
		ft_printf(ANSI_COLOR_YELLOW_PAST"*****************************\n");
		ft_printf(" *************** Run : %d ********** \n"ANSI_COLOR_RESET, i);
		ft_printf(ANSI_COLOR_YELLOW_PAST" *****************************");
		ft_printf(ANSI_COLOR_YELLOW_PAST"*****************************\n");
		ft_bfs(ant_farm, i);
		ft_sort_paths_on_size(ant_farm);
		ft_printf("Sorted paths \n");
		ft_print_paths_sizes(ant_farm);
		// ft_print_paths(ant_farm);
		ft_ants_to_paths(ant_farm);
		ft_printf(" ** Run : %d - lines : %d \n", i, ant_farm->lines);
		i += 1;
	}
}
