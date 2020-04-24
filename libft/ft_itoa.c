/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/03 11:58:28 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/05/02 12:55:32 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void		make_str(char *str, long n, int len)
{
	int			i;

	str[len + 1] = '\0';
	i = 0;
	while (len >= i)
	{
		if (n < 0)
		{
			str[0] = 45;
			n = n * (-1);
			i = 1;
		}
		if (n >= 0 && n <= 9)
		{
			str[len] = n + 48;
		}
		if (n > 9)
		{
			str[len] = (n % 10) + 48;
			n = n / 10;
		}
		len--;
	}
}

static int		count_len(long n)
{
	int			len;

	len = 0;
	if (n < 0)
	{
		len++;
		n = n * (-1);
	}
	if (n >= 0 && n <= 9)
		len++;
	else if (n > 9)
	{
		len = len + count_len(n / 10);
		len = len + count_len(n % 10);
	}
	return (len);
}

char			*ft_itoa(int n)
{
	int			len;
	char		*str;
	long		n1;

	n1 = 1 * (long)n;
	len = count_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	make_str(str, n1, len - 1);
	return (str);
}
