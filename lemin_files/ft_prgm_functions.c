/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_prgm_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/22 10:25:22 by dominique     #+#    #+#                 */
/*   Updated: 2020/04/24 10:08:02 by dominique     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int				ft_exit_msg(t_ant_farm *ant_farm, size_t flag)
{
	(void)ant_farm;
	if (flag == 0)
		ft_printf(ANSI_COLOR_RED"Error\n"ANSI_COLOR_RESET);
	return (-1);
}

int				ft_exitprogram(t_ant_farm *ant_farm)
{
	ft_free_inputlst(ant_farm->input);
	free(ant_farm);
	return (0);
}
