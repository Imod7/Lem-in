/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_ants.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:38:51 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/02 08:21:30 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void				ft_print_ants_in_paths(t_ant_farm *ant_farm)
{
	t_paths			*paths;
	t_ants			*ants_lst;

	ft_printf(ANSI_COLOR_CYAN"Ants assigned to Paths \n");
	paths = ant_farm->paths;
	while (paths != NULL)
	{
		ft_printf("Path ID %d : ", paths->path_id);
		ants_lst = paths->ants_lst;
		while (ants_lst != NULL)
		{
			// ft_printf("path list not NULL  \n");
			ft_printf("%d", ants_lst->ant_id);
			ants_lst = ants_lst->next;
			if (ants_lst != NULL)
				ft_printf(" -> ");
		}
		ft_printf(" [ total_size : %d ] ", paths->path_size + \
		paths->ants_amount);
		paths = paths->next;
		ft_printf("\n");
		// ft_printf("next path %p \n", paths);
	}
	ft_printf(ANSI_COLOR_RESET);
}

void				ft_print_ants_in_rooms(t_ant_farm *ant_farm)
{
	t_paths			*paths;
	t_path_list		*path_lst;
	t_ants			*ants_lst;
	// t_ants			*delete;

	ft_printf(ANSI_COLOR_YELLOW_PAST"Ants in Rooms \n");
	paths = ant_farm->paths;
	while (paths != NULL)
	{
		ft_printf("Path ID %d : ", paths->path_id);
		path_lst = paths->path_lst->next;
		while (path_lst != NULL)
		{
			if ((path_lst->room->ants_lst != NULL) && \
			(path_lst->room->position != END))
				ft_printf("| %s : %d |", path_lst->room->name, path_lst->room->ants_lst->ant_id);
			else if ((path_lst->room->ants_lst != NULL) && \
			(path_lst->room->position == END))
			{
				ants_lst = path_lst->room->ants_lst;
				// delete = path_lst->room->ants_lst;
				// ft_printf("\n ants in end room \n");
				// while (delete != NULL)
				// {
				// 	ft_printf("%d -> ", delete->ant_id);
				// 	delete = delete->next;
				// }
				// ft_printf(" ant %d has path  %p \n", ants_lst->ant_id, ants_lst->path->path_id);
				while ((ants_lst->next != NULL) && \
				(ants_lst->path->path_id != paths->path_id))
				{
					ants_lst = ants_lst->next;
				}
				if (ants_lst->path->path_id == paths->path_id)
				{
					ft_printf("| %s : %d |", path_lst->room->name, ants_lst->ant_id);
				}
				else
					ft_printf("| %s : 0 |", path_lst->room->name);
			}
			else
				ft_printf("| %s : 0 |", path_lst->room->name);
			path_lst = path_lst->next;
			if (path_lst != NULL)
				ft_printf(" -> ");
		}
		paths = paths->next;
		// ft_printf("\nnext path %p \n", paths);
	}
	ft_printf(ANSI_COLOR_RESET);
}

void				ft_print_move(t_ant_farm *ant_farm)
{
	t_paths			*paths;
	t_path_list		*path_lst;
	t_ants			*ants_lst;
	t_ants			*ants_lst_end;

	// ft_printf(ANSI_COLOR_GREEN_BOLD"\nPrinting the move / line\n");
	paths = ant_farm->paths;
	while (paths != NULL)
	{
		path_lst = paths->path_lst;
		while (path_lst->next != NULL)
			path_lst = path_lst->next;
		ants_lst = path_lst->room->ants_lst;
		// if (ants_lst != NULL)
			// ft_printf(" >>>> room %s ant %d \n", path_lst->room->name, ants_lst->ant_id);
		while (path_lst != NULL)
		{
			if (path_lst->room->ants_lst != NULL)
			{
				// ft_printf("- ant_id %d-%s\n", path_lst->room->ants_lst->ant_id, path_lst->room->name);
				if ((path_lst->room->position != END) && (path_lst->room->ants_lst->ant_id != 0))
					ft_printf("L%d-%s ", path_lst->room->ants_lst->ant_id, path_lst->room->name);
					// ft_printf("| %s : %d |", path_lst->room->name, path_lst->room->ants_lst->ant_id);
				else if (path_lst->room->position == END)
				{
					// ft_printf("- ant_id %d-%s\n", path_lst->room->ants_lst->ant_id, path_lst->room->name);
					ants_lst_end = path_lst->room->ants_lst;
					// ft_printf(" ant %d has path  %p \n", ants_lst->ant_id, ants_lst->path->path_id);
					while ((ants_lst_end->next != NULL) && \
					(ants_lst_end->path->path_id != paths->path_id))
					{
						ants_lst_end = ants_lst_end->next;
					}
					// ft_printf(" antlstpath %d and path %d \n", ants_lst_end->path->path_id, paths->path_id);
					if ((ants_lst_end->path->path_id == paths->path_id) && \
					(ants_lst_end->ant_id != 0))
					{
						ft_printf("L%d-%s ", ants_lst_end->ant_id, path_lst->room->name);
						// ft_printf("| %s : %d |", path_lst->room->name, ants_lst_end->ant_id);
					}
				}
			}
			path_lst = path_lst->prev;
		}
		paths = paths->next;
	}
	ft_printf("\n");
}
