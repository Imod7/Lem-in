/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_save_hash_items.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:39:13 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/29 20:52:26 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** Function that mallocs a new node of type t_hash_item which is
** the item where we store a room and then add it to our hash table.
** We also malloc with strdup the memory necessary for the room name.
*/

t_hash_item			*ft_hashitem_newnode(t_room *room, unsigned int key)
{
	t_hash_item		*newnode;

	newnode = malloc(sizeof(t_hash_item));
	if (newnode == NULL)
		return (NULL);
	newnode->room_name = ft_strdup(room->name);
	newnode->room = room;
	newnode->colision_next = NULL;
	newnode->colision_prev = NULL;
	newnode->hashed_key = key;
	return (newnode);
}

/*
** Function that adds the hash item/hashed room in the hash table.
** Depending on which parameters are given when this function is called,
** the hashed room is either saved directly in a key in the hash table
** or if there is a colision it saves it the colision linked list
** related to this key. The function works the same, it changes only
** based on the parameters that are given. Check function ft_hashing_process
** to see the different calls of this function
*/

void				ft_hashitem_addend(t_hash_item **lst, t_hash_item *new)
{
	t_hash_item		*temp;

	// ft_printf("hash item add function %s\n", new->room->name);
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	// ft_printf("temp %s\n", temp->room->name);
	while (temp->colision_next != NULL)
	{
		// ft_printf("temp %s\n", temp->colision_prev->room->name);
		temp = temp->colision_next;
	}
	// ft_printf(" >> temp %s\n", temp->room->name);
	temp->colision_next = new;
	new->colision_prev = temp;
}
