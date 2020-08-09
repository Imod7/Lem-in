/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_prgm_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:38:43 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/09 16:01:19 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_prgm_signal		ft_exit_msg(t_ant_farm *ant_farm, t_prgm_signal signal)
{
	ft_printf(ANSI_COLOR_RED_CINA);
	ant_farm->signal = signal;
	if (signal == ERROR)
		ft_putendl_fd("Error", 2);
	else if (signal == error_invalid_start_room)
		ft_putendl_fd("Invalid Start Room", 2);
	else if (signal == error_invalid_end_room)
		ft_putendl_fd("Invalid End Room", 2);
	else if (signal == error_end_room_exists)
		ft_putendl_fd("End Room already exists", 2);
	else if (signal == error_start_room_exists)
		ft_putendl_fd("Start Room already exists", 2);
	else if (signal == error_end_room_missing)
		ft_putendl_fd("End Room missing", 2);
	else if (signal == error_start_room_missing)
		ft_putendl_fd("Start Room missing", 2);
	else if (signal == error_empty_file)
		ft_putendl_fd("Empty File", 2);
	else if (signal == error_invalid_intermediate_room)
		ft_putendl_fd("Invalid Intermediate Room", 2);
	else if (signal == error_L_beginning_of_line)
		ft_putendl_fd("L in beginning of line", 2);
	else if (signal == error_empty_line)
		ft_putendl_fd("Empty line", 2);
	else if (signal == error_in_link)
		ft_putendl_fd("Error in Link", 2);
	else if (signal == error_invalid_ants_amount)
		ft_putendl_fd("Error in Ants Amount", 2);
	else if (signal == error_invalid_room_data)
		ft_putendl_fd("Error in Room Data (error in coordinates)", 2);
	else if (signal == error_no_links)
		ft_putendl_fd("Error No Links", 2);
	else if (signal == error_no_rooms)
		ft_putendl_fd("Error No Rooms", 2);
	else if (signal == error_start_room_con)
		ft_putendl_fd("Error Start Room has no Link to the Map", 2);
	else if (signal == error_end_room_con)
		ft_putendl_fd("Error End Room has no Link to the Map", 2);
	else if (signal == error_no_solution)
		ft_putendl_fd("Error No Solution in the Map", 2);
	else if (signal == error_coord_not_number)
		ft_putendl_fd("Error in Room Coordinates (coordinates are not numbers)", 2);
	// ft_printf("in exit msg signal = %d \n", signal);
	// ft_printf("error number \t : %d\n", errno);
	// ft_printf("error string \t : %s\n", strerror(errno));
	// exit(EXIT_FAILURE);
	ft_printf(ANSI_COLOR_RESET);
	return (signal);
}

int					ft_exitprogram(t_ant_farm *ant_farm)
{
	// ft_printf("Exit Function called \n");
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
	// if (ant_farm->signal == ERROR)
	// 	return (ERROR);
	return (SUCCESS);
}
