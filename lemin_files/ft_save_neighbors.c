/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_save_neighbors.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:39:37 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 14:37:38 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void			ft_neighbor_addend(t_neighbor **lst, t_neighbor *new)
{
	t_neighbor		*temp;

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

static int			ft_retrieve_and_save(t_ant_farm *ant_farm, char *room_a, \
										char *room_b)
{
	t_neighbor		*neighbor;
	t_hash_item		*room_item;
	t_hash_item		*neighbor_item;

	room_item = ft_retrieve_hash_item(ant_farm->hash_table, room_a);
	neighbor_item = ft_retrieve_hash_item(ant_farm->hash_table, room_b);
	if (room_item == NULL || neighbor_item == NULL)
	{
		return (ft_exit_msg(ant_farm, error_in_link));
	}
	else if (ft_strcmp(room_item->room_name, neighbor_item->room_name))
	{
		neighbor = (t_neighbor*)ft_memalloc(sizeof(t_neighbor));
		if (neighbor == NULL)
			return (ERROR);
		neighbor->hash_item = neighbor_item;
		ft_neighbor_addend(&(room_item->room->neighbors), neighbor);
	}
	return (SUCCESS);
}

static int			ft_check_neighbors(t_ant_farm *ant_farm, \
								int len, char **array)
{
	if (len < 2 || len > 2)
	{
		ft_free_string(array, len);
		return (ft_exit_msg(ant_farm, error_in_link));
	}
	if (ft_retrieve_and_save(ant_farm, array[0], array[1]) != SUCCESS)
	{
		ft_free_string(array, len);
		return (ant_farm->signal);
	}
	if (ft_retrieve_and_save(ant_farm, array[1], array[0]) != SUCCESS)
		return (ant_farm->signal);
	return (SUCCESS);
}

/*
** Iterating through all the nodes of linked list ant_farm->input
** where we saved the raw input lines as we got them from the file.
** When we find a link we save in each node (left part of link)
** the neighbor (right part of link) by adding a neighbor node
** Also, we save the reverse which means in each node (right part of link)
** the neighbor (left part of link) since our graphs are undirected.
*/

int					ft_save_neighbors(t_ant_farm *ant_farm)
{
	t_input			*temp;
	char			**array;
	size_t			len;

	temp = ant_farm->input;
	len = 0;
	while (temp != NULL)
	{
		if (ft_strchr(temp->line, '-') != NULL && temp->line[0] != '#' && \
		ft_strchr(temp->line, ' ') == NULL)
		{
			if (ft_get_start_room(ant_farm->rooms_lst) == NULL)
				return (ft_exit_msg(ant_farm, error_start_room_missing));
			if (ft_get_end_room(ant_farm) == NULL)
				return (ft_exit_msg(ant_farm, error_end_room_missing));
			array = ft_strsplit(temp->line, '-');
			len = array_size(array);
			len = ft_check_neighbors(ant_farm, len, array);
			if (len != SUCCESS)
				return (len);
			ft_free_string(array, 2);
		}
		temp = temp->next;
	}
	return (SUCCESS);
}
