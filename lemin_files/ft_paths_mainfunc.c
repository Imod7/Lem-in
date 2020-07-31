/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_paths_mainfunc.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 14:18:09 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/31 05:11:43 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** Function that updates the amount of discovered_paths of the
** current run (current run id is saved in best_run).
** That way we know how many paths our current run discovered and
** compare it with previous run and select the best one.
*/

void				ft_paths_discovered(t_ant_farm *ant_farm)
{
	t_paths			*temp;

	temp = ant_farm->paths;
	ant_farm->discovered_paths = 0;
	while (temp != NULL) //&& temp->run == ant_farm->best_run)
	{
		// ft_printf("path id %d path run %d\n", temp->path_id, temp->run);
		// ft_printf("current run %d \n", ant_farm->best_run);
		if (temp->run == ant_farm->best_run)
			ant_farm->discovered_paths += 1;
		temp = temp->next;
	}
	// ant_farm->discovered_paths += 1;
	ft_bfs_fullreset(ant_farm);
}

/*
** Function that returns the size of the given path
*/

size_t				ft_path_size(t_paths *lst)
{
	t_paths			*temp;
	size_t			len;

	temp = lst;
	len = 0;
	if (temp == NULL)
		return (0);
	while (temp != NULL)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}

static void			ft_check_and_sort(t_ant_farm *ant_farm, t_paths *paths, \
									size_t *flag)
{
	while (paths->next != NULL) // && paths->next != NULL)
	{
		if (paths->path_size > paths->next->path_size)
		{
			*flag += 1;
			ft_mergesort(ant_farm, &(ant_farm->paths));
			// sorted = ft_mergesort(ant_farm, &(ant_farm->paths));
			break ;
			// tmp_prev = paths->prev;
			// tmp_next = paths->next;
			// paths->path_id = paths->next->path_id;
			// paths->next->path_id = temp_id;
		}
		else
			paths = paths->next;
		// ft_printf(" ==== merge sort %d \n", ant_farm->paths->path_id);
		// ft_print_paths(ant_farm);
	}
}

/*
** Function that sorts the paths saved in ant_farm->paths
** from smallest to biggest for every bfs run that we have.
*/

void				ft_sort_paths_on_size(t_ant_farm *ant_farm)
{
	t_paths			*paths;
	// t_paths			*sorted;
	t_paths			*temp;
	size_t			flag;

	temp = ant_farm->paths;
	paths = ant_farm->paths;
	// sorted = NULL;
	flag = 0;
	while (paths->next != NULL && paths->run != ant_farm->best_run)
	{
		// ft_printf(">> iterating through Path %d\n", paths->path_id);
		paths = paths->next;
		temp = temp->next;
	}
	if (temp != NULL && temp->prev != NULL)
	{
		temp = temp->prev;
		// ft_printf(">> temp %d, run %d\n", temp->path_id, temp->run);
	}
	ft_check_and_sort(ant_farm, paths, &flag);
	// ft_printf(">> Sorting paths Starting from Path %d\n", paths->path_id);
	// while (paths->next != NULL) // && paths->next != NULL)
	// {
	// 	if (paths->path_size > paths->next->path_size)
	// 	{
	// 		flag += 1;
	// 		sorted = ft_mergesort(ant_farm, &(ant_farm->paths));
	// 		break ;
	// 		// tmp_prev = paths->prev;
	// 		// tmp_next = paths->next;
	// 		// paths->path_id = paths->next->path_id;
	// 		// paths->next->path_id = temp_id;
	// 	}
	// 	else
	// 		paths = paths->next;
	// 	// ft_printf(" ==== merge sort %d \n", ant_farm->paths->path_id);
	// 	// ft_print_paths(ant_farm);
	// }
	// ft_printf(">> temp %d, run %d\n", temp->path_id, temp->run);
	// if (sorted != NULL)
	// 	ft_printf(">> sorted ->  %d, sorted run %d\n", sorted->path_id, sorted->run);
	// ft_printf(">> ant_farm paths ->  %d, run %d\n", ant_farm->paths->path_id, ant_farm->paths->run);
	if (temp->next != NULL && temp->run != ant_farm->paths->run && flag != 0)
	{
		// ft_printf(" -- getting in here\n");
		temp->next = ant_farm->paths;
		ant_farm->paths->prev = temp;
		while (temp->prev != NULL)
			temp = temp->prev;
		ant_farm->paths = temp;
	}
}

/*
** Function that calculates the maximum number of paths a graph
** can have based on the number of edges (neighbors) from the source
** room and the sink room. The min number is the maximum possible paths.
** We use the level_sink and level_source to exclude dead ends from the
** source and sink room respectively. The level of dead ends rooms is zero.
*/

size_t				ft_find_maxpaths(t_ant_farm *ant_farm)
{
	t_room			*temp;
	t_neighbor		*neighbors_lst;
	// size_t			count_s;
	size_t			count;
	size_t			max_paths;

	count = 0;
	max_paths = 0;
	temp = ft_get_start_room(ant_farm->rooms_lst);
	neighbors_lst = temp->neighbors;
	// ft_printf(" start lvl sink %d \n", temp->level_sink);
	while (neighbors_lst != NULL)
	{
		// ft_printf(" neigh %s lvl sink %d \n", neighbors_lst->hash_item->room->name, neighbors_lst->hash_item->room->level_sink);
		if (neighbors_lst->hash_item->room->level_sink != 0)
			max_paths += 1;
		neighbors_lst = neighbors_lst->next;
	}
	temp = ft_get_end_room(ant_farm);
	neighbors_lst = temp->neighbors;
	// ft_printf(" end lvl source %d \n", temp->level_source);
	while (neighbors_lst != NULL)
	{
		// ft_printf(" neigh %s lvl source %d \n", neighbors_lst->hash_item->room->name, neighbors_lst->hash_item->room->level_source);
		if (neighbors_lst->hash_item->room->level_source != 0)
			count += 1;
		neighbors_lst = neighbors_lst->next;
	}
	max_paths = (max_paths <= count) ? max_paths : count;
	return (max_paths);
}
