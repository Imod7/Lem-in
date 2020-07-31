/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_ants.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:38:51 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/30 16:16:39 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** Function that prints the path IDs of the discovered paths
** and all the ants that are assigned to each path.
*/

void				ft_print_ants_in_paths(t_ant_farm *ant_farm)
{
	t_paths			*paths;
	t_ants			*ants_lst;

	ft_printf(ANSI_COLOR_YELLOW_PAST"\nAnts assigned to Paths \n");
	paths = ant_farm->paths;
	while (paths != NULL)
	{
		ft_printf(ANSI_COLOR_BLUE"Path ID %d ", paths->path_id);
		ft_printf("[ Run %d: PathSize %d + ", paths->run, paths->path_size);
		ft_printf("Ants %d = ", paths->ants_amount);
		ft_printf("TotalSize : %d]: ", paths->path_size + paths->ants_amount);
		ft_printf(ANSI_COLOR_RESET);
		ants_lst = paths->ants_lst;
		while (ants_lst != NULL)
		{
			// ft_printf("path list not NULL  \n");
			ft_printf("%d", ants_lst->ant_id);
			ants_lst = ants_lst->next;
			if (ants_lst != NULL)
				ft_printf(" -> ");
		}
		paths = paths->next;
		ft_printf("\n");
		// ft_printf("next path %p \n", paths);
	}
	ft_printf(ANSI_COLOR_RESET);
}

/*
** Function that iterates through the linked list of ants
** of the sink and prints only the ant of the room of the current
** path we are right now. If it has no ant assigned it prints 0.
** We have to iterate through the linked list of ants
** (since we can have more than one ant in the sink) and print
** the corresponding ant.
*/

static void			ft_print_ants_in_sink(t_ants *ants_lst, t_paths *paths, \
										t_path_list *path_lst)
{
	while ((ants_lst->next != NULL) && \
	(ants_lst->path->path_id != paths->path_id))
	{
		ants_lst = ants_lst->next;
	}
	if (ants_lst->path->path_id == paths->path_id)
	{
		ft_printf("| %s : %d |", path_lst->room->name, \
		ants_lst->ant_id);
	}
	else
		ft_printf("| %s : 0 |", path_lst->room->name);
}

/*
** Function that checks the position of the room.
** Depending on whether it is an intermediate room or the sink,
** it prints the ant or calls the ft_print_ants_in_sink function
** respectively.
*/

static void			ft_check_room_position(t_path_list *path_lst, \
											t_paths *paths)
{
	if ((path_lst->room->ants_lst != NULL) && \
	(path_lst->room->position != END))
		ft_printf("| %s : %d |", path_lst->room->name, \
		path_lst->room->ants_lst->ant_id);
	else if ((path_lst->room->ants_lst != NULL) && \
	(path_lst->room->position == END))
	// {
		ft_print_ants_in_sink(path_lst->room->ants_lst, paths, \
		path_lst);
		// ants_lst = path_lst->room->ants_lst;
		// while ((ants_lst->next != NULL) && \
		// (ants_lst->path->path_id != paths->path_id))
		// {
		// 	ants_lst = ants_lst->next;
		// }
		// if (ants_lst->path->path_id == paths->path_id)
		// {
		// 	ft_printf("| %s : %d |", path_lst->room->name, \
		// 	ants_lst->ant_id);
		// }
		// else
		// 	ft_printf("| %s : 0 |", path_lst->room->name);
	// }
	else
		ft_printf("| %s : 0 |", path_lst->room->name);
}

/*
** Function that prints the discovered paths and all its rooms
** and in each room it shows if there is an ant (prints the number of ant)
** or not (prints a zero).
*/

void				ft_print_ants_in_rooms(t_ant_farm *ant_farm)
{
	t_paths			*paths;
	t_path_list		*path_lst;

	ft_printf(ANSI_COLOR_YELLOW_PAST"Ants in Rooms\n");
	paths = ant_farm->paths;
	while (paths != NULL)
	{
		// ft_printf("path run %d - best run %d \n", paths->run, ant_farm->best_run);
		if (paths->run == ant_farm->best_run)
		{
			ft_printf("Path ID %d : ", paths->path_id);
			path_lst = paths->path_lst->next;
			while (path_lst != NULL)
			{
				ft_check_room_position(path_lst, paths);
				// if ((path_lst->room->ants_lst != NULL) && \
				// (path_lst->room->position != END))
				// 	ft_printf("| %s : %d |", path_lst->room->name, \
				// 	path_lst->room->ants_lst->ant_id);
				// else if ((path_lst->room->ants_lst != NULL) && \
				// (path_lst->room->position == END))
				// // {
				// 	ft_print_ants_in_sink(path_lst->room->ants_lst, paths, \
				// 	path_lst);
				// 	// ants_lst = path_lst->room->ants_lst;
				// 	// while ((ants_lst->next != NULL) && \
				// 	// (ants_lst->path->path_id != paths->path_id))
				// 	// {
				// 	// 	ants_lst = ants_lst->next;
				// 	// }
				// 	// if (ants_lst->path->path_id == paths->path_id)
				// 	// {
				// 	// 	ft_printf("| %s : %d |", path_lst->room->name, \
				// 	// 	ants_lst->ant_id);
				// 	// }
				// 	// else
				// 	// 	ft_printf("| %s : 0 |", path_lst->room->name);
				// // }
				// else
				// 	ft_printf("| %s : 0 |", path_lst->room->name);
				path_lst = path_lst->next;
				// (path_lst == NULL) ? : ft_printf(" -> ");
				if (path_lst != NULL)
					ft_printf(" -> ");
			}
			ft_printf("\n");
		}
		paths = paths->next;
	}
	ft_printf(ANSI_COLOR_RESET);
}
