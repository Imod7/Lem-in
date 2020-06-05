/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_save_hash_items.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/03 10:27:57 by dominique     #+#    #+#                 */
/*   Updated: 2020/05/04 10:59:50 by dominique     ########   odam.nl         */
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
	return (newnode);
}

void				ft_hashitem_addend(t_hash_item **lst, t_hash_item *new)
{
	t_hash_item		*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->colision_next != NULL)
		temp = temp->colision_next;
	temp->colision_next = new;
}
