/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_save_input.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:39:21 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/06/19 11:19:22 by dsaripap      ########   odam.nl         */
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
		// ft_printf(ANSI_COLOR_CYAN"Comment\n"ANSI_COLOR_RESET);
		return (CONTINUE);
	}
	else if (str[0] == 'L')
	{
		ant_farm->signal = error_L_beginning_of_line;
		return (ft_exit_msg(ant_farm->signal));
	}
	else if (!ft_strcmp(str, ""))
	{
		ant_farm->signal = error_empty_line;
		// ft_printf("in check VALID ant_farm->signal = %d\n", ant_farm->signal);
		return (ft_exit_msg(ant_farm->signal));
	}
	return (SUCCESS);
}

/*
** Saves the line as it is in the linked list ant_farm->input
** Saves also the room in the linked list ant_farm->rooms
** CAUTION : remember to free memory allocated from ft_strsplit
*/

t_prgm_signal		ft_save_inputline(t_ant_farm *ant_farm, char *line, \
									t_position pos)
{
	int				i;
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
		if (check_if_valid(ant_farm, line) != SUCCESS)
		{
			// ft_printf("save input line  ant_farm->signal = %d\n", ant_farm->signal);
			return (ant_farm->signal);
		}
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
	return (SUCCESS);
}

/*
** First checks if it is a non valid line (returns ERROR)
** or a comment (returns CONTINUE) so it will move on the next line
** If non of the above, it will continue on the next checks
*/

t_prgm_signal		ft_saveinput(t_ant_farm *ant_farm, char *line, size_t *j)
{
	char			*link;
	t_input			*input_line;

	link = ft_strchr(line, '-');
	input_line = ft_input_newnode(line);
	ft_input_addend(&(ant_farm->input), input_line);
	if (check_if_valid(ant_farm, line) != SUCCESS)
	{
		// ft_printf("is it valid ant_farm->signal = %d\n", ant_farm->signal);
		return (ant_farm->signal);
	}
	else if ((line[0] == '#') && (line[1] == '#') && \
	(!(!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))))
	{
		// ft_printf(ANSI_COLOR_CYAN"Invalid command\n"ANSI_COLOR_RESET);
		return (CONTINUE);
	}
	else if (lm_check_if_ants_amount(ant_farm, line, *j) != CONTINUE)
		return (ant_farm->signal);
	// else if (ft_isalnum(line[0]) && (*j == 0))
	// // else if (ft_isalnum(line))
	// {
	// 	ant_farm->ants = ft_atoi(line);
	// 	ft_printf(ANSI_COLOR_CYAN"Ants=%d\n"ANSI_COLOR_RESET, ant_farm->ants);
	// }
	else if (ft_check_if_is_room(ant_farm, line, link) != CONTINUE)
		return (ant_farm->signal);
	else if (link != NULL)
	{
		// ft_printf(ANSI_COLOR_CYAN"This is a Link\n"ANSI_COLOR_RESET);
	}
	return (SUCCESS);
}
