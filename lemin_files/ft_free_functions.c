/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 09:28:47 by dominique     #+#    #+#                 */
/*   Updated: 2020/04/24 09:29:05 by dominique     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			ft_free_inputlst(t_input *input_lst)
{
	t_input		*curr_node;
	t_input		*next_node;

	curr_node = input_lst;
	while (curr_node != NULL)
	{
		next_node = curr_node->next;
		free(curr_node);
		curr_node = next_node;
	}
	input_lst = NULL;
}
