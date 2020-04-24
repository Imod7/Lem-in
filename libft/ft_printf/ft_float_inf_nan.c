/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_float_inf_nan.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/11 19:37:06 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/10/11 19:37:08 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int			check_exp_allones(t_float *tfloat)
{
	int		bit;
	int		pos;

	pos = 14;
	while (pos >= 0)
	{
		bit = tfloat->exponent[4] >> pos;
		if (bit & 1)
			pos--;
		else
			return (-1);
	}
	return (0);
}

int			check_mant_allzeros(t_float *tfloat)
{
	int		bit;
	int		pos;

	pos = 62;
	while (pos >= 0)
	{
		bit = tfloat->mantissa >> pos;
		if (bit & 1)
			return (-1);
		else
			pos--;
	}
	return (0);
}

void		fill_product(short *product, char *str)
{
	size_t	index;

	index = 0;
	while (*str != '\0')
	{
		product[index] = *str;
		str++;
		index++;
	}
	product[index] = '\0';
}

int			check_inf_nan(t_float *tfloat, t_format *t_flags, t_print *t_prnt, \
							short *product)
{
	if ((check_exp_allones(tfloat) == 0) && (check_mant_allzeros(tfloat) == 0))
	{
		t_prnt->diff = -1;
		t_flags->flags |= FLAG_INF_NAN;
		if ((tfloat->exponent[4] >> 15) & 1)
		{
			fill_product(product, "-inf");
			return (-1);
		}
		else
		{
			fill_product(product, "inf");
			return (1);
		}
	}
	else if ((check_exp_allones(tfloat) == 0) && \
	(check_mant_allzeros(tfloat) != 0))
	{
		t_prnt->diff = -1;
		t_flags->flags &= ~FLAG_PLUS;
		t_flags->flags |= FLAG_INF_NAN;
		fill_product(product, "nan");
		return (2);
	}
	return (0);
}
