/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_neighbors.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 18:19:11 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 14:28:50 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** Function that prints the rooms that are in the colision linked list
** and also the neighbors of these rooms.
** We handle colisions with the separate chaining method.
*/

static void			ft_print_colisions(t_hash_item *temp_item, size_t *i)
{
	t_neighbor		*neigbors_lst;

	while (temp_item != NULL)
	{
		ft_printf("%d\t\t%s\t\t", *i, temp_item->room_name);
		neigbors_lst = temp_item->room->neighbors;
		while (neigbors_lst != NULL)
		{
			ft_printf("%s", neigbors_lst->hash_item->room_name);
			neigbors_lst = neigbors_lst->next;
			if (neigbors_lst)
				ft_printf(" -> ");
			else
				ft_printf("\t");
		}
		temp_item = temp_item->colision_next;
		ft_printf("\n");
	}
}

/*
** Function that prints the neighbors of the rooms which means
** iterating through the linked list of type t_neighbor
*/

static void			ft_print_neighbors(t_neighbor *neighbors_lst)
{
	while (neighbors_lst != NULL)
	{
		ft_printf("%s", neighbors_lst->hash_item->room_name);
		neighbors_lst = neighbors_lst->next;
		if (neighbors_lst)
			ft_printf(" -> ");
		else
			ft_printf("\t\t");
	}
	ft_printf("\n");
}

/*
** Function that iterates through all the items of the hash table
** and prints the room name and its neighbors (ft_print_neighbors
** function call) and also prints the colision rooms (ft_print_colisions
** function call).
*/

void				ft_print_neighbors_list(t_hash_table *hash_table)
{
	t_hash_item		**hash_item;
	size_t			i;

	hash_item = hash_table->array;
	ft_printf("\n          Hash Items - Rooms - Neighbors       \n");
	ft_printf("-------------------------------------------------\n");
	ft_printf("|hash_key\troom_name\tneighbors list\t\t\n");
	i = 0;
	while (i < hash_table->size)
	{
		if (hash_item[i] != NULL)
		{
			ft_printf("%d\t\t%s\t\t", i, hash_item[i]->room->name);
			ft_print_neighbors(hash_item[i]->room->neighbors);
			ft_print_colisions(hash_item[i]->colision_next, &i);
		}
		else
			ft_printf("|NULL\t\tNULL\t\tNULL\t\n");
		i += 1;
	}
	ft_printf("-----------------------------------------------\n");
}
