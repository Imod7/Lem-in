/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_integer.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/13 13:53:58 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/10/13 13:54:02 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void			print_num(long long arg, t_format *t_fl, t_print *t_pr, int len)
{
	if ((t_fl->argtype == 'b') && ((t_fl->flags & FLAG_ARG_ZERO) == 0))
		binary_number_int(arg, t_pr);
	else
		print_number_int(arg, t_fl, t_pr, len);
}

void			int_other(long long arg, t_format *t_fl, t_print *t_pr, int len)
{
	if ((t_fl->precision) < (t_fl->minfw) &&
	((t_fl->flags & FLAG_ZERO) == 0))
	{
		print_padding(t_fl, t_pr, len);
		print_sign(t_fl, t_pr);
		print_num(arg, t_fl, t_pr, len);
	}
	else
	{
		print_sign(t_fl, t_pr);
		print_padding(t_fl, t_pr, len);
		print_num(arg, t_fl, t_pr, len);
	}
}

void			int_minus(long long arg, t_format *t_fl, t_print *t_pr, int len)
{
	if (((t_fl->flags & FLAG_PRECIS) > 0) && \
	((t_fl->precision) > len) && \
	((t_fl->precision) >= (t_fl->minfw)))
	{
		print_sign(t_fl, t_pr);
		print_padding(t_fl, t_pr, len);
		print_num(arg, t_fl, t_pr, len);
	}
	else
	{
		print_sign(t_fl, t_pr);
		print_num(arg, t_fl, t_pr, len);
		print_padding(t_fl, t_pr, len);
	}
}

void			check_negative_int(long long *arg, t_format *t_flags, \
									t_print *t_prnt, int l)
{
	if (*arg < 0)
		t_flags->flags |= FLAG_NEGAT;
	if ((*arg < 0) && (t_flags->minfw == t_flags->precision))
		t_prnt->pad_len = t_flags->minfw - l;
}

/*
** function print_integer
** If the flag zero is SET then print first the format (plus sign)
** and then the zeros
** If flag zero is NOT SET and MINUS flag is NOT SET
** then first print the spaces and then the format
** Check Test 1, 2
*/

void			print_integer(va_list argptr, t_format *tflags, t_print *t_prnt)
{
	long long	arg;
	int			len;

	arg = va_arg(argptr, long long);
	check_plusflag(tflags);
	check_modifier(&arg, tflags);
	if (tflags->argtype == 'b')
		len = binary_length_int(arg);
	else
		len = number_of_digits(arg);
	check_negative_int(&arg, tflags, t_prnt, len);
	minfw_vs_precision(tflags, t_prnt, len);
	if (arg == 0)
		check_arg_zero(tflags, &len, t_prnt);
	if ((tflags->flags & FLAG_MINUS) > 0)
	{
		tflags->flags &= ~FLAG_ZERO;
		int_minus(arg, tflags, t_prnt, len);
	}
	else
		int_other(arg, tflags, t_prnt, len);
}
