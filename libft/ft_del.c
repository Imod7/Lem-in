/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_del.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/11 14:45:06 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/05/02 12:54:30 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_del(void *content, size_t content_size)
{
	free(content);
	content = NULL;
	content_size = 0;
}
