/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lemin.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:39:57 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/11 08:32:54 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** Checks if the argument order of the data is correct
** so that the order of 1)ants_amount, 2)rooms and 3)links is valid
** and also that data doesn't pass that doesn't belong in that section
*/
static int		ft_precheck_if_valid(t_ant_farm *ant_farm, t_data *data, char *line, int i)
{
	(void)i;
	if (ft_strequ(data->argument, "ants_amount"))
	{
		if (ant_farm->signal == 1)
			data->argument = "room";
		else if (ant_farm->signal != 2 && ant_farm->signal != 0)
		{
			ft_printf("ERROR amounts of ants in line:%s signal:%i\n", line, ant_farm->signal);
			data->valid = ERROR;
			return (ft_exit_msg(ant_farm, error_invalid_ants_amount));
		}
	}
	else if (ft_strequ(data->argument, "room"))
	{
		if (data->valid == 1 && ant_farm->signal == 5)
		{
			ft_printf("LINK CAME AFTER ROOM\n");
			data->valid = 0;
		}
		else if (data->valid == 0 && ant_farm->signal != 5)
		{
			ft_printf("ERROR invalid room data in line:%s\n", line);
			data->valid = ERROR;
			// if (ft_strequ("Urj0 1366 1366", line))
			// {
			// 	ft_printf("data:%s valid:%i signal:%i\n", data->argument, data->valid, ant_farm->signal);
			// 	exit(1);
			// }
			return (ft_exit_msg(ant_farm, error_invalid_room_data));
		}
		else if (data->valid == 0 && ant_farm->signal == 5)
		{
			ft_printf("TWO LINKS AFTER EACH OTHER\n");
			data->valid = 1;
			data->argument = "link";
		}
		ft_printf("GOOD ROOM\n");
	}
	else if (ft_strequ(data->argument, "link") && data->valid == 1)
	{
		if (ant_farm->signal != 5 && ant_farm->signal != 2 && ant_farm->signal != 0)
		{
			ft_printf("ERROR in link in line:%s\n", line);
			data->valid = ERROR;
			return (ft_exit_msg(ant_farm, error_in_link));
		}
		// data->valid = 1;
	}
	return (0);
}

static int			read_input(t_ant_farm *ant_farm, t_data **data)
{
	int				i;
	size_t			j;
	char			*returned_line;

	i = 1;
	j = 0;
	while (i > 0)
	{
		i = get_next_line(0, &returned_line);
		if (i != 0)
		{
			ft_saveinput(ant_farm, returned_line, &j, *data);
			ft_printf("line:%s valid:%i arg:%s i:%i j:%i signal:%i\n", returned_line, ant_farm->data->valid, ant_farm->data->argument, i, j, ant_farm->signal);
			if (ant_farm->signal == success_ants_saved)
			{
				j += 1;
			}
			else if ((ant_farm->signal != SUCCESS && \
			ant_farm->signal != CONTINUE && ant_farm->signal != succes_room_saved \
			&& ant_farm->signal != succes_link_saved)\
			|| (*data)->valid == ERROR)
			{
				// ft_printf("%i\n", ant_farm->signal);
				// ft_printf("data valid:%i\n", ant_farm->data->valid);
				return (ERROR);
			}
		}
		else if (i == 0 && j == 0)
			return (ft_exit_msg(ant_farm, error_empty_file));
		ft_precheck_if_valid(ant_farm, *data, returned_line, j);
		// if (ft_strequ("Urj0 1366 1366", returned_line))
		// {
		// 	ft_printf("data:%s valid:%i\n", data->argument, data->valid);
		// 	exit(1);
		// }
		if ((*data)->valid == ERROR)
			return (ERROR);
		ft_printf("line:%s datatype:%s valid:%i signal:%i\n", returned_line, ant_farm->data->argument, ant_farm->data->valid, ant_farm->signal);
	}
	ft_printf("going check dup_room\n");
	i = check_dup_rooms_lst(&ant_farm->rooms_lst);
	ft_printf("finished dup room:%i\n", i);
	if (i == -1)
		return (ft_exit_msg(ant_farm, error_invalid_room_data));
	return (SUCCESS);
}

int					main(int argc, char **argv)
{
	t_ant_farm		*ant_farm;

	ant_farm = (t_ant_farm *)(ft_memalloc(sizeof(t_ant_farm)));
	if ((argc > 1) && (set_prgm_options(argv[1], ant_farm) != CONTINUE))
		return (SUCCESS);
	ant_farm->data = (t_data *)ft_memalloc(sizeof(t_data));
	if (ant_farm->data == NULL)
		return (ERROR);
	ant_farm->data->valid = 1;
	ant_farm->data->argument = "ants_amount";
	if (read_input(ant_farm, &ant_farm->data) != SUCCESS)
		return (ft_exitprogram(ant_farm));
	print_input_list(ant_farm->input);
	ft_print_rooms_list(ant_farm->rooms_lst);
	if (ant_farm->rooms_lst == NULL)
	{
		ft_exit_msg(ant_farm, error_no_rooms);
		return (ft_exitprogram(ant_farm));
	}
	ft_hashing_process(ant_farm);
	// print_hash_table(ant_farm->hash_table);
	if (ft_save_neighbors(ant_farm) != SUCCESS)
		return (ft_exitprogram(ant_farm));
	// ft_print_neighbors_list(ant_farm->hash_table);
	// delete_dead_ends(ant_farm->hash_table);
	// ft_printf("Amount of rooms : %d\n", ant_farm->rooms);
	if (ft_check_links(ant_farm) != SUCCESS)
		return (ft_exitprogram(ant_farm));
	ft_bfs_level_sink(ant_farm);
	ft_bfs_level_source(ant_farm);
	ft_bfs_runs(ant_farm);
	ft_free_paths_ants_lst(ant_farm);
	ft_ants_to_paths(ant_farm);
	// ft_printf(ANSI_COLOR_BLUE" ============================================= \n");
	// ft_printf(" ****** BEST RUN %d - Lines needed %d ********** \n", ant_farm->best_run, ant_farm->lines);
	// ft_printf(" ============================================= \n"ANSI_COLOR_RESET);
	// ft_print_paths(ant_farm);
	// ft_print_paths_sizes(ant_farm);
	// ft_bfs_again(ant_farm, 2);
	// ft_printf("\nBFS AGAIN PATHS\n");
	// ft_print_paths(ant_farm);
	// ft_printf("\nRunning DFS\n");
	// ft_dfs(ant_farm);
	// ft_printf("\nDFS PATHS\n");
	// ft_print_paths(ant_farm);
	// ft_printf("\nRunning DFS from sink\n");
	// ft_dfs_from_sink(ant_farm);
	// ft_print_ants_in_paths(ant_farm);
	if (!(ant_farm->options & OPTION_M))
	{
		ft_print_mapdata(ant_farm);
		// ft_printf("its not set %d\n", ant_farm->options & OPTION_M);
	}
	// else
	// 	ft_printf("its set %d\n", ant_farm->options & OPTION_M);
	ft_move_ants(ant_farm);
	// ft_print_paths_list(ant_farm);
	// ft_print_paths_list_detail(ant_farm);
	ft_exitprogram(ant_farm);
	// while (1)
	// 	;
	return (SUCCESS);
}
