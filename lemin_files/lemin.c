/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lemin.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:39:57 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/09 09:57:12 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int			read_input(t_ant_farm *ant_farm)
{
	int				i;
	size_t			j;
	int				k;
	char			*returned_line;

	i = 1;
	k = 0;
	j = 0;
	while (i > 0)
	{
		i = get_next_line(0, &returned_line);
		if (i != 0)
		{
			// ft_printf("line = %s , i = %d, j = %d\n", returned_line, i, j);
			ft_saveinput(ant_farm, returned_line, &j);
			// if (ant_farm->signal == -7)
			// ft_printf("signal = %d\n", ant_farm->signal);
			if (ant_farm->signal == success_ants_saved)
			{
				j += 1;
			}
			else if (ant_farm->signal != SUCCESS && \
			ant_farm->signal != CONTINUE)
			{
				return (ERROR);
			}
		}
		else if (i == 0 && j == 0)
		{
			// ft_printf("empty file \n");
			// ft_printf("i = %d , j = %d\n", i, j);
			return (ft_exit_msg(ant_farm, error_empty_file));
		}
		// free(returned_line);
	}
	i = check_dup_rooms_lst(&ant_farm->rooms_lst);
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
	if (read_input(ant_farm) != SUCCESS)
		return (ft_exitprogram(ant_farm));
	// print_input_list(ant_farm->input);
	// ft_print_rooms_list(ant_farm->rooms_lst);
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
	if (ft_bfs_runs(ant_farm) != SUCCESS)
		return (ft_exitprogram(ant_farm));
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
	if (ant_farm->options & OPTION_L)
		ft_printf(ANSI_COLOR_BLUE"\nNumber of lines %d\n"ANSI_COLOR_RESET, \
		ant_farm->lines);
	// ft_print_paths_list(ant_farm);
	// ft_print_paths_list_detail(ant_farm);
	ft_exitprogram(ant_farm);
	// while (1)
	// 	;
	return (SUCCESS);
}
