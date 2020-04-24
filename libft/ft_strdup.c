/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/29 12:00:34 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/05/02 13:28:48 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char				*ft_strdup(const char *s1)
{
	unsigned char	*str1;
	char			*result;
	int				i;

	str1 = (unsigned char *)s1;
	i = 0;
	while (str1[i] != '\0')
		i++;
	result = (char *)malloc(sizeof(char) * (i + 1));
	if (result == NULL)
		return (NULL);
	else
	{
		i = 0;
		while (str1[i] != '\0')
		{
			result[i] = str1[i];
			i++;
		}
		result[i] = '\0';
	}
	return (result);
}
