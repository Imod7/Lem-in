/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printing.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 07:44:52 by dominique     #+#    #+#                 */
/*   Updated: 2020/05/06 20:15:06 by dominique     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void				print_input_list(t_input *input_data)
{
	t_input			*temp;

	temp = input_data;
	ft_printf("\n   Linked List with Raw Input Lines      \n");
	ft_printf("-----------------------------------------\n");
	ft_printf("|line\t\t\tnext_line\t|\n");
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
	ft_printf("\n                      Rooms (Linked List)                \n");
	ft_printf("-----------------------------------------------------");
	ft_printf("------------------------------------\n");
	ft_printf("|room_name\troom_x_coord\troom_y_coord\troom_position\t");
	ft_printf("explored\tparent_room\tnext_room|\n");
	while (temp != NULL)
	{
		ft_printf("|%s\t\t%d\t\t%d", temp->name, temp->x_coord, temp->y_coord);
		ft_printf("\t\t%d\t\t%d\t\t", temp->position, temp->explored);
		if (temp->parent != NULL)
			ft_printf("%s\t\t", temp->parent->name);
		else
			ft_printf("NULL\t\t");
		if (temp->next != NULL)
			ft_printf("%s\t|\n", temp->next->name);
		else
			ft_printf("NULL\t|\n");
		temp = temp->next;
	}
	ft_printf("--------------------------------------------------------");
	ft_printf("---------------------------------\n");
}

void				print_hash_table(t_hash_table *hash_table)
{
	t_hash_item		**temp;
	t_hash_item		*temp_item;
	size_t			i;

	ft_printf("\n           Hash Table        \n");
	ft_printf("-------------------------------------------");
	ft_printf("------------------------------\n");
	ft_printf("|hashed_name/key\troom_name\tpoints_to_room\tcolision_next\t\t|\n");
	temp = hash_table->array;
	i = 0;
	while (i < hash_table->size)
	{
		if (temp[i] != NULL)
		{
			ft_printf("|%d\t\t\t", i);
			ft_printf("%s\t\t", temp[i]->room_name);
			ft_printf("%s\t\t", temp[i]->room->name);
			temp_item = temp[i]->colision_next;
			while(temp_item != NULL)
			{
				ft_printf("%s", temp_item->room_name);
				temp_item = temp_item->colision_next;
				if (temp_item)
					ft_printf(" -> ");
				else
					ft_printf("\t");
			}
			ft_printf("|\n");
		}
		else
			ft_printf("|NULL\t\t\tNULL\t\tNULL\t\tNULL\t\t\t|\n");
		i += 1;
	}
	ft_printf("-------------------------------------------");
	ft_printf("-----------------------------\n");
}

void				print_neighbors_list(t_hash_table *hash_table)
{
	t_hash_item		**hash_item;
	t_neighbor		*neigbors_lst;
	t_hash_item		*temp_item;
	size_t			i;

	hash_item = hash_table->array;
	ft_printf("\n          Hash Items - Rooms - Neighbors       \n");
	ft_printf("-------------------------------------------------\n");
	ft_printf("|hash_key\troom_name\tneighbors list\t\t|\n");
	i = 0;
	while (i < hash_table->size)
	{
		if (hash_item[i] != NULL)
		{
			ft_printf("%d\t\t", i);
			ft_printf("%s\t\t", hash_item[i]->room->name);
			neigbors_lst = hash_item[i]->room->neighbors;
			while (neigbors_lst != NULL)
			{
				ft_printf("%s", neigbors_lst->hash_item->room_name);
				neigbors_lst = neigbors_lst->next;
				if (neigbors_lst)
					ft_printf(" -> ");
				else
					ft_printf("\t\t|");
			}
			ft_printf("\n");
			temp_item = hash_item[i]->colision_next;
			while(temp_item != NULL)
			{
				ft_printf("%d\t\t", i);
				ft_printf("%s\t\t", temp_item->room_name);
				neigbors_lst = temp_item->room->neighbors;
				while (neigbors_lst != NULL)
				{
					ft_printf("%s", neigbors_lst->hash_item->room_name);
					neigbors_lst = neigbors_lst->next;
					if (neigbors_lst)
						ft_printf(" -> ");
					else
						ft_printf("\t|");
				}
				temp_item = temp_item->colision_next;
				ft_printf("\n");
			}
		}
		else
			ft_printf("|NULL\t\tNULL\t\tNULL\t\n");
		i += 1;
	}
	ft_printf("-----------------------------------------------\n");
}
