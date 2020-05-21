/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bfs.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/05 16:11:02 by dominique     #+#    #+#                 */
/*   Updated: 2020/05/21 07:30:51 by dominique     ########   odam.nl         */
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

t_room				*ft_get_start_room(t_room *temp)
{
	while (temp != NULL)
	{
		if (temp->position == START)
			break ;
		temp = temp->next;
	}
	return (temp);
}

size_t				ft_check_if_completed(t_room *room)
{
	t_neighbor		*neighbors;

	neighbors = room->neighbors;
	while (neighbors != NULL)
	{
		if (neighbors->hash_item->room->state != COMPLETED)
			return (1);
	}
	return (0);
}

void				ft_remove_path(t_ant_farm *ant_farm, int path_id)
{
	t_path_list		*path_temp;
	t_paths			*paths;

	paths = ant_farm->paths;
	while (paths != NULL)
	{
		if (paths->path_id == path_id)
		{
			path_temp = paths->path_lst;
			ft_free_pathlst(paths->path_lst);
			paths->prev->next = paths->next;
			free(paths);
			break ;
		}
		paths = paths->next;
	}
}

int					ft_no_neighbors_open(t_neighbor	*neighbors)
{
	t_neighbor		*temp;

	temp = neighbors;
	while (temp != NULL)
	{
		// ft_printf("Checking temp room %s state : %d\n", temp->hash_item->room->name, temp->hash_item->room->state);
		if (temp->hash_item->room->state == UNEXPLORED)
			return (0);
		temp = temp->next;
	}
	return (1);
}

void				ft_bfs(t_ant_farm *ant_farm)
{
	t_room			*temp;
	t_neighbor		*neighbors;
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
			neighbors = ant_farm->queue->front->room->neighbors;
			while (neighbors != NULL)
			{
				// ft_printf("neighbor room %s state : %d\n", neighbors->hash_item->room->name, neighbors->hash_item->room->state);
				// ft_printf("path_id:%d\n", neighbors->hash_item->room->path_id);
				if (neighbors->hash_item->room->state == UNEXPLORED)
				{
					ft_enqueue(ant_farm->queue, neighbors->hash_item->room);
					neighbors->hash_item->room->parent = ant_farm->queue->front->room;
					neighbors->hash_item->room->level = neighbors->hash_item->room->parent->level + 1;
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
	ft_print_paths(ant_farm);
	ft_fullreset(ant_farm);
	// ft_print_paths_list_detail(ant_farm);
	// print_rooms_list(ant_farm->rooms_lst);
	ft_printf("Max Paths in Graph %d\n", ant_farm->max_paths);
}
