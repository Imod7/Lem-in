/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_rooms_functions.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 18:00:20 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/14 06:20:02 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int			ft_check_start(t_ant_farm *ant_farm, char *line)
{
	int				result;

	if (!ft_strcmp(line, "##start"))
	{
		if (ft_get_start_room(ant_farm->rooms_lst) != NULL)
			return (ft_exit_msg(ant_farm, error_start_room_exists));
		result = ft_save_inputline(ant_farm, line, START);
		if (result >= -3 && result <= -1)
			return (ant_farm->signal);
		else if (result != SUCCESS)
			return (ft_exit_msg(ant_farm, error_invalid_start_room));
		ant_farm->signal = succes_room_saved;
		return (SUCCESS);
	}
	return (CONTINUE);
}

static int			ft_check_end(t_ant_farm *ant_farm, char *line)
{
	int				result;

	if (!ft_strcmp(line, "##end"))
	{
		if (ft_get_end_room(ant_farm) != NULL)
			return (ft_exit_msg(ant_farm, error_end_room_exists));
		result = ft_save_inputline(ant_farm, line, END);
		if (result >= -3 && result <= -1)
			return (ant_farm->signal);
		else if (result != SUCCESS)
			return (ft_exit_msg(ant_farm, error_invalid_end_room));
		ant_farm->signal = succes_room_saved;
		return (SUCCESS);
	}
	return (CONTINUE);
}

/*
** Function that checks if the line that we check from the input file
** (with the map data) is a start / end  / intermediate room.
*/

int					ft_check_if_is_room(t_ant_farm *ant_farm, char *line, \
										char *link, t_data *data)
{
	int				result;

	result = ft_check_start(ant_farm, line);
	if (result < 0)
		return (ERROR);
	else if (result == SUCCESS)
		return (SUCCESS);
	result = ft_check_end(ant_farm, line);
	if (result < 0)
		return (ERROR);
	else if (result == SUCCESS)
		return (SUCCESS);
	else if (link == NULL)
	{
		if (ft_strequ(data->argument, "link"))
			return (ft_exit_msg(ant_farm, error_in_link));
		else if (ft_save_inputline(ant_farm, line, 0) != SUCCESS)
			return (ft_exit_msg(ant_farm, error_invalid_intermediate_room));
		ant_farm->signal = succes_room_saved;
	}
	return (SUCCESS);
}
