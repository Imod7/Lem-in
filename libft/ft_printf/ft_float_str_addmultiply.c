/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_float_str_addmultiply.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 12:55:48 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/10/31 12:55:52 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void			check_carry_and_sum(short *pr, char *fr, int carry)
{
	int			sum;

	if (carry > 0)
	{
		sum = (pr[FLOAT_MIDDLE - 1] - '0');
		sum++;
		pr[FLOAT_MIDDLE - 1] = sum + '0';
	}
	sum = (pr[FLOAT_MIDDLE - 1] - '0') + (fr[0] - '0');
	pr[FLOAT_MIDDLE - 1] = sum + '0';
}

int				length_fraction(char *fr)
{
	size_t		index;
	int			len;

	index = 0;
	len = 0;
	while (fr[index] != 0)
	{
		index++;
		len++;
	}
	return (len);
}

void			str_add_prod_frac(short *pr, char *fr)
{
	int			len_pr;
	int			len_fr;
	int			index;
	int			sum;
	int			carry;

	len_pr = length_product(pr);
	len_fr = length_fraction(fr);
	index = len_pr;
	while (index < len_fr)
	{
		pr[FLOAT_MIDDLE - 1 + index] = '0';
		index++;
	}
	index = len_fr;
	carry = 0;
	while (index > 2)
	{
		sum = (pr[FLOAT_MIDDLE - 1 + index - 1] - '0') + (fr[index - 1] - '0') \
		+ carry;
		pr[FLOAT_MIDDLE - 1 + index - 1] = (sum % 10) + '0';
		carry = sum / 10;
		index--;
	}
	check_carry_and_sum(pr, fr, carry);
}

void			check_carry(short *pr, int carry, int index)
{
	int			sum;

	while (carry > 0 || (pr[index] != 0))
	{
		if (pr[index] == 0)
			pr[index] = '0';
		sum = ((pr[index] - '0') * 2) + carry;
		pr[index] = (sum % 10) + '0';
		carry = sum / 10;
		index--;
	}
}

void			str_double(short *pr)
{
	int			index;
	int			carry;
	int			sum;
	int			dec_start;

	index = (FLOAT_MIDDLE - 1) + length_product_decpart(pr);
	carry = 0;
	dec_start = FLOAT_MIDDLE + 1;
	while (index >= dec_start)
	{
		sum = ((pr[index] - '0') * 2) + carry;
		pr[index] = (sum % 10) + '0';
		carry = sum / 10;
		index--;
	}
	sum = ((pr[FLOAT_MIDDLE - 1] - '0') * 2) + carry;
	pr[FLOAT_MIDDLE - 1] = (sum % 10) + '0';
	carry = sum / 10;
	index = FLOAT_MIDDLE - 2;
	check_carry(pr, carry, index);
}
