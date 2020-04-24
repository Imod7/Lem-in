/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printing.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 07:44:52 by dominique     #+#    #+#                 */
/*   Updated: 2020/04/24 07:50:18 by dominique     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			print_input_list(t_input *input_data)
{
	t_input		*temp;

	temp = input_data;
	while (temp != NULL)
	{
		if (temp != NULL)
			ft_printf("%s\n", temp->line);
		temp = temp->next;
	}
}
