/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bfs.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:12:05 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/08 18:36:19 by dsaripap      ########   odam.nl         */
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
		neighb_tmp->hash_item->room->score == 0 && \
		neighb_tmp->hash_item->room->level_sink != 0)
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
	{
		// ft_printf("\nArrived at %s room\n", ant_farm->queue->front->room->name);
		flag = 1;
	}
	ft_dequeue(ant_farm->queue);
	// ft_printf("Removing front of queue \n");
	// ft_print_queue(ant_farm->queue);
	return (flag);
}

/*
** We run the bfs algorithm traversing the graph from source to sink,
** find the shortest paths and save them.
** Also we set the level_source of all the rooms(leveling from source to sink).
** Before adding the neighbors of each room to the queue I sort
** the neighbors based on the level_sink
*/

size_t				ft_bfs_algorithm(t_ant_farm *ant_farm, size_t run)
{
	t_room			*temp;
	size_t			i;
	size_t			flag;

	ant_farm->max_paths = ft_find_maxpaths(ant_farm);
	ant_farm->queue = (t_queue *)ft_memalloc(sizeof(t_queue));
	temp = ft_get_start_room(ant_farm->rooms_lst);
	ft_enqueue(ant_farm->queue, temp);
	temp->parent = NULL;
	i = 0;
	while (i < ant_farm->max_paths)
	{
		flag = 0;
		while (!ft_queue_is_empty(ant_farm->queue))
			flag = ft_bfs(ant_farm, run, flag);
		// ft_printf(ANSI_COLOR_RED_CINA"result from neighbors result = %d - flag %d\n"ANSI_COLOR_RESET, result, flag);
		if (flag == 1)
			ft_save_paths_bfs(ant_farm, 1, run);
		ft_bfs_reset(ant_farm);
		temp = ft_get_start_room(ant_farm->rooms_lst);
		if (temp->state == COMPLETED)
			ft_enqueue(ant_farm->queue, temp);
		// ft_print_paths(ant_farm);
		i += 1;
	}
	ft_paths_discovered(ant_farm);
	ft_free_queue(ant_farm->queue);
	return (ant_farm->discovered_paths);
}

static size_t		find_last_elem(t_lines *lines_lst)
{
	t_lines			*lines;

	lines = lines_lst;
	if (lines == NULL || lines->next == NULL)
		return (0);
	while (lines->next != NULL)
	{
		// ft_printf("lines %d \n", lines->lines);
		lines = lines->next;
	}
	// ft_printf("lines %d prev %d\n", lines->lines, lines->prev->lines);
	// if (lines->next != NULL)
	// 	lines = lines->prev;
	// ft_printf("last element in lines %d \n", lines->lines);
	return (lines->prev->lines);
}

static size_t		find_best_run(t_lines *lines_lst)
{
	t_lines			*temp;
	size_t			min;
	size_t			min_run;

	temp = lines_lst;
	min = 2147483647;
	while (temp != NULL)
	{
		if (temp->lines < min)
		{
			min = temp->lines;
			min_run = temp->run;
			// result = ft_bfs_sink(ant_farm, i);
			// ant_farm->best_run = i - 1;
			// ft_paths_discovered(ant_farm);
			// flag = 1;
			// break ;
		}
		temp = temp->next;
	}
	return (min_run);
}

int					ft_bfs_runs(t_ant_farm *ant_farm)
{
	size_t			i;
	t_lines			*lines_lst;
	t_lines			*temp;
	size_t			flag;
	size_t			result;
	int				flag_stop;

	i = 1;
	flag = 0;
	flag_stop = 0;
	lines_lst = ant_farm->lines_lst;
	ant_farm->discovered_paths = -1;
	ant_farm->max_paths = ft_find_maxpaths(ant_farm);
	// ft_printf("max paths = %d \n", ant_farm->max_paths);
	while (!(ant_farm->discovered_paths == ant_farm->max_paths ||
	flag == 1 || ant_farm->discovered_paths == 0))
	// while (flag == 0)
	// while (i <= 8)
	{
		// ft_printf("discovered paths = %d \n", ant_farm->discovered_paths);
		ant_farm->best_run = i;
		result = ft_bfs_algorithm(ant_farm, i);
		ft_printf(">> Current Run : %d - BFS Result %d\n", ant_farm->best_run, result);
		if (result != 0)
		{
			ft_sort_paths_on_size(ant_farm);
			ft_ants_to_paths(ant_farm);
			ft_printf(ANSI_COLOR_BLUE" ============================================= \n");
			ft_printf(" ****** RUN : %d - LINES : %d \n", i, ant_farm->lines);
			ft_printf(" ============================================= \n"ANSI_COLOR_RESET);
			// ft_print_paths(ant_farm);
			temp = (t_lines *)ft_memalloc(sizeof(t_lines));
			temp->lines = ant_farm->lines;
			temp->run = i;
			ft_lines_list_addend(&(ant_farm->lines_lst), temp);
			ft_printf("flag stop %d best run %d lines %d last elem lines %d \n", flag_stop, ant_farm->best_run, ant_farm->lines, find_last_elem(ant_farm->lines_lst));
			if (flag_stop == 0 && ant_farm->best_run != 1 && \
			ant_farm->lines > find_last_elem(ant_farm->lines_lst))
			{
				ft_bfs_level_sink(ant_farm);
				ft_bfs_level_source(ant_farm);
				i += 1;
				ft_printf("Running BFS from sink - Run %d\n", i);
				result = ft_bfs_sink(ant_farm, i);
				ft_printf("RESULT %d from Running BFS from sink\n", result);
				ft_sort_paths_on_size(ant_farm);
				ft_ants_to_paths(ant_farm);
				ft_print_paths(ant_farm);
				temp = (t_lines *)ft_memalloc(sizeof(t_lines));
				temp->lines = ant_farm->lines;
				temp->run = i;
				ft_lines_list_addend(&(ant_farm->lines_lst), temp);
				ft_printf(ANSI_COLOR_BLUE" ============================================= \n");
				ft_printf(" ****** RUN : %d - LINES : %d \n", i, ant_farm->lines);
				ft_printf(" ============================================= \n"ANSI_COLOR_RESET);
			}
			// else
			// {
			// 	break ;
			// }
			// temp = ant_farm->lines_lst;
			// while (temp != NULL)
			// {
			// 	if (temp->next != NULL && temp->lines < temp->next->lines)
			// 	{
			// 		// result = ft_bfs_sink(ant_farm, i);
			// 		ant_farm->best_run = i - 1;
			// 		ft_paths_discovered(ant_farm);
			// 		flag = 1;
			// 		// break ;
			// 	}
			// 	temp = temp->next;
			// }
		}
		else
		{
			ant_farm->best_run = find_best_run(ant_farm->lines_lst);
			// ft_printf("BEST RUN : %d\n", ant_farm->best_run);
			ft_paths_discovered(ant_farm);
			flag = 1;
		}
		if (ant_farm->best_run == 0)
			return (ft_exit_msg(ant_farm, error_no_solution));
		ft_bfs_level_sink(ant_farm);
		ft_bfs_level_source(ant_farm);
		i += 1;
	}
	return (SUCCESS);
}
