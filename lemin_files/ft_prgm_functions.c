/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_prgm_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:38:43 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/06/19 10:38:45 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_prgm_signal		ft_exit_msg(t_prgm_signal signal)
{
	ft_printf(ANSI_COLOR_RED_CINA);
	if (signal == ERROR)
		write(2, "Error\n", 6);
		// perror("Error ");
	else if (signal == error_invalid_start_room)
		write(2, "Invalid Start Room\n", 19);
	else if (signal == error_invalid_end_room)
		write(2, "Invalid End Room\n", 17);
	else if (signal == error_invalid_intermediate_room)
		write(2, "Invalid Intermediate Room\n", 26);
	else if (signal == error_L_beginning_of_line)
		write(2, "L in beginning of line\n", 23);
	else if (signal == error_empty_line)
		write(2, "Empty line\n", 11);
	else if (signal == error_in_link)
		write(2, "Error in Link\n", 14);
	// ft_printf("in exit msg signal = %d \n", signal);
	// ft_printf("error number \t : %d\n", errno);
	// ft_printf("error string \t : %s\n", strerror(errno));
	// exit(EXIT_FAILURE);
	ft_printf(ANSI_COLOR_RESET);
	return (signal);
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
