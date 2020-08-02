/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_prgm_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:38:43 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/01 15:46:05 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_prgm_signal		ft_exit_msg(t_ant_farm *ant_farm, t_prgm_signal signal)
{
	ft_printf(ANSI_COLOR_RED_CINA);
	if (signal == ERROR)
		ft_putendl_fd("Error", 2);
		// write(2, "Error\n", 6);
		// perror("Error ");
	else if (signal == error_invalid_start_room)
		// write(2, "Invalid Start Room\n", 19);
		ft_putendl_fd("Invalid Start Room", 2);
	else if (signal == error_invalid_end_room)
		// write(2, "Invalid End Room\n", 17);
		ft_putendl_fd("Invalid End Room", 2);
	else if (signal == error_invalid_intermediate_room)
	{
		ft_putendl_fd("Invalid Intermediate Room", 2);
		// write(2, "Invalid Intermediate Room\n", 26);
	}
	else if (signal == error_L_beginning_of_line)
	{
		ant_farm->signal = error_L_beginning_of_line;
		ft_putendl_fd("L in beginning of line", 2);
		// write(2, "L in beginning of line\n", 23);
	}
	else if (signal == error_empty_line)
	{
		ant_farm->signal = error_empty_line;
		ft_putendl_fd("Empty line", 2);
		// ft_printf("in check VALID ant_farm->signal = %d\n", ant_farm->signal);
	}
	else if (signal == error_in_link)
	{
		ant_farm->signal = error_in_link;
		ft_putendl_fd("Error in Link", 2);
	}
	else if (signal == error_invalid_ants_amount)
	{
		ant_farm->signal = error_invalid_ants_amount;
		ft_putendl_fd("Error in Ants Amount", 2);
	}
	else if (signal == error_invalid_room_data)
	{
		ant_farm->signal = error_invalid_room_data;
		ft_putendl_fd("Error in Room Data (maybe missing coordinates)", 2);
	}
	// ft_printf("in exit msg signal = %d \n", signal);
	// ft_printf("error number \t : %d\n", errno);
	// ft_printf("error string \t : %s\n", strerror(errno));
	// exit(EXIT_FAILURE);
	ft_printf(ANSI_COLOR_RESET);
	return (signal);
}

int					ft_exitprogram(t_ant_farm *ant_farm)
{
	ft_printf("Exit Function called");
	// ft_printf("exit prgm \n");
	// print_input_list(ant_farm->input);
	ft_free_inputlst(ant_farm->input);
	// ant_farm->input = NULL;
	// ft_printf("ant_farm->input %p \n", ant_farm->input);
	// print_input_list(ant_farm->input);
	// ft_printf("before free paths\n");
	ft_free_paths(ant_farm);
	// ft_printf("after free paths\n");
	// ft_printf("printi paths %p \n", ant_farm->paths);
	// ft_print_paths(ant_farm);
	ft_free_roomslst(ant_farm->rooms_lst);
	ft_free_hashtable(ant_farm->hash_table);
	// ft_free_queue(ant_farm->queue);
	ft_free_path_lines(ant_farm->lines_lst);
	// ft_printf("after free queue\n");
	free(ant_farm);
	if (ant_farm->signal == ERROR)
		return (ERROR);
	return (SUCCESS);
}
