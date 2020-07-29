/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_paths_auxfunc.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:38:16 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/29 15:40:37 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void				ft_pathlst_addstart(t_path_list **lst, t_path_list *new)
{
	t_path_list		*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	*lst = new;
	new->next = temp;
	temp->prev = new;
}

void				ft_pathlst_addend(t_path_list **lst, t_path_list *new)
{
	t_path_list		*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

void				ft_path_addend(t_paths **path, t_paths *new)
{
	t_paths			*temp;
	int				max;

	if (*path == NULL)
	{
		*path = new;
		new->path_id = 1;
		return ;
	}
	temp = *path;
	max = 0;
	while (temp != NULL)
	{
		if (temp->path_id > max)
			max = temp->path_id;
		// ft_printf("  temp->path id %d - max %d\n", temp->path_id, max);
		temp = temp->next;
	}
	temp = *path;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
	if (max == 0)
		max = 1;
	new->path_id = max + 1;
	// ft_printf("max %d so new path id %d\n", max, new->path_id);
}

size_t				ft_find_maxpaths(t_ant_farm *ant_farm)
{
	t_room			*temp;
	t_neighbor		*neighbors_lst;
	size_t			count_s;
	size_t			count_e;
	size_t			max_paths;

	count_s = 0;
	count_e = 0;
	temp = ft_get_start_room(ant_farm->rooms_lst);
	neighbors_lst = temp->neighbors;
	// ft_printf(" start lvl sink %d \n", temp->level_sink);
	while (neighbors_lst != NULL)
	{
		// ft_printf(" neigh %s lvl sink %d \n", neighbors_lst->hash_item->room->name, neighbors_lst->hash_item->room->level_sink);
		if (neighbors_lst->hash_item->room->level_sink != 0)
			count_s += 1;
		neighbors_lst = neighbors_lst->next;
	}
	temp = ft_get_end_room(ant_farm);
	neighbors_lst = temp->neighbors;
	// ft_printf(" end lvl source %d \n", temp->level_source);
	while (neighbors_lst != NULL)
	{
		// ft_printf(" neigh %s lvl source %d \n", neighbors_lst->hash_item->room->name, neighbors_lst->hash_item->room->level_source);
		if (neighbors_lst->hash_item->room->level_source != 0)
			count_e += 1;
		neighbors_lst = neighbors_lst->next;
	}
	max_paths = (count_s <= count_e) ? count_s : count_e;
	return (max_paths);
}

void				ft_sort_paths_on_size(t_ant_farm *ant_farm)
{
	t_paths			*paths;
	t_paths			*sorted;
	t_paths			*temp;
	size_t			flag;

	temp = ant_farm->paths;
	paths = ant_farm->paths;
	sorted = NULL;
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
	// ft_printf(">> Sorting paths Starting from Path %d\n", paths->path_id);
	while (paths->next != NULL) // && paths->next != NULL)
	{
		if (paths->path_size > paths->next->path_size)
		{
			flag += 1;
			sorted = ft_mergesort(ant_farm, &(ant_farm->paths));
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
