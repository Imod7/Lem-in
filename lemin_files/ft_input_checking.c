/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_input_checking.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 15:02:42 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/04 07:15:52 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int				ft_is_number(char *str)
{
	int			i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((i == 0) && (str[0] == '+' || str[0] == '-'))
			;
		else if (str[i] < 48 || str[i] > 57)
			return (error_invalid_ants_amount);
		i++;
	}
	return (SUCCESS);
}

/*
** Function that checks if it the format of the line
** that corresponds to the ants amount is valid.
** If the given j is different than 0 it means that
** the number of ants is already set.
*/

int			ft_check_if_ants_amount(t_ant_farm *ant_farm, char *line, size_t j)
{
	ant_farm->signal = CONTINUE;
	// ft_printf("Ants amount : '%s'\n", line);
	if (ant_farm->ants != 0 || ft_is_number(line) != SUCCESS || j != 0)
	{
		return (ft_exit_msg(ant_farm, error_invalid_ants_amount));
	}
	else
	{
		ant_farm->ants = ft_atoi(line);
		// ft_printf(ANSI_COLOR_CYAN"Ants=%d\n"ANSI_COLOR_RESET, ant_farm->ants);
		ant_farm->signal = success_ants_saved;
	}
	return (ant_farm->signal);
}
