/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_memory.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 15:29:34 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/11/26 15:29:38 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void				puthex(unsigned char c, size_t index, char *str_dec, \
						t_print *t_prnt)
{
	int				div;
	int				mod;
	char			*str_hex;

	div = c / 16;
	mod = c % 16;
	str_hex = "0123456789abcdef";
	t_prnt->writer(&str_hex[div], 1, t_prnt);
	t_prnt->writer(&str_hex[mod], 1, t_prnt);
	if (c > 32 && c < 127)
		str_dec[index % 16] = c;
	else
		str_dec[index % 16] = '.';
}

void				print_end(size_t index, size_t size, char *str_dec, \
								t_print *t_prnt)
{
	size_t			index_end;
	size_t			limit;

	index_end = index % 16;
	limit = index_end + ((16 - index_end) * 2);
	while ((index_end < limit) && (index_end != 0))
	{
		if ((index_end % 4 == 0) && (index_end != 0))
			t_prnt->writer(&" ", 1, t_prnt);
		write(1, &" ", 1);
		t_prnt->writer(&" ", 1, t_prnt);
		index_end += 1;
	}
	write(1, &" ", 1);
	if ((index == size) || (index == 0))
	{
		if (index % 16 != 0)
			t_prnt->writer(str_dec, index % 16, t_prnt);
		else
			t_prnt->writer(str_dec, 16, t_prnt);
	}
	t_prnt->writer(&"\n", 1, t_prnt);
}

void				print_memory(va_list argptr, t_print *t_prnt)
{
	unsigned char	*address;
	size_t			index;
	char			str_dec[16];
	long long		arg;
	size_t			size;

	arg = va_arg(argptr, long long);
	size = sizeof(arg);
	address = (unsigned char *)arg;
	index = 0;
	while (index < size)
	{
		if ((index % 2 == 0) && (index != 0) && (index % 16 != 0))
			t_prnt->writer(&" ", 1, t_prnt);
		if ((index % 16 == 0) && (index != 0))
		{
			t_prnt->writer(" ", 1, t_prnt);
			t_prnt->writer(str_dec, 16, t_prnt);
			if (index < size - 1)
				t_prnt->writer(&"\n", 1, t_prnt);
		}
		puthex(address[index], index, str_dec, t_prnt);
		index++;
	}
	print_end(index, size, str_dec, t_prnt);
}
