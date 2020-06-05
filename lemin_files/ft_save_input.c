/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_save_input.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 18:11:15 by dominique     #+#    #+#                 */
/*   Updated: 2020/06/03 18:18:09 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** This function can return 1 one of the 3 following values :
** ERROR (-1) : returns -1 to main and stops the prgm
** CONTINUE (1) : returns 1 to main and continues on the next line
** SUCCESS (0) : does not return to main and checks next ifs
*/

static int			check_if_valid(t_ant_farm *ant_farm, char *str)
{
	if ((str[0] == '#') && (str[1] != '#'))
	{
		// ft_printf(ANSI_COLOR_CYAN"Ignoring Comments\n"ANSI_COLOR_RESET);
		return (CONTINUE);
	}
	else if (str[0] == 'L')
	{
		ant_farm->signal = ERROR;
		return (ft_exit_msg(ERROR));
	}
	else if (!ft_strcmp(str, ""))
	{
		ant_farm->signal = ERROR;
		return (ft_exit_msg(ERROR));
	}
	return (SUCCESS);
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
	// int				valid;
	t_input			*input_line;
	t_room			*room;
	char			**line_items;

	// valid = check_if_valid(ant_farm, line);
	// if (check_if_valid(ant_farm, line) == ERROR)
	// 	return (ERROR);
	if ((pos == START) || (pos == END))
	{
		i = get_next_line(0, &line);
		if (i == 0)
			return (0);
		if (check_if_valid(ant_farm, line) == ERROR)
			return (ERROR);
		input_line = ft_input_newnode(line);
		ft_input_addend(&(ant_farm->input), input_line);
	}
	line_items = ft_strsplit(line, ' ');
	// room = ft_room_newnode(line_items[0]);
	room = (t_room *)ft_memalloc(sizeof(t_room));
	room->name = ft_strdup(line_items[0]);
	ft_room_addend(&(ant_farm->rooms_lst), room);
	room->position = pos;
	room->x_coord = ft_atoi(line_items[1]);
	room->y_coord = ft_atoi(line_items[2]);
	ant_farm->rooms++;
	ft_free_line(line_items, 3);
	return (0);
}

/*
** First checks if it is a non valid line (returns ERROR)
** or a comment (returns CONTINUE) so it will move on the next line
** If non of the above, it will continue on the next checks
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
	if (valid != SUCCESS)
		return (valid);
	else if ((line[0] == '#') && (line[1] == '#') && \
	(!(!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))))
	{
		ft_printf(ANSI_COLOR_CYAN"More comments so ignore\n"ANSI_COLOR_RESET);
		return (CONTINUE);
	}
	else if (ft_isalnum(line[0]) && (*j == 0))
	// else if (ft_isalnum(line))
	{
		ant_farm->ants = ft_atoi(line);
		ft_printf(ANSI_COLOR_CYAN"Number of ants\n"ANSI_COLOR_RESET);
	}
	else if (!ft_strcmp(line, "##start"))
	{
		ft_printf(ANSI_COLOR_CYAN"This is a start node\n"ANSI_COLOR_RESET);
		if (ft_save_inputline(ant_farm, line, 1) == ERROR)
			return (ERROR);
	}
	else if (!ft_strcmp(line, "##end"))
	{
		ft_printf(ANSI_COLOR_CYAN"This is an end node\n"ANSI_COLOR_RESET);
		if (ft_save_inputline(ant_farm, line, 2) == ERROR)
			return (ERROR);
	}
	else if (link == NULL)
	{
		ft_printf(ANSI_COLOR_CYAN"This is an Intermediate room\n"ANSI_COLOR_RESET);
		if (ft_save_inputline(ant_farm, line, 0) == ERROR)
			return (ERROR);
	}
	else if (link != NULL)
	{
		ft_printf(ANSI_COLOR_CYAN"This is a Link\n"ANSI_COLOR_RESET);
	}
	return (SUCCESS);
}
