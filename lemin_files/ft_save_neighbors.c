/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_save_neighbors.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:39:37 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/04 09:23:01 by dsaripap      ########   odam.nl         */
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
	// ft_printf("Retrieved Room '%s'\n", room_item->room_name);
	neighbor_item = ft_retrieve_hash_item(ant_farm->hash_table, room_b);
	if (neighbor_item == NULL)
		return (ft_exit_msg(ant_farm, error_in_link));
	// ft_printf("Adding in retrieved room '%s' the neighbor '%s'\n", room_item->room_name, neighbor_item->room_name);
	// neighbor = ft_neighbor_newnode(neighbor_item);
	neighbor = (t_neighbor*)ft_memalloc(sizeof(t_neighbor));
	neighbor->hash_item = neighbor_item;
	ft_neighbor_addend(&(room_item->room->neighbors), neighbor);
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
	// unsigned int	key_room;
	// char			*neighbor_name;
	// t_neighbor		*neighbor;
	// t_hash_item		*room_item;
	// t_hash_item		*neighbor_item;

	temp = ant_farm->input;
	while (temp != NULL)
	{
		if (ft_strchr(temp->line, '-') != NULL)
		{
			if (ft_get_end_room(ant_farm) == NULL)
			{
				// ft_printf("end exists \n");
				return (ft_exit_msg(ant_farm, error_end_room_missing));
			}
			if (ft_get_start_room(ant_farm->rooms_lst) == NULL)
			{
				// ft_printf("end exists \n");
				return (ft_exit_msg(ant_farm, error_start_room_missing));
			}
			// ft_printf(ANSI_COLOR_CYAN"Link : '%s'\n"ANSI_COLOR_RESET, temp->line);
			array = ft_strsplit(temp->line, '-');
			ft_retrieve_and_save(ant_farm, array[0], array[1]);
			ft_retrieve_and_save(ant_farm, array[1], array[0]);
			// room_item = ft_retrieve_hash_item(ant_farm->hash_table, array[0]);
			// // ft_printf("Retrieved Room '%s'\n", room_item->room_name);
			// neighbor_item = ft_retrieve_hash_item(ant_farm->hash_table, array[1]);
			// if (neighbor_item == NULL)
			// 	return (ft_exit_msg(error_in_link));
			// // ft_printf("Adding in retrieved room '%s' the neighbor '%s'\n", room_item->room_name, neighbor_item->room_name);
			// // neighbor = ft_neighbor_newnode(neighbor_item);
			// neighbor = (t_neighbor*)ft_memalloc(sizeof(t_neighbor));
			// neighbor->hash_item = neighbor_item;
			// ft_neighbor_addend(&(room_item->room->neighbors), neighbor);
			// if (neighbor_item == NULL)
			// 	return (ft_exit_msg(error_in_link));
			// room_item = ft_retrieve_hash_item(ant_farm->hash_table, array[1]);
			// // ft_printf("Retrieved Room '%s'\n", room_item->room_name);
			// neighbor_item = ft_retrieve_hash_item(ant_farm->hash_table, array[0]);
			// // ft_printf("Adding in retrieved room '%s' the neighbor '%s'\n", room_item->room_name, neighbor_item->room_name);
			// neighbor = (t_neighbor*)ft_memalloc(sizeof(t_neighbor));
			// neighbor->hash_item = neighbor_item;
			// // neighbor = ft_neighbor_newnode(neighbor_item);
			// ft_neighbor_addend(&(room_item->room->neighbors), neighbor);
			ft_free_string(array, 2);
		}
		temp = temp->next;
	}
	return (SUCCESS);
}
