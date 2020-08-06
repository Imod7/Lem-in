/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/30 14:23:52 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/05 17:05:38 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
