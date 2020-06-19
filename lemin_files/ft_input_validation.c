/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_input_validation.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 18:00:12 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/06/19 10:47:41 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int			lm_check_if_ants_amount(t_ant_farm *ant_farm, char *line, size_t j)
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
