/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_input_parsing.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 15:04:20 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 18:40:53 by dsaripap      ########   odam.nl         */
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
		ant_farm->signal = CONTINUE;
		return (ant_farm->signal);
	}
	else if ((str[0] == '#') && (str[1] == '#') && \
	(!(!ft_strcmp(str, "##start") || !ft_strcmp(str, "##end"))))
		return (CONTINUE);
	else if (str[0] == 'L')
	{
		return (ft_exit_msg(ant_farm, error_L_beginning_of_line));
	}
	else if (!ft_strcmp(str, ""))
		return (ft_exit_msg(ant_farm, error_empty_line));
	else if (str[0] == ' ')
		return (ft_exit_msg(ant_farm, ERROR));
	return (SUCCESS);
}

t_prgm_signal		save_start_end(t_ant_farm *ant_farm, char **line, \
									t_position pos, int i)
{
	t_input			*input_line;

	if ((pos == START) || (pos == END))
	{
		i = get_next_line(0, line);
		if (i == 0)
			return (0);
		while (check_if_valid(ant_farm, *line) == CONTINUE)
		{
			free(*line);
			i = get_next_line(0, line);
			if (i == 0)
				return (0);
		}
		if (ant_farm->signal < 0)
			return (ant_farm->signal);
		if (check_if_valid(ant_farm, *line) != SUCCESS)
		{
			free(*line);
			return (ant_farm->signal);
		}
		input_line = ft_input_newnode(*line);
		ft_input_addend(&(ant_farm->input), input_line);
	}
	return (SUCCESS);
}

void				ft_saveinput_checks(t_ant_farm *ant_farm, char **link, \
									char *line, t_data *data)
{
	int				ret;
	t_input			*input_line;

	ret = count_words(line, ' ');
	data->min = ft_strchri(line, '-');
	*link = (ret == 1 && data->min == 1) ? ft_strchr(line, '-') : NULL;
	input_line = ft_input_newnode(line);
	ft_input_addend(&(ant_farm->input), input_line);
}

/*
** Function ft_saveinput first checks if it is a non valid line (returns ERROR)
** or a comment (returns CONTINUE) so it will move on the next line
** If non of the above, it will continue on the next checks.
** We keep j as a flag so if ants are saved (j != 0) then it will not
** check again for the ants_amount (function call ft_check_if_ants_amount)
*/

t_prgm_signal		ft_saveinput(t_ant_farm *ant_farm, char *line, size_t *j, \
								t_data *data)
{
	char			*link;

	ft_saveinput_checks(ant_farm, &link, line, data);
	if (check_if_valid(ant_farm, line) != SUCCESS)
		return (ant_farm->signal);
	else if (*j == 0 && ft_check_if_ants_amount(ant_farm, line, *j) != CONTINUE)
		return (ant_farm->signal);
	else if (*j != 0 && ft_is_number(line) == SUCCESS && \
	ft_strequ(data->argument, "ants_amount"))
		return (ft_exit_msg(ant_farm, error_invalid_ants_amount));
	else if (link)
	{
		if (data->min != 1 || ft_strlen(line) < 3)
		{
			ant_farm->signal = error_in_link;
			return (ft_exit_msg(ant_farm, error_in_link));
		}
		ant_farm->signal = succes_link_saved;
	}
	else if (ft_check_if_is_room(ant_farm, line, link, data) != CONTINUE)
		return (ant_farm->signal);
	else if (link != NULL)
		ant_farm->signal = succes_link_saved;
	return (SUCCESS);
}
