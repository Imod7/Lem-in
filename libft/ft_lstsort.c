/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsort.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/10 18:41:45 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/05/02 13:21:27 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static	void	swap_nodes(t_list *node1, t_list *node2)
{
	void		*temp;
	size_t		size;

	temp = node1->content;
	size = node1->content_size;
	node1->content = node2->content;
	node1->content_size = node2->content_size;
	node2->content = temp;
	node2->content_size = size;
}

void			ft_lstsort(t_list **lst, int cmpf())
{
	t_list		*tmp;
	int			len;
	int			i;
	int			check;

	tmp = *lst;
	len = ft_lstlen(tmp);
	i = 0;
	while (i < len)
	{
		tmp = NULL;
		tmp = *lst;
		while (tmp != NULL && tmp->next != NULL)
		{
			check = cmpf(tmp->content, tmp->next->content);
			if (check > 0)
				swap_nodes(tmp, tmp->next);
			else
				tmp = tmp->next;
		}
		i++;
	}
}
