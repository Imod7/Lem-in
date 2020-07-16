/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_save_hash_items.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:39:13 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/16 18:48:31 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_hash_item			*ft_hashitem_newnode(t_room *room)
{
	t_hash_item		*newnode;

	newnode = malloc(sizeof(t_hash_item));
	if (newnode == NULL)
		return (NULL);
	newnode->room_name = ft_strdup(room->name);
	newnode->room = room;
	newnode->colision_next = NULL;
	newnode->colision_prev = NULL;
	return (newnode);
}

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
