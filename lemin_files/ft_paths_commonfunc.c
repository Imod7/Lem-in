/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_paths_commonfunc.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:38:16 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/31 05:07:16 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** Function that adds a new path_list node at the start of the
** path list linked list.
** The path list node points to a specific room and the path list
** is pointed by a specific path so we are actually adding a room
** at the start of a specific path.
*/

void				ft_pathlst_addstart(t_path_list **lst, t_path_list *new)
{
	t_path_list		*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	*lst = new;
	new->next = temp;
	temp->prev = new;
}

/*
** Function that adds a new path_list node at the end of the
** path list linked list.
** The path list node points to a specific room and the path list
** is pointed by a specific path so we are actually adding a room
** at the end of a specific path.
*/

void				ft_pathlst_addend(t_path_list **lst, t_path_list *new)
{
	t_path_list		*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

/*
** Function that adds a path at the end of the linked list of paths
*/

void				ft_path_addend(t_paths **path, t_paths *new)
{
	t_paths			*temp;
	int				max;

	if (*path == NULL)
	{
		*path = new;
		new->path_id = 1;
		return ;
	}
	temp = *path;
	max = 0;
	while (temp != NULL)
	{
		if (temp->path_id > max)
			max = temp->path_id;
		// ft_printf("  temp->path id %d - max %d\n", temp->path_id, max);
		temp = temp->next;
	}
	temp = *path;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
	if (max == 0)
		max = 1;
	new->path_id = max + 1;
	// ft_printf("max %d so new path id %d\n", max, new->path_id);
}
