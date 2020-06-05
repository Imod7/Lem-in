/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_float_auxfunctions.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/15 19:14:26 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/05/28 06:54:24 by dominique     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void		print_final_float(short *pr, t_format *t_flags, t_print *t_prnt)
{
	int		index;
	int		len;

	index = 0;
	len = 0;
	if (pr[0] == 0)
	{
		index = FLOAT_MIDDLE - 1;
		while ((pr[index] != 0) && (index >= 0))
		{
			index--;
			len++;
		}
		index += 1;
	}
	while ((pr[index] != 0) && (index <= FLOAT_TOTAL_LEN))
	{
		t_prnt->writer(&pr[index], 1, t_prnt);
		index++;
	}
	if ((t_flags->flags & FLAG_HT) && \
	(t_flags->precision == 0) && \
	(!(t_flags->flags & FLAG_INF_NAN)))
		t_prnt->writer(&".", 1, t_prnt);
}

void		check_precision(short *pr, t_format *t_flags)
{
	int		prec_index;
	int		len;
	int		temp;

	if ((t_flags->flags & FLAG_PRECIS) == 0)
		t_flags->precision = 6;
	temp = FLOAT_MIDDLE + 1;
	while (pr[temp] != 0)
		temp++;
	len = temp - (FLOAT_MIDDLE + 1);
	if (len < t_flags->precision)
	{
		prec_index = 1;
		while (prec_index <= (t_flags->precision - len))
		{
			pr[FLOAT_MIDDLE + len + prec_index] = '0';
			prec_index++;
		}
		pr[FLOAT_MIDDLE + len + prec_index] = 0;
	}
	else
		len_bigger_than_prec(pr, t_flags);
}
