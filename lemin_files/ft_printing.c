/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printing.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 07:44:52 by dominique     #+#    #+#                 */
/*   Updated: 2020/04/29 09:15:56 by dominique     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void				print_input_list(t_input *input_data)
{
	t_input			*temp;

	temp = input_data;
	ft_printf("\n      Linked List with Raw Input Lines        \n");
	ft_printf("-----------------------------------------\n");
	ft_printf("|line\t\t\tnext_line|\n");
	ft_printf("|-------------------------------");
	ft_printf("-----|\n");
	while (temp != NULL)
	{
		ft_printf("|%s\t\t", temp->line);
		if (temp->next != NULL)
			ft_printf("\t-> %s\t|\n", temp->next->line);
		else
			ft_printf("\t-> NULL\t|\n");
		temp = temp->next;
	}
	ft_printf("----------------------------------------\n");
}

void				print_rooms_list(t_room *rooms_lst)
{
	t_room			*temp;

	temp = rooms_lst;
	ft_printf("\n           Linked List with all Saved Rooms        \n");
	ft_printf("-----------------------------------------------------");
	ft_printf("--------------------\n");
	ft_printf("|room_name\troom_x_coord\troom_y_coord\troom_position\t");
	ft_printf("next_room|\n");
	while (temp != NULL)
	{
		ft_printf("|%s\t\t%d\t\t%d", temp->name, temp->x_coord, temp->y_coord);
		ft_printf("\t\t%d\t\t", temp->position);
		if (temp->next != NULL)
			ft_printf("%s\t|\n", temp->next->name);
		else
			ft_printf("NULL\t|\n");
		temp = temp->next;
	}
	ft_printf("------------------------------------");
	ft_printf("------------------------------------\n");
}

void				print_hash_table(t_hash_table *hash_table)
{
	t_hash_item		**temp;
	size_t			i;

	ft_printf("\n           Hash Table        \n");
	ft_printf("-----------------------------------");
	ft_printf("---------------------\n");
	ft_printf("|hashed_name/key\troom_name\tpoints_to_room\t|\n");
	temp = hash_table->array;
	i = 0;
	while (i < hash_table->size)
	{
		if (temp[i] != NULL)
		{
			ft_printf("|%d\t\t\t", i);
			ft_printf("%s\t\t", temp[i]->room_name);
			ft_printf("%s\t\t|\n", temp[i]->room->name);
		}
		else
			ft_printf("|NULL\t\t\tNULL\t\tNULL\t\t|\n");
		i += 1;
	}
	ft_printf("------------------------------------");
	ft_printf("--------------------\n");
}

void				print_neighbors_list(t_hash_table *hash_table)
{
	t_hash_item		**temp;
	size_t			i;

	temp = hash_table->array;
	ft_printf("\n  Rooms & their Neighbors  \n");
	ft_printf("--------------------------\n");
	ft_printf("|room_name\tneighbors_linked_list\t\n");
	i = 0;
	while (i < hash_table->size)
	{
		if (temp[i] != NULL)
		{
			ft_printf("%s\t\t", temp[i]->room->name);
			while (temp[i]->room->neighbors != NULL)
			{
				ft_printf("%u->", temp[i]->room->neighbors->key);
				temp[i]->room->neighbors = temp[i]->room->neighbors->next;
			}
			ft_printf("\n");
		}
		else
			ft_printf("|NULL\t\tNULL\t\n");
		i += 1;
	}
	ft_printf("-------------------------\n");
}
