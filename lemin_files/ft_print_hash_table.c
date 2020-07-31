/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_hash_table.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 18:18:01 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/31 05:25:59 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** Function that prints the rooms that are in the colision linked list.
** We have this linked list because we handle colisions with
** the separate chaining method so in the same key of the hash table
** we can have more than one room stored.
*/

static void			ft_print_colisions(t_hash_item *temp_item)
{
	while (temp_item != NULL)
	{
		ft_printf("%s", temp_item->room_name);
		temp_item = temp_item->colision_next;
		if (temp_item)
			ft_printf(" -> ");
	}
}

void				print_hash_table(t_hash_table *hash_table)
{
	t_hash_item		**temp;
	size_t			i;

	ft_printf("\n           Hash Table        \n");
	ft_printf("---------------------------------------\n");
	ft_printf("index\tname\troom\tcolision_next\t\n");
	temp = hash_table->array;
	i = 0;
	while (i < hash_table->size)
	{
		if (temp[i] != NULL)
		{
			ft_printf("%d\t", i);
			ft_printf("%s\t%s\t", temp[i]->room_name, temp[i]->room->name);
			ft_print_colisions(temp[i]->colision_next);
			ft_printf("\t\t\n");
		}
		else
			ft_printf("%d\tNULL\tNULL\tNULL\t\n", i);
		i += 1;
	}
	ft_printf("---------------------------------------\n");
}
