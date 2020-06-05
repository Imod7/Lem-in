/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/30 14:39:19 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/05/02 13:33:33 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char		*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*found;
	char	*s1;
	char	c1;
	int		len;

	i = 0;
	found = 0;
	len = 0;
	s1 = (char *)s;
	c1 = (char)c;
	while (s1[len] != '\0')
		len++;
	while (i <= len)
	{
		if (s1[i] == c1)
			found = &s1[i];
		i++;
	}
	if (found == 0)
		return (NULL);
	else
		return (found);
}
