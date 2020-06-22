/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/16 13:33:53 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/07/16 13:45:05 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int				ft_printf(const char *format, ...)
{
	va_list		argptr;
	int			result;
	t_format	t_flags;
	t_print		t_prnt;

	clear_formatstruct(&t_flags, &t_prnt);
	t_prnt.fd = 1;
	t_prnt.writer = writer_printf;
	va_start(argptr, format);
	initialize_buffer(&t_prnt);
	result = ft_printf_genericfunc(&t_flags, &t_prnt, format, argptr);
	va_end(argptr);
	return (result);
}

int				ft_dprintf(int fd, const char *format, ...)
{
	va_list		argptr;
	int			result;
	t_format	t_flags;
	t_print		t_prnt;

	clear_formatstruct(&t_flags, &t_prnt);
	t_prnt.fd = fd;
	t_prnt.writer = writer_printf;
	va_start(argptr, format);
	initialize_buffer(&t_prnt);
	result = ft_printf_genericfunc(&t_flags, &t_prnt, format, argptr);
	va_end(argptr);
	return (result);
}

int				ft_sprintf(char *str, const char *format, ...)
{
	va_list		argptr;
	int			result;
	t_format	t_flags;
	t_print		t_prnt;

	clear_formatstruct(&t_flags, &t_prnt);
	t_prnt.writer = writer_sprintf;
	t_prnt.sprintf_str = str;
	va_start(argptr, format);
	initialize_buffer(&t_prnt);
	result = ft_printf_genericfunc(&t_flags, &t_prnt, format, argptr);
	va_end(argptr);
	return (result);
}

int				ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list		argptr;
	int			result;
	t_format	t_flags;
	t_print		t_prnt;

	clear_formatstruct(&t_flags, &t_prnt);
	t_prnt.writer = writer_snprintf;
	t_prnt.sprintf_str = str;
	t_prnt.snprintf_size = size;
	va_start(argptr, format);
	initialize_buffer(&t_prnt);
	result = ft_printf_genericfunc(&t_flags, &t_prnt, format, argptr);
	va_end(argptr);
	return (result);
}
