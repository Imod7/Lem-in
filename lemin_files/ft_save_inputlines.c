/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_save_inputlines.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:39:29 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/06/19 10:39:31 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** Functions ft_input_newnode & ft_input_addend
** are used to save the lines of the input file
** into a linked list
** Should I put here ft_memalloc instead of malloc ?
*/

t_input				*ft_input_newnode(char *line)
{
	t_input			*newnode;

	newnode = malloc(sizeof(t_input));
	if (newnode == NULL)
		return (NULL);
	newnode->line = line;
	newnode->next = NULL;
	return (newnode);
}

void				ft_input_addend(t_input **lst, t_input *new)
{
	t_input			*temp;

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
