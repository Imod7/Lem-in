/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_check_specifier.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/13 13:49:53 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/10/13 13:49:55 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void		check_modifier(long long *arg, t_format *t_flags)
{
	if (t_flags->modifier == N)
		*arg = (int)(*arg);
	else if (t_flags->modifier == h)
		*arg = (short)(*arg);
	else if (t_flags->modifier == hh)
		*arg = (signed char)(*arg);
	else if (t_flags->modifier == l)
		*arg = (long)(*arg);
	else if (t_flags->modifier == ll)
		*arg = (long long)(*arg);
}

void		check_modif_un(unsigned long long *arg, t_format *t_flags)
{
	if (t_flags->modifier == h)
		*arg = (unsigned short)(*arg);
	else if (t_flags->modifier == hh)
		*arg = (unsigned char)(*arg);
	else if (t_flags->modifier == l)
		*arg = (unsigned long)(*arg);
	else if (t_flags->modifier == ll)
		*arg = (unsigned long long)(*arg);
	else
		*arg = (unsigned int)(*arg);
}

void		asterisk_precision(va_list argptr, t_format *t_flags)
{
	int		aster_arg;

	aster_arg = va_arg(argptr, int);
	if (aster_arg < 0)
	{
		t_flags->precision = aster_arg;
	}
	else if ((t_flags->flags & FLAG_PRECIS) &&
	(t_flags->precision == 0))
		t_flags->precision = aster_arg;
}

void		check_asterisks(va_list argptr, t_format *t_flags)
{
	int		aster_arg;

	if (t_flags->flags & FLAG_ASTER_MINFW)
	{
		aster_arg = va_arg(argptr, int);
		if (t_flags->minfw == 0)
		{
			if (aster_arg < 0)
			{
				aster_arg = aster_arg * (-1);
				t_flags->flags |= FLAG_MINUS;
			}
			t_flags->minfw = aster_arg;
		}
	}
	if (t_flags->flags & FLAG_ASTER_PREC)
		asterisk_precision(argptr, t_flags);
}

/*
** If there is an asterisk then we have to retrieve the minimum width/precision
** from the argument list with va_arg
*/

void		print_arg(va_list argptr, t_format *t_flags, t_print *t_prnt)
{
	check_asterisks(argptr, t_flags);
	if (ft_strchr("bdi", t_flags->argtype) != 0)
		print_integer(argptr, t_flags, t_prnt);
	else if (t_flags->argtype == 's')
		print_string(argptr, t_flags, t_prnt);
	else if (t_flags->argtype == 'c')
		print_char(argptr, t_flags, t_prnt);
	else if (ft_strchr("opxX", t_flags->argtype) != 0)
		print_hexoctal(argptr, t_flags, t_prnt);
	else if (ft_strchr("Bu", t_flags->argtype) != 0)
		print_int_unsigned(argptr, t_flags, t_prnt);
	else if (t_flags->argtype == 'f')
		print_float(argptr, t_flags, t_prnt);
	else if (t_flags->argtype == 'm')
		print_memory(argptr, t_prnt);
	else
		print_other(t_flags->argtype, t_flags, t_prnt);
}
