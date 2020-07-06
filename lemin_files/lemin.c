/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lemin.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:39:57 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/06 16:40:56 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int			read_input(t_ant_farm *ant_farm)
{
	int				i;
	size_t			j;
	char			*returned_line;

	i = 1;
	j = 0;
	ant_farm->rooms = 0;
	while (i > 0)
	{
		i = get_next_line(0, &returned_line);
		if (i != 0)
		{
			// ft_printf("line = %s\n", returned_line);
			ft_saveinput(ant_farm, returned_line, &j);
			// ft_printf("signal = %d\n", ant_farm->signal);
			if (ant_farm->signal == success_ants_saved)
			{
				j += 1;
			}
			else if ((ant_farm->signal != SUCCESS) && \
			(ant_farm->signal != CONTINUE))
			{
				free(returned_line);
				return (ERROR);
			}
		}
		free(returned_line);
	}
	return (0);
}

int					main(int argc, char **argv)
{
	t_ant_farm		*ant_farm;

	ant_farm = (t_ant_farm *)(ft_memalloc(sizeof(t_ant_farm)));
	// ft_printf("argc = %d \n", argc);
	// exit(1);
	if ((argc > 1) && (set_prgm_options(argv[1], ant_farm) != CONTINUE))
		return (SUCCESS);
	if (read_input(ant_farm) == ERROR)
		return (ft_exitprogram(ant_farm));
	print_input_list(ant_farm->input);
	// print_rooms_list(ant_farm->rooms_lst);
	ft_hashing_process(ant_farm);
	// print_hash_table(ant_farm->hash_table);
	if (ft_save_neighbors(ant_farm) != SUCCESS)
		return (ft_exitprogram(ant_farm));
	// print_neighbors_list(ant_farm->hash_table);
	// ft_printf("Amount of rooms : %d\n", ant_farm->rooms);
	// ft_printf("\nRunning BFS\n");
	// ft_printf("===========\n");
	ft_bfs(ant_farm);
	ft_print_paths(ant_farm);
	// decision making based on ants
	// if (ant_farm->ants > 5)
	// {
	// ft_free_paths(ant_farm);
	// ft_printf("\nRunning DFS\n");
	// ft_printf("===========\n");
	// ft_dfs(ant_farm);
	// ft_print_paths(ant_farm);
	// }
	ft_ants_to_paths(ant_farm);
	// ft_print_ants_in_paths(ant_farm);
	// if (!(ant_farm->options & OPTION_M))
	// {
	ft_print_mapdata(ant_farm);
	ft_printf("its not set \n");
	// }
	// else
	ft_printf("its set \n");
	ft_move_ants(ant_farm);
	ft_exitprogram(ant_farm);
	// while (1)
	// 	;
	return (SUCCESS);
}
