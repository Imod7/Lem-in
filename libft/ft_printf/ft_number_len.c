/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_number_len.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 10:07:36 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/10/30 10:07:38 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int			number_of_digits(long long num)
{
	size_t	digits;
	size_t	base;

	digits = 0;
	base = 10;
	if (num == 0)
		digits++;
	else if (num < 0)
	{
		if (num < -9223372036854775807)
			num = 9223372036854775807;
		else
			num = num * (-1);
	}
	while (num > 0)
	{
		num = num / base;
		digits++;
	}
	return (digits);
}

int			number_of_digits_un(unsigned long long num, t_format t_flags)
{
	size_t	digits;
	size_t	base;

	digits = 0;
	base = 10;
	if (t_flags.argtype == 'o')
		base = 8;
	else if ((t_flags.argtype == 'x') || (t_flags.argtype == 'X') || \
	(t_flags.argtype == 'p'))
		base = 16;
	else
		base = 10;
	if (num == 0)
		digits++;
	else
	{
		while (num > 0)
		{
			num = num / base;
			digits++;
		}
	}
	return (digits);
}
