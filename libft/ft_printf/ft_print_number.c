/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_number.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/17 18:17:39 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/10/17 18:17:41 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int		check_binary(t_format *t_flags)
{
	if (((t_flags->argtype == 'B') && (t_flags->flags & FLAG_ARG_ZERO)) \
	|| ((t_flags->argtype == 'b') && (t_flags->flags & FLAG_ARG_ZERO))
	|| ((t_flags->argtype != 'B') && (t_flags->argtype != 'b')))
		return (1);
	else
		return (0);
}

void	print_unsigned_num(unsigned long long arg, t_format *t_flags, \
						t_print *t_prnt)
{
	if ((t_flags->argtype == 'B') && ((t_flags->flags & FLAG_ARG_ZERO) == 0))
		binary_number_unsigned_int(arg, t_prnt);
	else if (t_flags->argtype == 'X')
		ft_putnbr_hex_capit(arg, t_flags, t_prnt);
	else if ((t_flags->argtype == 'x') || \
	(t_flags->argtype == 'p'))
	{
		if (check_binary(t_flags) == 1)
			ft_putnbr_hex(arg, t_flags, t_prnt);
	}
	else if (t_flags->argtype == 'o')
	{
		if (check_binary(t_flags) == 1)
			ft_putnbr_octal(arg, t_flags, t_prnt);
	}
	else if ((t_flags->argtype == 'u') || \
	((t_flags->argtype == 'B') && (t_flags->flags & FLAG_ARG_ZERO)))
	{
		if (check_binary(t_flags) == 1)
			ft_putnbr_un_int(arg, t_flags, t_prnt);
	}
}

void	print_hex_pointer(unsigned long long arg, t_format *t_flags, \
						t_print *t_prnt)
{
	if ((arg != 0) || \
	((arg == 0) && ((t_flags->flags & NOFLAGS_MASK) == 0)) ||
	((arg == 0) && ((t_flags->flags & FLAG_HT) > 0) &&
	((t_flags->flags & FLAG_PRECIS) == 0)))
		print_unsigned_num(arg, t_flags, t_prnt);
}

void	print_number(unsigned long long arg, t_format *t_flags, \
					t_print *t_prnt, int len)
{
	if ((arg != 0) &&
	(t_flags->precision > len) &&
	(t_flags->precision <= t_flags->minfw))
		length_precision_diff(t_flags, t_prnt, len);
	if ((t_flags->argtype == 'u') || (t_flags->argtype == 'B'))
	{
		if ((arg != 0) || \
		((arg == 0) && (t_flags->minfw == 0) && \
		((t_flags->flags & NOFLAGS_MASK) == 0)))
			print_unsigned_num(arg, t_flags, t_prnt);
	}
	else if (t_flags->argtype == 'o')
	{
		if (arg != 0)
			print_unsigned_num(arg, t_flags, t_prnt);
	}
	else
		print_hex_pointer(arg, t_flags, t_prnt);
	if (arg == 0)
		print_padding_with_zeros(t_flags, t_prnt, len);
}

void	print_number_int(long long arg, t_format *t_flags, t_print *t_prnt, \
						int len)
{
	if ((arg != 0) || (t_flags->argtype == 'b'))
	{
		if ((t_flags->precision > len) && (t_flags->precision < t_flags->minfw))
			length_precision_diff(t_flags, t_prnt, len);
		if (check_binary(t_flags) == 1)
			ft_putnbr_int(arg, t_flags, t_prnt);
	}
	if (arg == 0)
		print_padding_with_zeros(t_flags, t_prnt, len);
}
