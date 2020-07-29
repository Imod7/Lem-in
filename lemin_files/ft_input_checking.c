/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_input_checking.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 15:02:42 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/29 15:02:44 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int			ft_check_if_ants_amount(t_ant_farm *ant_farm, char *line, size_t j)
{
	ant_farm->signal = CONTINUE;
	if (ft_isalnum(line[0]) && (j == 0))
	{
		ant_farm->ants = ft_atoi(line);
		// ft_printf(ANSI_COLOR_CYAN"Ants=%d\n"ANSI_COLOR_RESET, ant_farm->ants);
		ant_farm->signal = success_ants_saved;
	}
	return (ant_farm->signal);
}
