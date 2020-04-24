/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_zero_arg.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/17 18:49:42 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/10/17 18:49:45 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
** function check_arg_zero
** Setting pad_len here so when the print_format function
** is called the pad_len is already set
*/

void	check_arg_zero(t_format *t_flags, int *len, t_print *t_prnt)
{
	t_flags->flags |= FLAG_ARG_ZERO;
	if (t_flags->precision > t_flags->minfw)
		t_prnt->pad_len = -1;
	else if ((t_flags->minfw > t_flags->precision) && (t_flags->argtype == 'p'))
		t_prnt->pad_len = t_flags->minfw - t_flags->specialchars_printed - *len;
	else if ((t_flags->minfw > t_flags->precision) && \
	(!(t_flags->flags & (FLAG_HT & FLAG_ZERO))) && (t_flags->precision != 0))
		t_prnt->pad_len = t_flags->minfw - t_flags->precision;
	if (((t_flags->flags & (FLAG_PLUS & FLAG_PRECIS)) && \
	(!(t_prnt->pad_len))) || ((t_flags->flags & (FLAG_HT)) && \
	(t_flags->argtype == 'o') && (t_flags->precision == 0)) || \
	(ft_strchr("Bb", t_flags->argtype) != 0))
		t_prnt->pad_len = t_flags->minfw - *len;
	else if (t_flags->flags & (FLAG_PLUS) && \
	(!(t_flags->flags & FLAG_PRECIS)) && (!(t_prnt->pad_len)))
		t_prnt->pad_len = t_flags->minfw - 2;
	else if (t_flags->flags & (FLAG_PLUS) && (t_prnt->pad_len))
		t_prnt->pad_len -= 1;
	if ((t_flags->flags & FLAG_SPACE) && (t_flags->flags & FLAG_MINUS))
	{
		if (t_flags->precision == 0)
			t_prnt->pad_len = t_flags->minfw - *len - 1;
		else
			t_prnt->pad_len = t_flags->minfw - t_flags->precision - 1;
	}
}

void	minfw_bigger_precision_extra_checks(t_format *t_flags, \
								t_print *t_prnt, int len, int *diff)
{
	if (((t_flags->flags & (FLAG_PLUS | FLAG_SPACE)) && \
	(t_flags->flags & FLAG_PRECIS)) ||
	((t_flags->flags & FLAG_HT) && (ft_strchr("xX", t_flags->argtype) > 0)))
		*diff = t_flags->precision;
	else if (((t_flags->flags & (FLAG_PLUS | FLAG_HT | FLAG_SPACE)) ||
	(((t_flags->flags & NOFLAGS_MASK) == 0) && \
	(ft_strchr("xX", t_flags->argtype) != 0))) && \
	(!(t_flags->flags & (FLAG_PRECIS))))
	{
		if (((t_flags->flags & FLAG_HT) && (t_flags->argtype == 'o')) ||
		((t_flags->flags & FLAG_SPACE) && (!(t_flags->flags & FLAG_ZERO)) \
		&& (ft_strchr("di", t_flags->argtype) > 0)))
			*diff = t_flags->minfw - t_prnt->pad_len;
		else
			*diff = t_flags->minfw - t_prnt->pad_len - 1;
	}
	else
		*diff = t_flags->minfw - t_prnt->pad_len;
	if ((t_flags->flags & (FLAG_HT & FLAG_ZERO)) && \
	(t_flags->argtype == 'o') && (t_flags->precision == 0))
		t_prnt->pad_len = len;
}

void	minfw_bigger_precision(t_format *t_flags, t_print *t_prnt, int len,\
								int *diff)
{
	if (t_prnt->pad_len <= 0)
	{
		if ((t_flags->precision == 0) && \
		((t_flags->argtype != 'o') ||
		(!((t_flags->argtype == 'o') && (t_flags->flags & FLAG_MINUS) &&
		((t_flags->flags & (FLAG_PRECIS)) > 0))) ||
		((t_flags->argtype == 'o') && (t_flags->flags & (FLAG_HT)))))
			t_prnt->pad_len = t_flags->minfw - len;
		else
			t_prnt->pad_len = t_flags->minfw - t_flags->precision;
	}
	if ((t_flags->flags & (FLAG_HT | FLAG_SPACE | FLAG_MINUS | FLAG_PLUS))
	&& ((t_flags->flags & (FLAG_PRECIS)))
	&& (t_flags->precision == 0) && \
	(ft_strchr("o", t_flags->argtype) == 0))
	{
		t_prnt->pad_len = 0;
		*diff = 0;
	}
	else
		minfw_bigger_precision_extra_checks(t_flags, t_prnt, len, diff);
}

void	length_diff_zeros_unsigned(t_format *t_flags, t_print *t_prnt, int len,\
									int *diff)
{
	if (t_flags->minfw == t_flags->precision)
	{
		if (t_flags->minfw != 0)
			*diff = t_flags->precision;
		else if ((t_flags->minfw == 0) &&
		((!((t_flags->flags & (FLAG_PRECIS)) && t_flags->precision == 0) && \
		(t_flags->argtype == 'o')) || (!((t_flags->flags & (FLAG_PRECIS))) && \
		(ft_strchr("di", t_flags->argtype) != 0)) || \
		(t_flags->flags & (FLAG_PLUS) && (t_flags->argtype == 'o')) ||
		((t_flags->flags & (FLAG_HT)) && (t_flags->argtype == 'o'))))
			*diff = len;
	}
	else if (t_flags->minfw > t_flags->precision)
		minfw_bigger_precision(t_flags, t_prnt, len, diff);
	else if (t_flags->minfw < t_flags->precision)
	{
		t_prnt->pad_len = 0;
		*diff = t_flags->precision;
	}
}

void	print_padding_with_zeros(t_format *t_flags, t_print *t_prnt, int len)
{
	int	diff;

	diff = 0;
	length_diff_zeros_unsigned(t_flags, t_prnt, len, &diff);
	if ((t_flags->argtype == 'p') && (t_flags->precision != 0))
		diff = t_flags->precision;
	else if ((t_flags->argtype == 'p') && (t_flags->precision == 0))
		diff = 0;
	if (diff > 0)
	{
		if ((t_flags->flags & FLAG_SPACE) && \
		(t_flags->flags & FLAG_MINUS) && (t_flags->precision == 0))
			diff -= 1;
		t_flags->specialchars_printed += diff;
	}
	while (diff > 0)
	{
		t_prnt->writer(&"0", 1, t_prnt);
		diff--;
	}
}
