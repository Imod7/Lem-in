/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/10 14:26:12 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/05/02 12:57:49 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int			ft_lstlen(t_list *lst)
{
	t_list	*temp;
	int		len;

	temp = lst;
	len = 0;
	if (temp == NULL)
		return (len);
	while (temp != NULL)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}
