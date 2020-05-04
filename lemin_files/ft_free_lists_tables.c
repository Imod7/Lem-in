/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_lists_tables.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 09:28:47 by dominique     #+#    #+#                 */
/*   Updated: 2020/05/04 17:06:38 by dominique     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void				ft_free_inputlst(t_input *input_lst)
{
	t_input			*curr_node;
	t_input			*next_node;

	curr_node = input_lst;
	while (curr_node != NULL)
	{
		ft_printf("freeing line %s \n", curr_node->line);
		next_node = curr_node->next;
		free(curr_node->line);
		free(curr_node);
		curr_node = next_node;
	}
	input_lst = NULL;
}

static void			ft_free_neighborslst(t_neighbor *neighbors_lst)
{
	t_neighbor		*curr_node;
	t_neighbor		*next_node;

	curr_node = neighbors_lst;
	while (curr_node != NULL)
	{
		ft_printf(" freeing neigbor %s \n", curr_node->hash_item->room_name);
		next_node = curr_node->next;
		free(curr_node);
		curr_node = next_node;
	}
	neighbors_lst = NULL;
}

void				ft_free_roomslst(t_room *rooms_lst)
{
	t_room			*curr_node;
	t_room			*next_node;

	curr_node = rooms_lst;
	while (curr_node != NULL)
	{
		ft_printf("freeing neighbors of room %s \n", curr_node->name);
		ft_free_neighborslst(curr_node->neighbors);
		ft_printf("freeing room %s \n", curr_node->name);
		next_node = curr_node->next;
		free(curr_node->name);
		free(curr_node);
		curr_node = next_node;
	}
	rooms_lst = NULL;
}

void				ft_free_hashtable(t_hash_table *hash_table)
{
	size_t			i;
	t_hash_item		*curr_item;
	t_hash_item		*next_item;

	if (hash_table == NULL)
		return ;
	i = 0;
	while (i < hash_table->size)
	{
		if (hash_table->array[i] != NULL)
		{
			curr_item = hash_table->array[i];
			while(curr_item != NULL)
			{
				ft_printf("freeing hash item %s \n", curr_item->room_name);
            	next_item = curr_item->colision_next;
				free(curr_item->room_name);
            	free(curr_item);
            	curr_item = next_item;
        	}
		}
		i += 1;
	}
	free(hash_table->array);
	free(hash_table);
}
