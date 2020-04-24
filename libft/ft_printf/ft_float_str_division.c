/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_float_str_division.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 12:56:35 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/10/31 12:56:38 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void			frac_divide_by_two(char *fr)
{
	int			temp;
	int			len;
	int			index;
	int			carry;

	index = 2;
	carry = 0;
	len = ft_strlen(fr);
	if (fr[0] == '1')
	{
		fr[0] = '0';
		carry = 1;
	}
	while (index <= len)
	{
		if (fr[index] != 0)
			temp = fr[index] - '0';
		else
			temp = 0;
		temp = ((carry * 10) + temp) / 2;
		carry = fr[index] % 2;
		fr[index] = temp + '0';
		index++;
	}
}

void			prod_divide_by_two(short *pr)
{
	int			temp;
	int			len;
	int			index;
	int			carry;

	carry = 0;
	len = (FLOAT_MIDDLE - 1) + length_product(pr);
	if (pr[FLOAT_MIDDLE - 1] == '1')
	{
		pr[FLOAT_MIDDLE - 1] = '0';
		carry = 1;
	}
	index = FLOAT_MIDDLE + 1;
	while (index <= len)
	{
		if (pr[index] != 0)
			temp = pr[index] - '0';
		else
			temp = 0;
		temp = ((carry * 10) + temp) / 2;
		carry = pr[index] % 2;
		pr[index] = temp + '0';
		index++;
	}
}
