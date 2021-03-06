/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lines_move.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 11:22:55 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 14:08:00 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** Precalculation of the number of lines we are going to need to move
** all the ants from source room to sink.
** The final result lines is max_lines - 2 because in the path_size
** source room and sink room are included but while moving the ants
** we do not need to include them in the lines.
** The reason is because in the beginning the subject assumes that
** all ants are at the source room so we start printing lines from the
** next room. Here we save 1 line.
** Also, as soon as the last ant reached the end we are over so we do not
** an extra line to move the ant from sink to somewhere else. And here we save
** the second line.
*/

void				ft_calculate_lines(t_ant_farm *ant_farm)
{
	t_paths			*paths;
	size_t			total_size;
	size_t			max_lines;

	max_lines = 0;
	paths = ant_farm->paths;
	while (paths != NULL)
	{
		if (paths->ants_lst != NULL && paths->run == ant_farm->best_run)
		{
			total_size = paths->path_size + paths->ants_amount;
			if (total_size > max_lines)
				max_lines = total_size;
		}
		paths = paths->next;
	}
	ant_farm->lines = max_lines - 2;
}

/*
** Function that adds a line in the lines_list
** This helps us compare the lines (needed to move the ants) between paths
*/

void				ft_lines_list_addend(t_lines **lst, t_lines *new)
{
	t_lines			*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}
