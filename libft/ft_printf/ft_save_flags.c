/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_saveflags.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/08 15:07:14 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/08/08 15:07:17 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int					all_flags_retrieved(char str)
{
	if (str == '*' || str == '-' || str == '+')
		return (0);
	if (str == ' ' || str == '0' || str == '#')
		return (0);
	if (str == '.')
		return (0);
	if (str == 'h')
		return (0);
	if (str == 'l')
		return (0);
	if (str == 'L')
		return (0);
	if (ft_isdigit(str) == 1)
		return (0);
	return (1);
}

int					save_modifier(const char *str, t_format *t_flags)
{
	if ((str[0] == 'h') && (str[1] != 'h'))
		t_flags->modifier = h;
	if ((str[0] == 'h') && (str[1] == 'h'))
		t_flags->modifier = hh;
	if ((str[0] == 'l') && (str[1] != 'l'))
		t_flags->modifier = l;
	if ((str[0] == 'l') && (str[1] == 'l'))
		t_flags->modifier = ll;
	if (str[0] == 'L')
		t_flags->modifier = L;
	return (0);
}

void				minfw_precision_flags(t_format *t_flags, const char **str)
{
	int				digits;

	if ((ft_isdigit(**str) == 1) &&
	(t_flags->minfw == 0) &&
	(!(t_flags->flags & FLAG_PRECIS)))
	{
		t_flags->minfw = ft_atoi(*str);
		digits = number_of_digits(t_flags->minfw);
		(*str) = (*str) + digits - 1;
	}
	else if (**str == '.')
	{
		t_flags->flags |= FLAG_PRECIS;
		(*str)++;
		if ((ft_isdigit(**str) == 1) && \
		(t_flags->precision == 0))
		{
			t_flags->precision = ft_atoi(*str);
			digits = number_of_digits(t_flags->precision);
			(*str) = (*str) + digits - 1;
		}
		else
			(*str)--;
	}
}

void				save_flags(t_format *t_flags, const char **str)
{
	while (**str != '\0' && all_flags_retrieved(**str) == 0)
	{
		if ((**str == '*') && (!(t_flags->flags & FLAG_PRECIS)))
			t_flags->flags |= FLAG_ASTER_MINFW;
		else if ((**str == '*') && ((t_flags->flags & FLAG_PRECIS)))
			t_flags->flags |= FLAG_ASTER_PREC;
		else if (**str == '-')
			t_flags->flags |= FLAG_MINUS;
		else if (**str == '+')
			t_flags->flags |= FLAG_PLUS;
		else if (**str == ' ')
			t_flags->flags |= FLAG_SPACE;
		else if (**str == '0')
			t_flags->flags |= FLAG_ZERO;
		else if (**str == '#')
			t_flags->flags |= FLAG_HT;
		else if (((ft_isdigit(**str) == 1) &&
		(t_flags->minfw == 0)) || (**str == '.'))
			minfw_precision_flags(t_flags, str);
		else if ((**str == 'h' || **str == 'l' || **str == 'L') && \
		(t_flags->modifier == 0))
			save_modifier(*str, t_flags);
		(*str)++;
	}
	t_flags->argtype = **str;
}
