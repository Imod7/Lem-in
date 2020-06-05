/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_format.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/15 20:09:35 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/12/15 20:09:38 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void		set_diff(t_format *t_flags, t_print *t_prnt, int arg_digits_len)
{
	if ((!(t_prnt->diff)) && (t_flags->precision == t_flags->minfw) &&
	(t_flags->flags & FLAG_ARG_ZERO))
		t_prnt->diff = t_prnt->pad_len - t_flags->precision;
	else if (t_prnt->diff != -1)
	{
		t_prnt->diff = (t_prnt->pad_len - t_flags->precision) + \
		arg_digits_len + t_flags->specialchars_printed;
	}
	if ((t_prnt->diff) && (t_prnt->sign_printed == 1) && \
	(t_flags->precision >= t_flags->minfw))
		t_prnt->diff -= 1;
}

void		set_pad_len(t_format *t_flags, t_print *t_prnt, int arg_digits_len)
{
	if ((t_prnt->sign_printed == 0) &&
	(t_flags->flags & (FLAG_PLUS | FLAG_MINUS | FLAG_NEGAT)))
		t_flags->specialchars_printed += 1;
	if (!(t_prnt->pad_len) && (!(t_flags->flags & FLAG_ARG_ZERO)))
	{
		t_prnt->pad_len = t_flags->minfw - \
		t_flags->specialchars_printed - arg_digits_len;
	}
	else if (!(t_prnt->pad_len) && (t_flags->flags & FLAG_ARG_ZERO))
	{
		if ((t_flags->precision == 0) && (!(t_flags->flags & FLAG_PRECIS)))
			t_prnt->pad_len = t_flags->minfw - arg_digits_len - \
			t_flags->specialchars_printed;
		else
		{
			if ((t_flags->flags & (FLAG_MINUS | FLAG_PLUS)) || \
			((t_flags->argtype == 'p') && \
			(t_flags->precision > arg_digits_len)))
				t_prnt->pad_len = t_flags->minfw - t_flags->precision - \
				t_flags->specialchars_printed;
			else
				t_prnt->pad_len = t_flags->minfw - t_flags->precision;
		}
	}
	set_diff(t_flags, t_prnt, arg_digits_len);
}

/*
** If FLAG_PLUS or FLAG_NEGAT is set AND FLAG_ZERO is not set
** then we need to increase the specialchars_printed
*/

void		print_padding(t_format *t_flags, t_print *t_prnt, \
							int arg_digits_len)
{
	int		i;
	int		c;
	int		flag_diff;

	flag_diff = 0;
	set_pad_len(t_flags, t_prnt, arg_digits_len);
	i = 0;
	while (i < t_prnt->pad_len)
	{
		if (t_flags->flags & FLAG_ZERO)
			c = '0';
		else
			c = ' ';
		if ((t_flags->flags & FLAG_PRECIS) && (t_flags->argtype != 's') && \
		(t_flags->argtype != 'c') && (i >= t_prnt->diff) &&
		(t_prnt->diff >= 0))
		{
			c = '0';
			flag_diff = -1;
		}
		t_prnt->writer(&c, 1, t_prnt);
		i++;
	}
	if (flag_diff == -1)
		t_prnt->diff = -1;
}

void		print_sign(t_format *t_flags, t_print *t_prnt)
{
	if ((t_flags->flags & FLAG_NEGAT) > 0)
	{
		t_flags->flags &= ~FLAG_SPACE;
		t_flags->flags &= ~FLAG_PLUS;
		t_prnt->writer(&"-", 1, t_prnt);
		t_flags->specialchars_printed++;
	}
	if ((t_flags->flags & FLAG_PLUS) > 0)
	{
		t_prnt->writer(&"+", 1, t_prnt);
		t_flags->specialchars_printed++;
	}
	if ((t_flags->flags & FLAG_SPACE) && ((!(t_prnt->diff)) ||
	(t_prnt->pad_len <= 0)))
	{
		t_prnt->writer(&" ", 1, t_prnt);
		t_flags->specialchars_printed++;
	}
	t_prnt->sign_printed = 1;
}
