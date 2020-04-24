/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/02 15:46:21 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/05/02 13:34:46 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	count_spaces_end(char const *s, int len)
{
	int		i;
	int		spaces;

	i = len;
	spaces = 0;
	while (i > 0)
	{
		if (s[i - 1] == 32 || s[i - 1] == '\n' || s[i - 1] == '\t')
			spaces++;
		else
			break ;
		i--;
	}
	return (spaces);
}

static int	count_spaces_start(char const *s)
{
	int		i;
	int		spaces;

	i = 0;
	spaces = 0;
	while (s[i] != '\0')
	{
		if (s[i] == 32 || s[i] == '\n' || s[i] == '\t')
			spaces++;
		else
			break ;
		i++;
	}
	return (spaces);
}

char		*ft_strtrim(char const *s)
{
	char	*copy;
	int		i;
	int		sp_start;
	int		sp_end;
	int		len;

	i = 0;
	sp_start = 0;
	sp_end = 0;
	len = ft_strlen(s);
	sp_start = count_spaces_start(s);
	sp_end = count_spaces_end(s, len);
	if ((sp_start == len) && (sp_end == len))
		copy = "";
	else
	{
		copy = (char *)malloc(sizeof(char) * ((len - sp_start - sp_end) + 1));
		if (copy == NULL)
			return (NULL);
		copy = ft_strsub(s, sp_start, len - sp_start - sp_end);
	}
	return (copy);
}
