/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_input_functions.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 07:59:04 by dominique     #+#    #+#                 */
/*   Updated: 2020/04/28 12:07:41 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** Should I put here ft_memalloc instead ?
** I don't think it really matters?
*/

t_input				*ft_input_newnode(char *line)
{
	t_input			*newnode;

	// newnode = ft_memalloc(sizeof(t_input));
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
