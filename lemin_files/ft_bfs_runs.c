/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bfs_runs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/11 19:18:33 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 15:19:39 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static size_t		find_best_run(t_lines *lines_lst)
{
	t_lines			*temp;
	size_t			min;
	size_t			min_run;

	temp = lines_lst;
	min = 2147483647;
	while (temp != NULL)
	{
		if (temp->lines < min)
		{
			min = temp->lines;
			min_run = temp->run;
		}
		temp = temp->next;
	}
	return (min_run);
}

static int			bfs_result_positive(t_ant_farm *ant_farm, \
										int flag_stop, size_t *i)
{
	t_lines			*temp;

	ft_sort_paths_on_size(ant_farm);
	if (ft_ants_to_paths(ant_farm) != SUCCESS)
		return (ft_exit_msg(ant_farm, ERROR));
	temp = (t_lines *)ft_memalloc(sizeof(t_lines));
	if (temp == NULL)
		return (ERROR);
	temp->lines = ant_farm->lines;
	temp->run = *i;
	ft_lines_list_addend(&(ant_farm->lines_lst), temp);
	if (ft_run_bfs_reset_score(ant_farm, flag_stop, i) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int			ft_bfs_result_check(t_ant_farm *ant_farm, size_t *flag, \
										int flag_stop, size_t *i)
{
	int				result;

	result = ft_bfs_algorithm(ant_farm, *i);
	if (result > 0)
	{
		if (bfs_result_positive(ant_farm, flag_stop, i) != SUCCESS)
			return (ERROR);
	}
	else if (result == 0)
	{
		ant_farm->best_run = find_best_run(ant_farm->lines_lst);
		ft_paths_discovered(ant_farm);
		*flag = 1;
	}
	else
		return (ERROR);
	return (SUCCESS);
}

int					ft_bfs_runs(t_ant_farm *ant_farm)
{
	size_t			i;
	t_lines			*lines_lst;
	size_t			flag;
	int				flag_stop;

	i = 1;
	flag = 0;
	flag_stop = 0;
	lines_lst = ant_farm->lines_lst;
	ant_farm->discovered_paths = -1;
	ant_farm->max_paths = ft_find_maxpaths(ant_farm);
	while (!(ant_farm->discovered_paths == ant_farm->max_paths ||
	flag == 1 || ant_farm->discovered_paths == 0))
	{
		ant_farm->best_run = i;
		if (ft_bfs_result_check(ant_farm, &flag, flag_stop, &i) == ERROR)
			return (ERROR);
		if (ant_farm->best_run == 0)
			return (ft_exit_msg(ant_farm, error_no_solution));
		if (lvl_sink(ant_farm) != SUCCESS || lvl_source(ant_farm) != SUCCESS)
			return (ERROR);
		i += 1;
	}
	return (SUCCESS);
}
