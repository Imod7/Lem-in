/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_save_input.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 18:11:15 by dominique     #+#    #+#                 */
/*   Updated: 2020/04/29 01:06:56 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int					check_if_valid(t_ant_farm *ant_farm, char *str)
{
	if ((str[0] == '#') && (str[1] != '#'))
	{
		ft_printf(ANSI_COLOR_CYAN"Ignoring Comments\n\n"ANSI_COLOR_RESET);
		return (1);
	}
	else if ((str[0] == '#') && (str[1] == '#') && \
	(!(!ft_strcmp(str, "##start") || !ft_strcmp(str, "##end"))))
	{
		ft_printf(ANSI_COLOR_CYAN"Command != start/end so we ignore\n\n"ANSI_COLOR_RESET);
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
** 1st if checks if it is a comment
** 2nd if checks that line is invalid
** 3rd if checks if it is a command that we ignore
** ...
*/

int					add_commands(t_ant_farm *ant_farm, char *line)
{
	int				i;
	int				valid;
	t_input			*input_line;
	char			*command;

	command = line;
	i = get_next_line(0, &line);
	if (i != 0)
	{
		valid = check_if_valid(ant_farm, line);
		if (valid != 0)
			return (valid);
		if ((!ft_strcmp(command, "##start")))
			ft_printf(ANSI_COLOR_CYAN"start node line = %s\n\n"ANSI_COLOR_RESET, line);
		else if (!ft_strcmp(command, "##end"))
			ft_printf(ANSI_COLOR_CYAN"end node line = %s\n\n"ANSI_COLOR_RESET, line);
		input_line = ft_input_newnode(line);
		ft_input_addend(&(ant_farm->input), input_line);
		ant_farm->rooms++;
	}
	return (0);
}

int					ft_saveinput(t_ant_farm *ant_farm, char *line, size_t *j)
{
	int				i;
	char			*link;
	t_input			*input_line;

	link = ft_strchr(line, '-');
	input_line = ft_input_newnode(line);
	ft_input_addend(&(ant_farm->input), input_line);
	if (ft_isalnum(line[0]) && (*j == 0))
	{
		ant_farm->ants = ft_atoi(line);
		ft_printf(ANSI_COLOR_CYAN"Saved number of ants = %d\n\n"ANSI_COLOR_RESET, ant_farm->ants);
	}
	else if (line[0] == '#')
		return (add_commands(ant_farm, line));
	else if (link == NULL)
	{
		ft_printf(ANSI_COLOR_CYAN"Intermediate room\n\n"ANSI_COLOR_RESET);
		ant_farm->rooms++;
	}
	else if (link != NULL)
		ft_printf(ANSI_COLOR_CYAN"Link = %s\n\n"ANSI_COLOR_RESET, line);
	return (0);
}
