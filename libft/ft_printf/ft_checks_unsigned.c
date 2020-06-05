/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_checks_unsigned.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/13 13:43:06 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/10/13 13:43:08 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void		unsigned_minus(unsigned long long ar, t_format *t_flags,
						t_print *t_prnt, int len)
{
	if (((t_flags->precision) > len) &&
	((t_flags->precision) > (t_flags->minfw)))
	{
		print_inverse(t_flags, t_prnt, len);
		print_number(ar, t_flags, t_prnt, len);
	}
	else
	{
		print_number(ar, t_flags, t_prnt, len);
		print_inverse(t_flags, t_prnt, len);
	}
}

void		pointer_hashtag(t_format *t_flags, t_print *t_prnt)
{
	if (((t_flags->flags & FLAG_HT) > 0) && (t_flags->argtype == 'p'))
	{
		t_prnt->writer("0x", 2, t_prnt);
	}
	if ((t_flags->argtype == 'p') &&
	(t_flags->precision > t_flags->minfw))
		t_prnt->diff = 1;
}

void		unsigned_hashtag(unsigned long long arg, t_format *t_flags, \
							t_print *t_prnt, int len)
{
	char	c;

	if (((t_flags->argtype == 'o') > 0) &&
	(arg != 0) && (t_flags->flags & FLAG_HT) &&
	t_flags->precision < len)
	{
		c = '0';
		t_prnt->writer(&c, 1, t_prnt);
		t_flags->specialchars_printed++;
	}
	if (((t_flags->flags & FLAG_HT) > 0) && (arg != 0) &&
	((t_flags->argtype == 'x') || (t_flags->argtype == 'X')))
	{
		if (t_flags->argtype == 'x')
			t_prnt->writer("0x", 2, t_prnt);
		else
			t_prnt->writer("0X", 2, t_prnt);
		if (t_flags->minfw > t_flags->precision)
			t_flags->specialchars_printed += 2;
	}
	pointer_hashtag(t_flags, t_prnt);
}
