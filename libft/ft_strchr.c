/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/30 14:23:52 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/04 19:30:13 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strchri(const char *str, char c)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			j++;
		i++;
	}
	return (j);
}

char		*ft_strchr(const char *s, int c)
{
	char	c1;
	char	*s1;
	int		i;

	s1 = (char *)s;
	c1 = (char)c;
	i = 0;
	while (s1[i] != c1 && s1[i] != '\0')
		i++;
	if (s1[i] == c)
		return (&s1[i]);
	else
		return (NULL);
}
