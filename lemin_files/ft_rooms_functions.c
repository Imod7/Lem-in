/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_rooms_functions.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 18:00:20 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 09:37:03 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** Functions ft_room_addend which is used to
** save a room of the input file at the end of the
** rooms linked list
*/

void				ft_room_addend(t_room **lst, t_room *new)
{
	t_room			*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

/*
** Function that returns the source.
** It iterates through the rooms_list and if the position
** of the room is START, then it means this room is the source.
*/

t_room				*ft_get_start_room(t_room *temp)
{
	while (temp != NULL)
	{
		if (temp->position == START)
			return (temp);
		temp = temp->next;
	}
	temp = NULL;
	return (temp);
}

/*
** Function that returns the sink.
** It iterates through the rooms_list and if the position
** of the room is END, then it means this room is the sink
*/

t_room				*ft_get_end_room(t_ant_farm *ant_farm)
{
	t_room			*temp;

	// ft_print_rooms_list(ant_farm->rooms_lst);
	temp = ant_farm->rooms_lst;
	while (temp != NULL)
	{
		if (temp->position == END)
		{
			// ft_printf("room %s %d \n", temp->name, temp->position);
			return (temp);
		}
		temp = temp->next;
	}
	temp = NULL;
	return (temp);
}

/*
** Function that checks if the line that we check from the input file
** (with the map data) is a start / end  / intermediate room.
*/

int					ft_check_if_is_room(t_ant_farm *ant_farm, char *line, \
										char *link, t_data *data)
{
	int ret;
	int result;

	// ft_printf(">>>check if is room \n");
	ret = -1;
	(void)data;
	if (!ft_strcmp(line, "##start"))
	{
		// ft_printf("FUNCTION ft_check_if_is_room %s\n", line);
		if (ft_get_start_room(ant_farm->rooms_lst) != NULL)
		{
			// ft_printf("start exists %s\n", line);
			return (ft_exit_msg(ant_farm, error_start_room_exists));
		}
		result = ft_save_inputline(ant_farm, line, START);
		// ft_printf(" ------>>> signal %d\n", result);
		if (result >= -3 && result <= -1)
			return (ant_farm->signal);
		else if (result != SUCCESS)
		{
			// ft_printf(" .. error found:%s error:%i\n", line, ant_farm->signal);
			// ant_farm->signal = error_invalid_start_room;
			return (ft_exit_msg(ant_farm, error_invalid_start_room));
		}
		else
			ant_farm->signal = succes_room_saved;
	}
	else if (!ft_strcmp(line, "##end"))
	{
		// ft_printf(ANSI_COLOR_CYAN"End node\n"ANSI_COLOR_RESET);
		if (ft_get_end_room(ant_farm) != NULL)
		{
			t_room *str;
			str = ft_get_end_room(ant_farm);
			// ft_printf("end exists %p\n", str);
			return (ft_exit_msg(ant_farm, error_end_room_exists));
		}
		result = ft_save_inputline(ant_farm, line, END);
		// ft_printf(" ------>>> signal %d\n", result);
		if (result >= -3 && result <= -1)
			return (ant_farm->signal);
		else if (result != SUCCESS)
		{
			// ft_printf(" ... /// error found:%s error:%i\n", line, ant_farm->signal);
			// ant_farm->signal = error_invalid_end_room;
			return (ft_exit_msg(ant_farm, error_invalid_end_room));
		}
		else
			ant_farm->signal = succes_room_saved;
	}
	else if (link == NULL)
	{
		// ft_printf(ANSI_COLOR_CYAN"Intermediate room %s \n"ANSI_COLOR_RESET, line);
		// if (ft_strchri(line, '-') && ft_strequ(line, "Jaj7 8 --8"))
		// {
		// 	ret = ft_save_inputline(ant_farm, line, 0);
		// 	ft_printf("ret is:%i\n", ret);
		// 	ft_printf("ptr:%p\n", link);
		// 	ft_printf("%i\n", ant_farm->signal);
		// 	exit(0);
		// }
		if (ft_strequ(data->argument, "link"))
		{
			return (ft_exit_msg(ant_farm, error_in_link));
		}
		else if (ft_save_inputline(ant_farm, line, 0) != SUCCESS)
		{
			// ft_printf(" >>> line:%s error found >s> :%s error:%i data arg:%s\n", line, ant_farm->signal, data->argument);
			if (ft_strequ(line, "Gyy5- Q_d0"))
			{
				ft_printf("ret is:%i\n", ret);
				ft_printf("ptr:%p\n", link);
				ft_printf("%i\n", ant_farm->signal);
				// exit(1);
			}
			return (ft_exit_msg(ant_farm, error_invalid_intermediate_room));
		}
		else
			ant_farm->signal = succes_room_saved;
	}
	return (SUCCESS);
}
