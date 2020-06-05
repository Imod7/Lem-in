/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_other.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/19 17:48:09 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/08/19 17:48:14 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void		write_string_arg(char *arg, t_format *t_flags, t_print *t_prnt, \
							int *len)
{
	if (((arg == NULL) && (!(t_flags->flags & FLAG_PRECIS))) ||
	((arg == NULL) && ((t_flags->flags & FLAG_PRECIS)) &&
	t_flags->precision != 0))
		t_prnt->writer(&"(null)", *len, t_prnt);
	else if (arg != NULL)
		t_prnt->writer(arg, *len, t_prnt);
}

void		check_null_string(char *arg, t_format *t_flags, int *len)
{
	if (((arg == NULL) && (!(t_flags->flags & FLAG_PRECIS))) ||
	((arg == NULL) && ((t_flags->flags & FLAG_PRECIS)) &&
	t_flags->precision != 0))
	{
		*len = 6;
	}
	else if (arg != NULL)
		*len = ft_strlen(arg);
	if (((t_flags->precision < *len) && (t_flags->precision > 0) \
	&& (*len != 0)) || ((t_flags->flags & FLAG_PRECIS) &&
	(t_flags->precision == 0) && (arg != NULL)))
		*len = t_flags->precision;
}

void		print_string(va_list argptr, t_format *t_flags, t_print *t_prnt)
{
	char	*arg;
	int		len;

	len = 0;
	arg = va_arg(argptr, char *);
	check_null_string(arg, t_flags, &len);
	print_sign(t_flags, t_prnt);
	if ((t_flags->flags & FLAG_MINUS) > 0)
	{
		if ((t_flags->flags & FLAG_PRECIS) && (t_flags->precision == 0))
			;
		else
			write_string_arg(arg, t_flags, t_prnt, &len);
		if (t_flags->minfw != 0)
			print_padding(t_flags, t_prnt, len);
	}
	else
	{
		if (t_flags->minfw != 0)
			print_padding(t_flags, t_prnt, len);
		if ((t_flags->flags & FLAG_PRECIS) && (t_flags->precision == 0))
			;
		else
			write_string_arg(arg, t_flags, t_prnt, &len);
	}
}

void		print_char(va_list argptr, t_format *t_flags, t_print *t_prnt)
{
	char	arg;
	int		len;

	arg = va_arg(argptr, int);
	len = 1;
	t_flags->flags &= ~FLAG_PLUS;
	t_flags->flags &= ~FLAG_SPACE;
	if (t_flags->flags & FLAG_MINUS)
	{
		t_prnt->writer(&arg, 1, t_prnt);
		print_sign(t_flags, t_prnt);
		print_padding(t_flags, t_prnt, len);
	}
	else
	{
		print_sign(t_flags, t_prnt);
		print_padding(t_flags, t_prnt, len);
		t_prnt->writer(&arg, 1, t_prnt);
	}
}

void		print_other(char arg, t_format *t_flags, t_print *t_prnt)
{
	int		len;

	len = 1;
	t_flags->flags &= ~FLAG_SPACE;
	t_flags->flags &= ~FLAG_PLUS;
	t_flags->precision = 0;
	if ((t_flags->flags & FLAG_MINUS) > 0)
	{
		t_prnt->writer(&arg, 1, t_prnt);
		print_sign(t_flags, t_prnt);
		print_padding(t_flags, t_prnt, len);
	}
	else
	{
		print_sign(t_flags, t_prnt);
		print_padding(t_flags, t_prnt, len);
		t_prnt->writer(&arg, 1, t_prnt);
	}
}
