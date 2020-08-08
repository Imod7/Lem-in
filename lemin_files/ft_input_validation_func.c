/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_input_validation_func.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/07 19:07:43 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/07 19:08:57 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** Function that returns the size of the array after a strsplit
*/

size_t				array_size(char **array)
{
	size_t 			i;

	i = 0;
	while (array[i] != NULL)
	{
		// ft_printf("array %s\n", array[i]);
		i += 1;
	}
	return (i);
}
