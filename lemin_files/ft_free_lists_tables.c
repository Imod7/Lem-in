/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_lists_tables.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:37:48 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/07 12:31:39 by dsaripap      ########   odam.nl         */
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
		// ft_printf("freeing line %s \n", curr_node->line);
		next_node = curr_node->next;
		free(curr_node->line);
		free(curr_node);
		// curr_node = NULL;
		// ft_printf("current node is %p \n", curr_node);
		curr_node = next_node;
	}
	input_lst = NULL;
	// ft_printf("set list to %p \n", input_lst);
}

static void			ft_free_neighborslst(t_neighbor *neighbors_lst)
{
	t_neighbor		*curr_node;
	t_neighbor		*next_node;

	curr_node = neighbors_lst;
	while (curr_node != NULL)
	{
		// ft_printf(" freeing neighbor %s \n", curr_node->hash_item->room_name);
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
		// ft_printf("freeing neighbors of room %s \n", curr_node->name);
		ft_free_ants_lst(&(curr_node->ants_lst));
		ft_free_neighborslst(curr_node->neighbors);
		// ft_printf("freeing room %s \n", curr_node->name);
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
				// ft_printf("freeing hash item %s \n", curr_item->room_name);
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
