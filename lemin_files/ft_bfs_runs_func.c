/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bfs_runs_func.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/12 15:18:27 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 15:20:01 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static size_t		find_last_elem(t_lines *lines_lst)
{
	t_lines			*lines;

	lines = lines_lst;
	if (lines == NULL || lines->next == NULL)
		return (0);
	while (lines->next != NULL)
		lines = lines->next;
	return (lines->prev->lines);
}

int					ft_run_bfs_reset_score(t_ant_farm *ant_farm, \
											int flag_stop, size_t *i)
{
	t_lines			*temp;

	if (flag_stop == 0 && ant_farm->best_run != 1 && \
	ant_farm->lines > find_last_elem(ant_farm->lines_lst))
	{
		ft_bfs_fullreset_and_score(ant_farm);
		if (lvl_sink(ant_farm) != SUCCESS || lvl_source(ant_farm) != SUCCESS)
			return (ERROR);
		*i += 1;
		ant_farm->best_run = *i;
		if (ft_bfs_algorithm(ant_farm, *i) < 0)
			return (ERROR);
		ft_sort_paths_on_size(ant_farm);
		if (ft_ants_to_paths(ant_farm) != SUCCESS)
			return (ERROR);
		temp = (t_lines *)ft_memalloc(sizeof(t_lines));
		if (temp == NULL)
			return (ERROR);
		temp->lines = ant_farm->lines;
		temp->run = *i;
		ft_lines_list_addend(&(ant_farm->lines_lst), temp);
		flag_stop = 1;
		ft_paths_discovered(ant_farm);
	}
	return (SUCCESS);
}
