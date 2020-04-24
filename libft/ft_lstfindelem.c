/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstfindelem.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/10 18:07:57 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/05/02 12:57:06 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int			ft_lstfindelem(t_list *lst, t_list *search_node)
{
	t_list	*temp;
	int		index;

	temp = lst;
	if (temp == NULL)
		return (0);
	index = 0;
	while (temp != NULL && temp != search_node)
	{
		index++;
		temp = temp->next;
	}
	if (temp != NULL)
		return (index);
	else
		return (0);
}
