/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_ants_move.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/30 12:25:49 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 15:19:07 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void			ft_check_room_position(t_path_list *path_lst, \
											t_paths *paths)
{
	t_ants			*ants_lst_end;

	if ((path_lst->room->position != END) && \
	(path_lst->room->ants_lst->ant_id != 0))
		ft_printf("L%d-%s ", path_lst->room->ants_lst->ant_id,\
	path_lst->room->name);
	else if (path_lst->room->position == END)
	{
		ants_lst_end = path_lst->room->ants_lst;
		while ((ants_lst_end->next != NULL) && \
		(ants_lst_end->path->path_id != paths->path_id))
		{
			ants_lst_end = ants_lst_end->next;
		}
		if ((ants_lst_end->path->path_id == paths->path_id) && \
		(ants_lst_end->ant_id != 0))
		{
			ft_printf("L%d-%s ", ants_lst_end->ant_id, path_lst->room->name);
		}
	}
}

void				ft_print_move(t_ant_farm *ant_farm)
{
	t_paths			*paths;
	t_path_list		*path_lst;

	paths = ant_farm->paths;
	while (paths != NULL)
	{
		if (paths->run == ant_farm->best_run)
		{
			path_lst = paths->path_lst;
			while (path_lst->next != NULL)
				path_lst = path_lst->next;
			while (path_lst != NULL)
			{
				if (path_lst->room->ants_lst != NULL)
					ft_check_room_position(path_lst, paths);
				path_lst = path_lst->prev;
			}
		}
		paths = paths->next;
	}
	ft_printf("\n");
}
