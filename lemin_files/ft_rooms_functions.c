/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_rooms_functions.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 18:00:20 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/31 04:50:44 by dsaripap      ########   odam.nl         */
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
			break ;
		temp = temp->next;
	}
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
			break ;
		temp = temp->next;
	}
	return (temp);
}

int					ft_check_if_is_room(t_ant_farm *ant_farm, char *line, \
										char *link)
{
	if (!ft_strcmp(line, "##start"))
	{
		// ft_printf(ANSI_COLOR_CYAN"Start node\n"ANSI_COLOR_RESET);
		if (ft_save_inputline(ant_farm, line, 1) != SUCCESS)
			ant_farm->signal = error_invalid_start_room;
		else
			ant_farm->signal = SUCCESS;
	}
	else if (!ft_strcmp(line, "##end"))
	{
		// ft_printf(ANSI_COLOR_CYAN"End node\n"ANSI_COLOR_RESET);
		if (ft_save_inputline(ant_farm, line, 2) != SUCCESS)
			ant_farm->signal = error_invalid_end_room;
		else
			ant_farm->signal = SUCCESS;
	}
	else if (link == NULL)
	{
		// ft_printf(ANSI_COLOR_CYAN"Intermediate room\n"ANSI_COLOR_RESET);
		if (ft_save_inputline(ant_farm, line, 0) != SUCCESS)
			ant_farm->signal = error_invalid_intermediate_room;
		else
			ant_farm->signal = SUCCESS;
	}
	else
		ant_farm->signal = CONTINUE;
	return (ant_farm->signal);
}
