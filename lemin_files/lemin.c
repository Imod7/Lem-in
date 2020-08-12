/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lemin.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:39:57 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 17:16:44 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int	check_valid_input(t_ant_farm *ant_farm, int i, int j, int dup)
{
	if (i == -1)
		return (ft_exit_msg(ant_farm, error_file_missing));
	if (i == 0 && j == 0)
		return (ft_exit_msg(ant_farm, error_empty_file));
	if (dup == 1)
		return (check_dup_rooms_lst(&ant_farm->rooms_lst));
	return (SUCCESS);
}

static int	read_input(t_ant_farm *ant_farm, t_data **data)
{
	int				i;
	size_t			j;
	char			*returned_line;

	i = 1;
	j = 0;
	while (i > 0)
	{
		i = get_next_line(0, &returned_line);
		if (i != 0 && i != -1)
		{
			ft_saveinput(ant_farm, returned_line, &j, *data);
			if (ant_farm->signal == success_ants_saved)
				j += 1;
			else if (ft_precheck_if_valid(ant_farm, *data, 1) == -1)
				return (ERROR);
		}
		else if ((i == 0 && j == 0) || i == -1)
			return (check_valid_input(ant_farm, i, j, 0));
		if (ft_precheck_if_valid(ant_farm, *data, 0) != SUCCESS)
			return (ERROR);
	}
	if (check_valid_input(ant_farm, i, j, 1) != SUCCESS)
		return (ft_exit_msg(ant_farm, error_invalid_room_data));
	return (SUCCESS);
}

static int	set_and_retrieve(t_ant_farm *ant_farm, int argc, char *argv)
{
	if (ant_farm == NULL)
		return (ERROR);
	if ((argc > 1) && (set_prgm_options(argv, ant_farm) != CONTINUE))
		return (SUCCESS);
	ant_farm->data = (t_data *)ft_memalloc(sizeof(t_data));
	if (ant_farm->data == NULL)
		return (ERROR);
	ant_farm->data->valid = 1;
	ant_farm->data->argument = "ants_amount";
	if (read_input(ant_farm, &ant_farm->data) != SUCCESS)
		return (ERROR);
	if (ant_farm->rooms_lst == NULL)
	{
		ft_exit_msg(ant_farm, error_no_rooms);
		return (ERROR);
	}
	ft_hashing_process(ant_farm);
	return (CONTINUE);
}

int			main(int argc, char **argv)
{
	t_ant_farm		*ant_farm;
	int				ret;

	ant_farm = (t_ant_farm *)(ft_memalloc(sizeof(t_ant_farm)));
	ret = set_and_retrieve(ant_farm, argc, argv[1]);
	if (ret != CONTINUE)
		return (ret == ERROR ? ft_exitprogram(ant_farm) : SUCCESS);
	if (ft_save_neighbors(ant_farm) != SUCCESS)
		return (ft_exitprogram(ant_farm));
	if (ft_check_links(ant_farm) != SUCCESS)
		return (ft_exitprogram(ant_farm));
	ft_bfs_level_sink(ant_farm);
	ft_bfs_level_source(ant_farm);
	if (ft_bfs_runs(ant_farm) != SUCCESS)
		return (ft_exitprogram(ant_farm));
	ft_free_paths_ants_lst(ant_farm);
	ft_ants_to_paths(ant_farm);
	if (!(ant_farm->options & OPTION_M))
		ft_print_mapdata(ant_farm);
	ft_move_ants(ant_farm);
	if (ant_farm->options & OPTION_L)
		ft_printf(ANSI_COLOR_BLUE"\nNumber of lines %d\n"ANSI_COLOR_RESET, \
		ant_farm->lines);
	ft_exitprogram(ant_farm);
	return (SUCCESS);
}
