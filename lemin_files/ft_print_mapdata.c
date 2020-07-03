/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_mapdata.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/28 10:48:20 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/02 08:23:28 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			ft_print_mapdata(t_ant_farm *ant_farm)
{
	t_input		*lines;

	lines = ant_farm->input;
	while (lines != NULL)
	{
		// if ((lines->line[0] == '#') && (lines->line[1] != '#'))
		// 	;
		// else
		ft_printf("%s\n", lines->line);
		lines = lines->next;
	}
	ft_printf("\n");
}
