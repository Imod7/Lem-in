/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsplit.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/02 17:50:21 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/05/02 13:33:48 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	fill_array(char **array, char const *s, char c, int words)
{
	int		i;
	int		j;
	int		len;
	int		found;

	i = 0;
	j = 0;
	while (j < words)
	{
		len = 0;
		found = 0;
		while (s[i] != '\0' && found == 0)
		{
			while (s[i] != c && s[i] != '\0')
			{
				len++;
				i++;
				found = 1;
			}
			i++;
		}
		if (len != 0)
			array[j] = ft_strsub(s, i - len - 1, len);
		j++;
	}
}

static int	count_words(char const *s, char c)
{
	int		words;
	int		i;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			words++;
		i++;
	}
	if ((s[0] != c) && (s[0] != '\0'))
		words++;
	return (words);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**array;
	int		words;

	words = count_words(s, c);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (array == NULL)
		return (NULL);
	fill_array(array, s, c, words);
	array[words] = 0;
	return (array);
}
