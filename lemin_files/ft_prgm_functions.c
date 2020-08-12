/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_prgm_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:38:43 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 14:19:50 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void			ft_exit_room_msg(t_prgm_signal signal)
{
	ft_printf(ANSI_COLOR_RED_CINA);
	if (signal == error_invalid_start_room)
		ft_putendl_fd("Invalid Start Room", 2);
	else if (signal == error_invalid_end_room)
		ft_putendl_fd("Invalid End Room", 2);
	else if (signal == error_invalid_intermediate_room)
		ft_putendl_fd("Invalid Intermediate Room", 2);
	else if (signal == error_invalid_room_data)
		ft_putendl_fd("Error in Room Data (error in coordinates)", 2);
	else if (signal == error_end_room_exists)
		ft_putendl_fd("End Room already exists", 2);
	else if (signal == error_start_room_exists)
		ft_putendl_fd("Start Room already exists", 2);
	else if (signal == error_end_room_missing)
		ft_putendl_fd("End Room missing", 2);
	else if (signal == error_start_room_missing)
		ft_putendl_fd("Start Room missing", 2);
	else if (signal == error_no_rooms)
		ft_putendl_fd("Error No Rooms", 2);
	else if (signal == error_start_room_con)
		ft_putendl_fd("Error Start Room has no Link to the Map", 2);
	else if (signal == error_end_room_con)
		ft_putendl_fd("Error End Room has no Link to the Map", 2);
	ft_printf(ANSI_COLOR_RESET);
}

t_prgm_signal		ft_exit_msg(t_ant_farm *ant_farm, t_prgm_signal signal)
{
	ft_printf(ANSI_COLOR_RED_CINA);
	ant_farm->signal = signal;
	if (signal == ERROR)
		ft_putendl_fd("Error", 2);
	else if (signal < -3 && signal > -21)
		ft_exit_room_msg(signal);
	else if (signal == error_L_beginning_of_line)
		ft_putendl_fd("L in beginning of line", 2);
	else if (signal == error_invalid_ants_amount)
		ft_putendl_fd("Error in Ants Amount", 2);
	else if (signal == error_empty_file)
		ft_putendl_fd("Empty File", 2);
	else if (signal == error_empty_line)
		ft_putendl_fd("Empty line", 2);
	else if (signal == error_in_link)
		ft_putendl_fd("Error in Link", 2);
	else if (signal == error_no_links)
		ft_putendl_fd("Error No Links", 2);
	else if (signal == error_no_solution)
		ft_putendl_fd("Error No Solution in the Map", 2);
	else if (signal == error_file_missing)
		ft_putendl_fd("Missing file", 2);
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
