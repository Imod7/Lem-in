/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_float_len.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 09:57:25 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/10/30 09:57:27 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

size_t			left_to_dot(short *pr, int *len)
{
	size_t		index;

	index = FLOAT_MIDDLE - 1;
	while ((pr[index] != 0) && (index <= FLOAT_TOTAL_LEN))
	{
		index--;
		(*len)++;
	}
	return (index);
}

void			product_not_zero(short *pr, int *len)
{
	size_t		index;

	index = 0;
	while ((pr[index] == 0) && (index <= FLOAT_TOTAL_LEN))
		index++;
	while ((pr[index] != 0) && (index <= FLOAT_TOTAL_LEN))
	{
		index++;
		(*len)++;
	}
}

int				length_product(short *pr)
{
	size_t		index;
	int			len;

	len = 0;
	if (pr[0] == 0)
	{
		index = left_to_dot(pr, &len);
		index = FLOAT_MIDDLE + 1;
		while ((pr[index] != 0) && (index <= FLOAT_TOTAL_LEN))
		{
			index++;
			len++;
		}
		if (len != 1)
			len += 1;
	}
	else
		product_not_zero(pr, &len);
	return (len);
}

int				length_product_decpart(short *pr)
{
	size_t		index;
	int			len;

	index = FLOAT_MIDDLE + 1;
	len = 0;
	while (pr[index] != 0)
	{
		index++;
		len++;
	}
	return (len);
}

int				length_product_intpart(short *pr)
{
	size_t		index;
	int			len;

	len = 0;
	if (pr[0] == 0)
		index = left_to_dot(pr, &len);
	else
	{
		index = 0;
		while ((pr[index] == 0) && (index <= FLOAT_TOTAL_LEN))
		{
			index++;
		}
		while ((pr[index] != 0) && (index <= FLOAT_TOTAL_LEN) && \
		pr[index] != '.')
		{
			index++;
			len++;
		}
	}
	return (len);
}
