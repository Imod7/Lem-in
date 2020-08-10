/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_input_parsing.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 15:04:20 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/10 03:58:55 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** This function can return one of the 3 following values :
** ERROR (-1) : returns -1 to main and stops the prgm
** CONTINUE (1) : returns 1 to main and continues on the next line
** SUCCESS (0) : does not return to main and checks next ifs
*/

static int			check_if_valid(t_ant_farm *ant_farm, char *str)
{
	if ((str[0] == '#') && (str[1] != '#'))
	{
		// ft_printf("Comment line %s\n", str);
		ant_farm->signal = CONTINUE;
		return (ant_farm->signal);
	}
	else if ((str[0] == '#') && (str[1] == '#') && \
	(!(!ft_strcmp(str, "##start") || !ft_strcmp(str, "##end"))))
	{
		// ft_printf(ANSI_COLOR_CYAN"Invalid command\n"ANSI_COLOR_RESET);
		return (CONTINUE);
	}
	else if (str[0] == 'L')
	{
		return (ft_exit_msg(ant_farm, error_L_beginning_of_line));
	}
	else if (!ft_strcmp(str, ""))
	{
		// ant_farm->signal = error_empty_line;
		// ft_printf("in check VALID ant_farm->signal = %d\n", ant_farm->signal);
		return (ft_exit_msg(ant_farm, error_empty_line));
	}
	else if (str[0] == ' ')
		return (ft_exit_msg(ant_farm, ERROR));
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
	int				space;
	t_input			*input_line;
	t_room			*room;
	char			**line_items;
	size_t			len;

	// valid = check_if_valid(ant_farm, line);
	// if (check_if_valid(ant_farm, line) == ERROR)
	// 	return (ERROR);
	if ((pos == START) || (pos == END))
	{
		i = get_next_line(0, &line);
		if (i == 0)
			return (0);
		while (check_if_valid(ant_farm, line) == CONTINUE)
		{
			ft_printf("freeing line : %s \n", line);
			free(line);
			i = get_next_line(0, &line);
			if (i == 0)
				return (0);
		}
		if (check_if_valid(ant_farm, line) != SUCCESS)
		{
			ft_printf("it frees line - signal %d\n", ant_farm->signal);
			free(line);
			return (ant_farm->signal);
		}
		// ft_printf("save input line  ant_farm->signal = %d, line %s\n", ant_farm->signal, line);
		input_line = ft_input_newnode(line);
		ft_input_addend(&(ant_farm->input), input_line);
	}
	space = ft_strchri(line, ' ');
	i = ft_strchri(line, '-');
	line_items = ft_strsplit(line, ' ');
	// if (line_items == NULL)
	// 	ft_printf("line_items is NULL\n");
	len = array_size(line_items);
	// ft_printf("'%s'  len %d\n", line_items[0], len);
	// ft_printf("len = %d : '%s' : x '%s'  y '%s'\n", len, line_items[0], line_items[1], line_items[2]);
	if (len < 3 || i > 1 || len > 3 || space > 2)
	{
		ft_free_string(line_items, len);
		return (ft_exit_msg(ant_farm, error_invalid_room_data));
	}
	// room = ft_room_newnode(line_items[0]);
	if (ft_is_number(line_items[1]) != SUCCESS || \
	ft_is_number(line_items[2]) != SUCCESS)
		return (ft_exit_msg(ant_farm, error_coord_not_number));
	// ft_printf("save input line  items = '%s' : x '%s'\n", line_items[0], line_items[1]);
	room = (t_room *)ft_memalloc(sizeof(t_room));
	room->name = ft_strdup(line_items[0]);
	// ft_printf("save input room = '%s'\n", line_items[0]);
	ft_room_addend(&(ant_farm->rooms_lst), room);
	room->position = pos;
	room->x_coord = check_argv(&ant_farm->signal, line_items[1]);
	room->y_coord = check_argv(&ant_farm->signal, line_items[2]);
	if (ant_farm->signal < 0)
		return (ft_exit_msg(ant_farm, error_invalid_room_data));
	ant_farm->rooms++;
	ft_free_string(line_items, 3);
	return (SUCCESS);
}

/*
** Function ft_saveinput first checks if it is a non valid line (returns ERROR)
** or a comment (returns CONTINUE) so it will move on the next line
** If non of the above, it will continue on the next checks.
** We keep j as a flag so if ants are saved (j != 0) then it will not
** check again for the ants_amount (function call ft_check_if_ants_amount)
*/

t_prgm_signal		ft_saveinput(t_ant_farm *ant_farm, char *line, size_t *j)
{
	char			*link;
	t_input			*input_line;
	int				ret;

	ret = count_words(line, ' ');
	link = (ret == 1) ? ft_strchr(line, '-') : NULL;
	input_line = ft_input_newnode(line);
	ft_input_addend(&(ant_farm->input), input_line);
	if (check_if_valid(ant_farm, line) != SUCCESS)
	{
		// ft_printf("is it valid ant_farm->signal = %d\n", ant_farm->signal);
		return (ant_farm->signal);
	}
	// else if ((line[0] == '#') && (line[1] == '#') && \
	// (!(!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))))
	// {
	// 	// ft_printf(ANSI_COLOR_CYAN"Invalid command\n"ANSI_COLOR_RESET);
	// 	return (CONTINUE);
	// }
	// ft_printf(" j = %d \n", )
	else if (*j == 0 && ft_check_if_ants_amount(ant_farm, line, *j) != CONTINUE)
		return (ant_farm->signal);
	else if (*j != 0 && ft_is_number(line) == SUCCESS)
	{
		// ft_printf("invalid ants amount\n");
		return (ft_exit_msg(ant_farm, error_invalid_ants_amount));
	}
	else if (link)
	{
		// ft_printf("line:%s\n", line);
		// ft_printf(ANSI_COLOR_CYAN">>This is a Link %s \n"ANSI_COLOR_RESET, line);
		ret = ft_strchri(line, '-');
		if (ret != 1)
		{
			ant_farm->signal = error_in_link;
			// ft_printf("error found:%s\n", line);
			return (ft_exit_msg(ant_farm, error_in_link));
		}
	}
	else if (ft_check_if_is_room(ant_farm, line, link) != CONTINUE)
	{
		// ft_printf("This is a room - line:%s\n", line);
		return (ant_farm->signal);
	}
	else if (link != NULL)
	{
		// ft_printf("line:%s\n", line);
		// ft_printf(ANSI_COLOR_CYAN"This is a Link\n"ANSI_COLOR_RESET);
	}
	return (SUCCESS);
}
