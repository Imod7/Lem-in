/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_rooms_functions.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 18:00:20 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 16:50:09 by svan-der      ########   odam.nl         */
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

	temp = ant_farm->rooms_lst;
	while (temp != NULL)
	{
		if (temp->position == END)
		{
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
	if (!ft_strcmp(line, "##start"))
	{
		if (ft_get_start_room(ant_farm->rooms_lst) != NULL)
			return (ft_exit_msg(ant_farm, error_start_room_exists));
		if (ft_save_inputline(ant_farm, line, 1) != SUCCESS)
			return (ft_exit_msg(ant_farm, error_invalid_start_room));
		ant_farm->signal = succes_room_saved;
	}
	else if (!ft_strcmp(line, "##end"))
	{
		if (ft_get_end_room(ant_farm) != NULL)
			return (ft_exit_msg(ant_farm, error_end_room_exists));
		if (ft_save_inputline(ant_farm, line, 2) != SUCCESS)
			return (ft_exit_msg(ant_farm, error_invalid_end_room));
		ant_farm->signal = succes_room_saved;
	}
	else if (link == NULL)
	{
		if (ft_strequ(data->argument, "link"))
			return (ft_exit_msg(ant_farm, error_in_link));
		else if (ft_save_inputline(ant_farm, line, 0) != SUCCESS)
			return (ft_exit_msg(ant_farm, error_invalid_intermediate_room));
		ant_farm->signal = succes_room_saved;
	}
	return (SUCCESS);
}
