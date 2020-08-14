/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchri.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 17:05:52 by svan-der      #+#    #+#                 */
/*   Updated: 2020/08/14 05:36:13 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strchri(const char *str, char c)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (str != NULL)
	{
		while (str[i])
		{
			if (str[i] == c)
				j++;
			i++;
		}
	}
	return (j);
}
