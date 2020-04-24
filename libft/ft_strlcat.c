/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/29 19:35:27 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/05/02 13:29:47 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_size;
	size_t	dst_size;
	size_t	total_size;
	size_t	i;

	src_size = 0;
	dst_size = 0;
	i = 0;
	while (src[src_size] != '\0')
		src_size++;
	if (size == 0)
		return (src_size + size);
	while (dst[dst_size] != '\0')
		dst_size++;
	total_size = src_size + dst_size;
	while ((dst_size < (size - 1)) && (src[i] != 0))
	{
		dst[dst_size] = src[i];
		dst_size++;
		i++;
	}
	dst[dst_size] = '\0';
	if (dst_size > size)
		return (src_size + size);
	return (total_size);
}
