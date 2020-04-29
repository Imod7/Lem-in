/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_save_neighbors.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 19:07:22 by dominique     #+#    #+#                 */
/*   Updated: 2020/04/29 09:14:37 by dominique     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static t_neighbor	*ft_neighbor_newnode(unsigned int key)
{
	t_neighbor		*newnode;

	newnode = malloc(sizeof(t_neighbor));
	if (newnode == NULL)
		return (NULL);
	newnode->key = key;
	newnode->next = NULL;
	return (newnode);
}

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
}

/*
** Iterating through all the nodes of linked list ant_farm->input
** where we saved the raw input lines as we got them from the file.
** When we find a link we save in each node (left part of link)
** the neighbor (right part of link) by adding a neighbor node
** Also, we save the reverse which means in each node (right part of link)
** the neighbor (left part of link) since our graphs are undirected.
*/

void				ft_save_neighbors(t_ant_farm *ant_farm, \
									t_hash_table **hash_table)
{
	t_input			*temp;
	char			**array;
	unsigned int	key_room;
	unsigned int	key_neighbor;
	t_neighbor		*neighbor;

	temp = ant_farm->input;
	while (temp != NULL)
	{
		if (ft_strchr(temp->line, '-') != NULL)
		{
			// ft_printf(ANSI_COLOR_CYAN"Link : %s\n"ANSI_COLOR_RESET, temp->line);
			array = ft_strsplit(temp->line, '-');
			key_room = ft_hash_function(array[0], (*hash_table)->size);
			key_neighbor = ft_hash_function(array[1], (*hash_table)->size);
			neighbor = ft_neighbor_newnode(key_neighbor);
			// ft_printf(ANSI_COLOR_CYAN"Added in %u the %u\n"ANSI_COLOR_RESET, key_room, key_neighbor);
			ft_neighbor_addend(&((*hash_table)->array[key_room]->room->neighbors), neighbor);
			key_room = ft_hash_function(array[1], (*hash_table)->size);
			key_neighbor = ft_hash_function(array[0], (*hash_table)->size);
			neighbor = ft_neighbor_newnode(key_neighbor);
			ft_neighbor_addend(&((*hash_table)->array[key_room]->room->neighbors), neighbor);
			// ft_printf(ANSI_COLOR_CYAN"Added in %u the %u\n"ANSI_COLOR_RESET, key_room, key_neighbor);
		}
		temp = temp->next;
	}
}
