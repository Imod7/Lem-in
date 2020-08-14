/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_prgm_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:38:43 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/14 06:19:26 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_prgm_signal		ft_exit_msg(t_ant_farm *ant_farm, t_prgm_signal signal)
{
	ft_printf(ANSI_COLOR_RED_CINA);
	ant_farm->signal = signal;
	ft_putendl_fd("ERROR", 2);
	ft_printf(ANSI_COLOR_RESET);
	return (signal);
}

int					ft_exitprogram(t_ant_farm *ant_farm)
{
	ft_free_data(ant_farm->data);
	ft_free_inputlst(ant_farm->input);
	ft_free_paths(ant_farm);
	ft_free_roomslst(ant_farm->rooms_lst);
	ft_free_hashtable(ant_farm->hash_table);
	ft_free_path_lines(ant_farm->lines_lst);
	free(ant_farm);
	return (SUCCESS);
}
