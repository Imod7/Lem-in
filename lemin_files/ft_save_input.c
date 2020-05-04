/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_save_input.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 18:11:15 by dominique     #+#    #+#                 */
/*   Updated: 2020/05/04 16:17:37 by dominique     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int			check_if_valid(t_ant_farm *ant_farm, char *str)
{
	if ((str[0] == '#') && (str[1] != '#'))
	{
		ft_printf(ANSI_COLOR_CYAN"Ignoring Comments\n\n"ANSI_COLOR_RESET);
		return (1);
	}
	else if (str[0] == 'L')
		return (ft_exit_msg(ant_farm, 0));
	else if (!ft_strcmp(str, ""))
		return (ft_exit_msg(ant_farm, 0));
	else
		return (0);
}

/*
** Saves the line as it is in the linked list ant_farm->input
** Saves also the room in the linked list ant_farm->rooms
** CAUTION : remember to free memory allocated from ft_strsplit
*/

int					ft_save_inputline(t_ant_farm *ant_farm, char *line, \
									t_position pos)
{
	int				i;
	int				valid;
	t_input			*input_line;
	t_room			*room;
	char			**line_items;

	valid = check_if_valid(ant_farm, line);
	if (valid != 0)
		return (valid);
	if ((pos == START) || (pos == END))
	{
		i = get_next_line(0, &line);
		if (i == 0)
			return (0);
		input_line = ft_input_newnode(line);
		ft_input_addend(&(ant_farm->input), input_line);
	}
	line_items = ft_strsplit(line, ' ');
	room = ft_room_newnode(line_items[0]);
	ft_room_addend(&(ant_farm->rooms_lst), room);
	room->position = pos;
	room->x_coord = ft_atoi(line_items[1]);
	room->y_coord = ft_atoi(line_items[2]);
	ant_farm->rooms++;
	ft_free_line(line_items, 3);
	return (0);
}

/*
** 1st if checks if it is a comment
** 2nd if checks that line is invalid
** 3rd if checks if it is a command that we ignore
** ...
*/

int					ft_saveinput(t_ant_farm *ant_farm, char *line, size_t *j)
{
	char			*link;
	t_input			*input_line;
	int				valid;

	link = ft_strchr(line, '-');
	input_line = ft_input_newnode(line);
	ft_input_addend(&(ant_farm->input), input_line);
	valid = check_if_valid(ant_farm, line);
	if (valid != 0)
		return (valid);
	else if ((line[0] == '#') && (line[1] == '#') && \
	(!(!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))))
	{
		ft_printf(ANSI_COLOR_CYAN"Command != start/end so ignore\n"ANSI_COLOR_RESET);
	}
	else if (ft_isalnum(line[0]) && (*j == 0))
	{
		ant_farm->ants = ft_atoi(line);
		ft_printf(ANSI_COLOR_CYAN"These are the number of ants\n"ANSI_COLOR_RESET);
	}
	else if (!ft_strcmp(line, "##start"))
	{
		ft_printf(ANSI_COLOR_CYAN"This is a start node\n"ANSI_COLOR_RESET);
		if (ft_save_inputline(ant_farm, line, 1) == -1)
			return (-1);
	}
	else if (!ft_strcmp(line, "##end"))
	{
		ft_printf(ANSI_COLOR_CYAN"This is an end node\n"ANSI_COLOR_RESET);
		if (ft_save_inputline(ant_farm, line, 2) == -1)
			return (-1);
	}
	else if (link == NULL)
	{
		ft_printf(ANSI_COLOR_CYAN"This is an Intermediate room\n"ANSI_COLOR_RESET);
		if (ft_save_inputline(ant_farm, line, 0) == -1)
			return (-1);
	}
	else if (link != NULL)
	{
		ft_printf(ANSI_COLOR_CYAN"This is a Link\n"ANSI_COLOR_RESET);
	}
	return (0);
}
