/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strarrtolst.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/09 19:47:07 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/05/02 13:27:25 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list		*ft_strarrtolst(char **str)
{
	t_list	*node;
	t_list	*list_start;
	size_t	i;
	size_t	len;

	i = 0;
	while (str[i] != NULL)
	{
		len = ft_strlen(str[i]);
		node = ft_lstnew(str[i], len + 1);
		if (node == NULL)
		{
			ft_lstdel(&list_start, &ft_del);
			return (NULL);
		}
		ft_lstaddend(&list_start, node);
		i++;
	}
	return (list_start);
}
