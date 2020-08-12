/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_input_parsing_func.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/12 18:33:48 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 18:38:10 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static t_prgm_signal	ft_save_input_n_check(t_ant_farm *ant_farm, \
									char **line, char ***line_items, \
									t_position pos)
{
	int					i;
	size_t				len;
	int					space;

	i = 0;
	if (save_start_end(ant_farm, line, pos, i) != SUCCESS)
		return (ERROR);
	space = ft_strchri(*line, ' ');
	*line_items = ft_strsplit(*line, ' ');
	i = ft_strchri((*line_items)[0], '-');
	len = array_size(*line_items);
	if (len < 3 || i > 0 || len > 3 || space > 2)
	{
		ft_free_string(*line_items, len);
		return (ERROR);
	}
	if (ft_is_number((*line_items)[1]) != SUCCESS || \
	ft_is_number((*line_items)[2]) != SUCCESS)
	{
		ft_free_string(*line_items, len);
		return (ft_exit_msg(ant_farm, error_coord_not_number));
	}
	return (len);
}

/*
** Saves the line as it is in the linked list ant_farm->input
** Saves also the room in the linked list ant_farm->rooms
** CAUTION : remember to free memory allocated from ft_strsplit
*/

t_prgm_signal			ft_save_inputline(t_ant_farm *ant_farm, char *line, \
									t_position pos)
{
	t_room				*room;
	char				**line_items;
	int					len;

	line_items = NULL;
	len = ft_save_input_n_check(ant_farm, &line, &line_items, pos);
	if (len < 0)
		return (ERROR);
	room = (t_room *)ft_memalloc(sizeof(t_room));
	if (room == NULL)
		return (ERROR);
	room->name = ft_strdup(line_items[0]);
	ft_room_addend(&(ant_farm->rooms_lst), room);
	room->position = pos;
	room->x_coord = check_argv(&ant_farm->signal, line_items[1]);
	room->y_coord = check_argv(&ant_farm->signal, line_items[2]);
	if (ant_farm->signal < 0)
	{
		ft_free_string(line_items, len);
		return (ft_exit_msg(ant_farm, error_invalid_room_data));
	}
	ant_farm->rooms++;
	ft_free_string(line_items, len);
	return (SUCCESS);
}
