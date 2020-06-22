/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_base.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/13 00:20:08 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/08/13 00:58:43 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void					ft_putnbr_int(long long n, t_format *t_flags, \
									t_print *t_prnt)
{
	int					num;

	if (n < -9223372036854775807)
	{
		t_prnt->writer(&"9", 1, t_prnt);
		ft_putnbr_int(223372036854775808, t_flags, t_prnt);
	}
	if (n == -2147483648)
	{
		t_prnt->writer(&"2", 1, t_prnt);
		ft_putnbr_int(147483648, t_flags, t_prnt);
	}
	else if (n < 0)
		n = n * (-1);
	if (n >= 0 && n <= 9)
	{
		num = n + 48;
		t_prnt->writer(&num, 1, t_prnt);
	}
	if (n > 9)
	{
		ft_putnbr_int(n / 10, t_flags, t_prnt);
		ft_putnbr_int(n % 10, t_flags, t_prnt);
	}
}

void					ft_putnbr_un_int(unsigned long long n, \
								t_format *t_flags, t_print *t_prnt)
{
	int					num;

	if (n <= 9)
	{
		num = n + 48;
		t_prnt->writer(&num, 1, t_prnt);
	}
	if (n > 9)
	{
		ft_putnbr_un_int(n / 10, t_flags, t_prnt);
		ft_putnbr_un_int(n % 10, t_flags, t_prnt);
	}
}

void					ft_putnbr_octal(unsigned long long n, \
								t_format *t_flags, t_print *t_prnt)
{
	unsigned long long	num;

	if (n < 8)
	{
		num = n + 48;
		t_prnt->writer(&num, 1, t_prnt);
	}
	if (n >= 8)
	{
		ft_putnbr_octal(n / 8, t_flags, t_prnt);
		ft_putnbr_octal(n % 8, t_flags, t_prnt);
	}
}

void					ft_putnbr_hex(unsigned long long n, t_format *t_flags, \
								t_print *t_prnt)
{
	unsigned long long	num;

	if (n <= 9)
	{
		num = n + 48;
		t_prnt->writer(&num, 1, t_prnt);
	}
	if (n > 9 && n < 16)
	{
		num = n + 87;
		t_prnt->writer(&num, 1, t_prnt);
	}
	if (n >= 16)
	{
		ft_putnbr_hex(n / 16, t_flags, t_prnt);
		ft_putnbr_hex(n % 16, t_flags, t_prnt);
	}
}

void					ft_putnbr_hex_capit(unsigned long long n, \
									t_format *t_flags, t_print *t_prnt)
{
	unsigned long long	num;

	if (n <= 9)
	{
		num = n + 48;
		t_prnt->writer(&num, 1, t_prnt);
	}
	if (n > 9 && n < 16)
	{
		num = n + 55;
		t_prnt->writer(&num, 1, t_prnt);
	}
	if (n >= 16)
	{
		ft_putnbr_hex_capit(n / 16, t_flags, t_prnt);
		ft_putnbr_hex_capit(n % 16, t_flags, t_prnt);
	}
}
