/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_save_rooms.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 19:04:13 by dominique     #+#    #+#                 */
/*   Updated: 2020/04/28 19:04:36 by dominique     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** Functions ft_room_newnode & ft_room_addend
** are used to save the rooms of the input file
** into a linked list
** Should I put here ft_memalloc instead of malloc ?
*/

t_room				*ft_room_newnode(char *str)
{
	t_room			*newnode;

	newnode = malloc(sizeof(t_room));
	if (newnode == NULL)
		return (NULL);
	newnode->name = str;
	newnode->next = NULL;
	return (newnode);
}

void				ft_room_addend(t_room **lst, t_room *new)
{
	t_room			*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}
