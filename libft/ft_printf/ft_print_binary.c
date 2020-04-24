/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_binary.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/16 19:40:27 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/11/16 19:40:30 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int				binary_length_int(long long num)
{
	int			len;

	if (num < 0)
		num = num * (-1);
	len = 0;
	while (num)
	{
		num >>= 1;
		len++;
	}
	return (len);
}

void			binary_number_int(long long num, t_print *t_prnt)
{
	int			bit;
	int			pos;
	int			start;

	start = 0;
	if (num < 0)
		num = num * (-1);
	pos = 63;
	while (pos >= 0)
	{
		bit = num >> pos;
		if (bit & 1)
		{
			t_prnt->writer("1", 1, t_prnt);
			start = 1;
		}
		else
		{
			if (start == 1)
				t_prnt->writer("0", 1, t_prnt);
		}
		pos--;
	}
}

int				binary_length_unsigned_int(unsigned long long num)
{
	int			len;

	if (num < 0)
		num = num * (-1);
	len = 0;
	while (num)
	{
		num >>= 1;
		len++;
	}
	return (len);
}

void			binary_number_unsigned_int(unsigned long long num, \
											t_print *t_prnt)
{
	int			bit;
	int			pos;
	int			start;

	start = 0;
	if (num < 0)
		num = num * (-1);
	pos = 63;
	while (pos >= 0)
	{
		bit = num >> pos;
		if (bit & 1UL)
		{
			t_prnt->writer("1", 1, t_prnt);
			start = 1;
		}
		else
		{
			if (start == 1)
				t_prnt->writer("0", 1, t_prnt);
		}
		pos--;
	}
}
