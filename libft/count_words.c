/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   count_words.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 17:06:54 by svan-der      #+#    #+#                 */
/*   Updated: 2020/08/14 05:40:21 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		count_words(char const *s, char c)
{
	int		words;
	int		i;

	i = 0;
	words = 0;
	if (s != NULL)
	{
		while (s[i] != '\0')
		{
			if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
				words++;
			i++;
		}
		if ((s[0] != c) && (s[0] != '\0'))
			words++;
	}
	return (words);
}
