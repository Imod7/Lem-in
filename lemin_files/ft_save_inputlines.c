/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_save_inputlines.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/25 18:36:58 by dominique     #+#    #+#                 */
/*   Updated: 2020/04/28 19:04:31 by dominique     ########   odam.nl         */
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
