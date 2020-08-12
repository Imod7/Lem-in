/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_input_validation_order.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/11 23:53:05 by svan-der      #+#    #+#                 */
/*   Updated: 2020/08/12 15:17:53 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int		ft_check_links_valid(t_ant_farm *ant_farm, t_data *data)
{
	if (ant_farm->signal != 5 && ant_farm->signal != 2)
	{
		data->valid = ERROR;
		return (ft_exit_msg(ant_farm, error_in_link));
	}
	return (SUCCESS);
}

static int		ft_check_rooms_valid(t_ant_farm *ant_farm, t_data *data)
{
	if (data->valid == 1 && ant_farm->signal == 5)
		data->valid = 0;
	else if (data->valid == 0 && ant_farm->signal != 5 \
	&& ant_farm->signal != 2)
	{
		data->valid = ERROR;
		return (ft_exit_msg(ant_farm, error_invalid_room_data));
	}
	else if (data->valid == 0 && ant_farm->signal == 5)
	{
		data->valid = 1;
		data->argument = "link";
	}
	return (SUCCESS);
}

static int		ft_check_ants_valid(t_ant_farm *ant_farm, t_data *data)
{
	if (ant_farm->signal == 1)
		data->argument = "room";
	else if (ant_farm->signal != 2 && ant_farm->signal != 0)
	{
		data->valid = ERROR;
		return (ft_exit_msg(ant_farm, error_invalid_ants_amount));
	}
	return (SUCCESS);
}

/*
** Checks if the argument order of the data is correct
** so that the order of 1)ants_amount, 2)rooms and 3)links is valid
** and also that data doesn't pass that doesn't belong in that section
*/

int				ft_precheck_if_valid(t_ant_farm *ant_farm, t_data *data, int i)
{
	if (i == 1)
	{
		if ((ant_farm->signal != SUCCESS && \
			ant_farm->signal != CONTINUE && \
			ant_farm->signal != succes_room_saved \
			&& ant_farm->signal != succes_link_saved)\
			|| data->valid == ERROR)
			return (ERROR);
	}
	else if (ft_strequ(data->argument, "ants_amount"))
		return (ft_check_ants_valid(ant_farm, data));
	else if (ft_strequ(data->argument, "room"))
		return (ft_check_rooms_valid(ant_farm, data));
	else if (ft_strequ(data->argument, "link") && data->valid == 1)
		return (ft_check_links_valid(ant_farm, data));
	return (SUCCESS);
}
