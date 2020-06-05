/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_prgm_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/22 10:25:22 by dominique     #+#    #+#                 */
/*   Updated: 2020/06/02 17:16:00 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_prgm_signal		ft_exit_msg(t_prgm_signal signal)
{
	if (signal == ERROR)
		ft_printf("Error\n");
	return (ERROR);
}

int					ft_exitprogram(t_ant_farm *ant_farm)
{
	ft_free_inputlst(ant_farm->input);
	ft_free_paths(ant_farm);
	ft_free_roomslst(ant_farm->rooms_lst);
	ft_free_hashtable(ant_farm->hash_table);
	ft_free_queue(ant_farm->queue);
	free(ant_farm);
	if (ant_farm->signal == ERROR)
		return (ERROR);
	return (SUCCESS);
}
