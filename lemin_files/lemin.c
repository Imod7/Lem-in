/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lemin.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 13:55:03 by dominique     #+#    #+#                 */
/*   Updated: 2020/06/03 08:55:20 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int			read_input(t_ant_farm *ant_farm)
{
	int				i;
	size_t			j;
	int				result;
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
			result = ft_saveinput(ant_farm, returned_line, &j);
			// ft_printf("result = %d\n", result);
			if (result == ERROR)
				return (ERROR);
			else if (result == CONTINUE)
				;
			else
				j += 1;
		}
	}
	return (0);
}

int					main(void)
{
	t_ant_farm		*ant_farm;

	ant_farm = (t_ant_farm *)(ft_memalloc(sizeof(t_ant_farm)));
	if (read_input(ant_farm) == ERROR)
		return (ft_exitprogram(ant_farm));
	print_input_list(ant_farm->input);
	print_rooms_list(ant_farm->rooms_lst);
	ft_hashing_process(ant_farm);
	print_hash_table(ant_farm->hash_table);
	if (ft_save_neighbors(ant_farm) == ERROR)
		return (ft_exitprogram(ant_farm));
	print_neighbors_list(ant_farm->hash_table);
	// ft_printf("Amount of rooms : %d\n", ant_farm->rooms);
	ft_printf("Running BFS\n");
	ft_bfs(ant_farm);
	ft_free_paths(ant_farm);
	ft_printf("Running DFS\n");
	ft_dfs(ant_farm);
	// ft_ants_to_paths(ant_farm);
	ft_exitprogram(ant_farm);
	// while (1)
	// 	;
	return (0);
}
