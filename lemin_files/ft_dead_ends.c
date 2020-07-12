/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dead_ends.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/11 14:22:11 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/11 19:00:48 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** In this function I want to delete the room that has only one neighbor
** from the hash table but also retrieve its neighbor to delete it from
** its neighbor's neighbors list too.
*/


/* Function to delete a node in a Doubly Linked List. 
   head_ref --> pointer to head node pointer. 
   del  -->  pointer to node to be deleted. */
// void deleteNode(struct Node** head_ref, struct Node* del) 
// { 

  
//     /* If node to be deleted is head node */
//     if (*head_ref == del) 
//         *head_ref = del->next; 
  
//     /* Change next only if node to be deleted is NOT the last node */
//     if (del->next != NULL) 
//         del->next->prev = del->prev; 
  
//     /* Change prev only if node to be deleted is NOT the first node */
//     if (del->prev != NULL) 
//         del->prev->next = del->next; 
  
//     /* Finally, free the memory occupied by del*/
//     free(del); 
//     return; 
// } 

static void			delete_item(t_hash_item *temp_item)
{
	// t_hash_item		*neighbor_item;
	t_neighbor		*neigbors_lst;
	t_neighbor		*temp;
	size_t			count;

	ft_printf(" temp_item %s \n", temp_item->room_name);
	neigbors_lst = temp_item->room->neighbors->hash_item->room->neighbors;
	ft_printf(" delete it first from the neightbors list of %s \n", temp_item->room->neighbors->hash_item->room->name);
	count = 0;
	while (neigbors_lst != NULL)
	{
		ft_printf(" neighbor %s \n", neigbors_lst->hash_item->room_name);
		if (ft_strcmp(temp_item->room_name, neigbors_lst->hash_item->room_name) == 0) 
		// if (temp_item->room_name == neigbors_lst->hash_item->room_name)
		{
			ft_printf("  Deleting neighbor %s \n", neigbors_lst->hash_item->room_name);
			temp = neigbors_lst->next;
			if (temp != NULL)
				ft_printf("  next %s \n", temp->hash_item->room->name);
			if (neigbors_lst->prev != NULL)
				neigbors_lst->prev->next = temp;
			else
			{
				temp_item->room->neighbors->hash_item->room->neighbors = temp;
				ft_printf("  prev is NULL %s \n", temp_item->room->neighbors->hash_item->room->neighbors->hash_item->room->name);
			}
			if ((temp != NULL) && (neigbors_lst != NULL))
				temp->prev = neigbors_lst->prev;
			else if ((temp != NULL) && (neigbors_lst == NULL))
				temp->prev = NULL;
			free(neigbors_lst);
			neigbors_lst = temp;
			if (neigbors_lst != NULL)
				ft_printf("  so now i continue from %s \n", neigbors_lst->hash_item->room_name);
		}
		if (neigbors_lst != NULL)
			neigbors_lst = neigbors_lst->next;
	}
	// ft_printf(" so now head is %s \n", temp_item->room->neighbors->hash_item->room->neighbors->hash_item->room->name);
	// ft_printf(" so now next of head is %s \n", temp_item->room->neighbors->hash_item->room->neighbors->next->hash_item->room->name);
	// ft_printf(" so now prev of head is %p \n", temp_item->room->neighbors->hash_item->room->neighbors->prev);
	// ft_printf(" so now next of next is %p \n", temp_item->room->neighbors->hash_item->room->neighbors->next->next);
	// ft_printf(" so now prev of next is %s \n", temp_item->room->neighbors->hash_item->room->neighbors->next->prev->hash_item->room->name);
	free(temp_item);
}

/*
** In this function I want to iterate through all the hash table
** and find the hash_items / rooms that have only one neighbor
** and that means they are dead ends.
** When I find one I call the function delete_item()
*/

void				delete_dead_ends(t_hash_table *hash_table)
{
	t_hash_item		**hash_item;
	t_neighbor		*neigbors_lst;
	t_hash_item		*temp_item;
	t_hash_item		*temp_itema;
	size_t			i;
	size_t			count;

	ft_printf("DEAD ENDS\n");
	hash_item = hash_table->array;
	i = 0;
	while (i < hash_table->size)
	{
		ft_printf("HASH ITEM [%d] \n", i);
		if (hash_item[i] != NULL)
		{
			neigbors_lst = hash_item[i]->room->neighbors;
			count = 0;
			while (neigbors_lst != NULL)
			{
				neigbors_lst = neigbors_lst->next;
				count += 1;
				if (count > 1)
					break ;
			}
			if (count == 1)
			{
				ft_printf("Deleting room %s \n", hash_item[i]->room->name);
				temp_item = hash_item[i]->colision_next;
				delete_item(hash_item[i]);
				hash_item[i] = temp_item;
				// print_neighbors_list(hash_table);
			}
			else
				temp_item = hash_item[i]->colision_next;
			// if (hash_item[i] != NULL)
			// {
			// 	temp_item = hash_item[i]->colision_next;
			// }
			// else
			// 	temp_item = NULL;
			while (temp_item != NULL)
			{
				ft_printf("Collision next temp_item %s \n", temp_item->room_name);
				neigbors_lst = temp_item->room->neighbors;
				count = 0;
				while (neigbors_lst != NULL)
				{
					// ft_printf("%s", neigbors_lst->hash_item->room_name);
					neigbors_lst = neigbors_lst->next;
					count += 1;
					if (count > 1)
						break ;
				}
				if (count == 1)
				{
					ft_printf("Deleting room %s \n", temp_item->room_name);
					temp_itema = temp_item->colision_next;
					if (temp_item->colision_prev != NULL)
						temp_item->colision_prev->colision_next = temp_itema;
					if (temp_itema != NULL)
						temp_itema->colision_prev = temp_item->colision_prev;
					delete_item(temp_item);
					temp_item = temp_itema;
					// print_neighbors_list(hash_table);
					if (temp_item != NULL)
						ft_printf("so now collision next is %s \n", temp_item->room_name);
					else
						ft_printf("so now collision next is NULL \n");
				}
				else
					temp_item = temp_item->colision_next;
				// if (hash_item[i] != NULL)
				// {
				// 	ft_printf("Colision next room %s \n", hash_item[i]->room->name);
				// 	temp_item = hash_item[i]->colision_next;
				// }
				// else
				// 	temp_item = NULL;
				// temp_item = temp_item->colision_next;
			}
		}
		i += 1;
	}
}
