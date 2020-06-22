/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_writer_manager.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/20 14:24:25 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/11/20 14:24:29 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int					store_to_buffer(unsigned char **un_str, int len, \
									t_print *t_prnt, int i)
{
	while ((t_prnt->writer_index < BUFFER_SIZE) && (i < len))
	{
		if (t_prnt->print_end != 1)
		{
			t_prnt->buffer[t_prnt->writer_index] = **un_str;
			t_prnt->writer_index++;
			(*un_str)++;
		}
		i++;
	}
	if ((t_prnt->writer_index == BUFFER_SIZE) || (t_prnt->print_end == 1))
	{
		write(t_prnt->fd, t_prnt->buffer, t_prnt->writer_index);
		t_prnt->total_chars_printed += t_prnt->writer_index;
		t_prnt->writer_index = 0;
	}
	return (i);
}

void				writer_printf(const void *str, int len, t_print *t_prnt)
{
	int				i;
	unsigned char	*un_str;

	un_str = (unsigned char *)str;
	i = 0;
	if (len < BUFFER_SIZE)
		store_to_buffer(&un_str, len, t_prnt, i);
	else
	{
		while (i < len)
		{
			i = store_to_buffer(&un_str, len, t_prnt, i);
		}
	}
}

void				writer_sprintf(const void *str, int len, t_print *t_prnt)
{
	int				i;
	unsigned char	*un_str;

	un_str = (unsigned char *)str;
	i = 0;
	while (i < len)
	{
		t_prnt->sprintf_str[t_prnt->writer_index] = *un_str;
		t_prnt->writer_index++;
		un_str++;
		i++;
		if (t_prnt->print_end != 1)
			t_prnt->total_chars_printed += len;
	}
}

void				writer_snprintf(const void *str, int len, t_print *t_prnt)
{
	int				i;
	unsigned char	*un_str;

	un_str = (unsigned char *)str;
	i = 0;
	if (t_prnt->writer_index < t_prnt->snprintf_size - 1)
	{
		while (i < len)
		{
			t_prnt->sprintf_str[t_prnt->writer_index] = *un_str;
			t_prnt->writer_index++;
			un_str++;
			i++;
		}
		t_prnt->total_chars_printed += len;
	}
	else
		t_prnt->total_chars_printed++;
	if (t_prnt->print_end == 1)
	{
		if (t_prnt->snprintf_size != 0)
			t_prnt->sprintf_str[t_prnt->writer_index] = 0;
		t_prnt->total_chars_printed--;
	}
}
