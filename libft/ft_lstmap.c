/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/08 13:26:11 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/05/02 13:20:07 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*result;

	if (lst == NULL)
		return (NULL);
	result = (*f)(lst);
	result->next = ft_lstmap(lst->next, f);
	return (result);
}
