/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/31 13:53:55 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/05/02 13:31:04 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int					ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;
	size_t			l;

	l = 0;
	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while ((*c1 != '\0') && (*c2 != '\0') && (l < (n - 1)))
	{
		if (*c1 == *c2)
		{
			c1++;
			c2++;
			l++;
		}
		else
			return (*c1 - *c2);
	}
	return (*c1 - *c2);
}
