/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lemin.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 13:55:03 by dominique     #+#    #+#                 */
/*   Updated: 2020/04/24 09:49:03 by dominique     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int		read_input(t_ant_farm *ant_farm)
{
	int			i;
	size_t		j;
	int			result;
	char		*returned_line;

	i = 1;
	j = 0;
	ant_farm->rooms = 0;
	while (i > 0)
	{
		i = get_next_line(0, &returned_line);
		if (i != 0)
		{
			ft_printf("line = %s\n", returned_line);
			result = ft_saveinput(ant_farm, returned_line, &j);
			if (result == -1)
				return (-1);
			else if (result == 1)
				;
			else
				j += 1;
		}
	}
	ft_printf("Printing the input linked list\n");
	print_input_list(ant_farm->input);
	ft_printf("Amount of rooms : %d\n", ant_farm->rooms);
	return (0);
}

int				main()
{
	t_ant_farm	*ant_farm;

	ant_farm = ft_memalloc(sizeof(t_ant_farm));
	if (read_input(ant_farm) == -1)
		return (ft_exitprogram(ant_farm));
	ft_exitprogram(ant_farm);
	return (0);
}
