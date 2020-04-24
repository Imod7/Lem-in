/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/27 15:05:42 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/05/02 13:22:25 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void				*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*my_s;
	unsigned char	my_c;
	unsigned char	*found;
	size_t			i;

	my_s = (unsigned char *)s;
	my_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (my_c == *my_s)
		{
			found = my_s;
			return (found);
		}
		else
		{
			my_s++;
			i++;
		}
	}
	my_s = NULL;
	return (my_s);
}
