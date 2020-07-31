/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lines_move.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 11:22:55 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/29 11:25:09 by dsaripap      ########   odam.nl         */
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
	// ft_printf(">> Calculate Lines - Current Run : %d \n", ant_farm->best_run);
	while (paths != NULL) // && paths->run == ant_farm->best_run)
	{
		if (paths->ants_lst != NULL && paths->run == ant_farm->best_run)
		{
			// ft_printf("...path_id %d, paths_size %d, path run %d\n", paths->path_id, paths->path_size, paths->run);
			// ft_printf("path_id %d, paths_size %d, ants %d\n", paths->path_id, paths->path_size, paths->ants_amount);
			total_size = paths->path_size + paths->ants_amount;
			if (total_size > max_lines)
				max_lines = total_size;
		}
		paths = paths->next;
	}
	ant_farm->lines = max_lines - 2;
	// ft_printf(ANSI_COLOR_CYAN"Lines Needed: %d \n\n", ant_farm->lines);
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
