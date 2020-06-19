/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnequ.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/01 16:58:04 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/05/02 13:31:37 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int			ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (*s1 != '\0' && *s2 != '\0' && i < n && *s1 == *s2)
	{
		s1++;
		s2++;
		i++;
	}
	if ((*s1 == '\0' && *s2 == '\0') || (n == i) || (n == 0))
		return (1);
	else
		return (0);
}
