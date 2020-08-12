/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_paths.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:39:05 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 14:30:26 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void				ft_print_paths(t_ant_farm *ant_farm)
{
	t_path_list		*path_temp;
	t_paths			*paths;

	ft_printf(ANSI_COLOR_YELLOW_PAST"\nPrinting the discovered paths \n");
	paths = ant_farm->paths;
	while (paths != NULL)
	{
		ft_printf(ANSI_COLOR_BLUE"Path ID %d ", paths->path_id);
		ft_printf(" [ Run %d - Path Size %d ] : ", paths->run, \
		paths->path_size);
		ft_printf(ANSI_COLOR_RESET);
		path_temp = paths->path_lst;
		while (path_temp != NULL)
		{
			ft_printf("%s", path_temp->room->name);
			path_temp = path_temp->next;
			if (path_temp != NULL)
				ft_printf(" -> ");
		}
		paths = paths->next;
		ft_printf("\n");
	}
	ft_printf(ANSI_COLOR_RESET);
}

void				ft_print_paths_sizes(t_ant_farm *ant_farm)
{
	t_paths			*paths;

	paths = ant_farm->paths;
	while (paths != NULL)
	{
		ft_printf("Path ID %d : ", paths->path_id);
		ft_printf(" [ Path Size : %d ", paths->path_size);
		ft_printf(" - Run : %d ] \n", paths->run);
		paths = paths->next;
	}
}

static void			ft_path_lst_iter(t_path_list *paths_lst)
{
	while (paths_lst != NULL)
	{
		ft_printf("%s", paths_lst->room->name);
		paths_lst = paths_lst->next;
		if (paths_lst != NULL)
			ft_printf(" -> ");
	}
}

void				ft_print_paths_list(t_ant_farm *ant_farm)
{
	t_paths			*paths;

	paths = ant_farm->paths;
	ft_printf("\n               Paths List          \n");
	ft_printf("---------------------------------------------------------\n");
	ft_printf("|path_id\tpath_size\tants_amount\tprev\tnext\tpath_list\t\t|\n");
	while (paths != NULL)
	{
		ft_printf("%d\t\t%d\t\t", paths->path_id, paths->path_size);
		ft_printf("%d\t\t", paths->ants_amount);
		if (paths->prev)
			ft_printf("%d\t", paths->prev->path_id);
		else
			ft_printf("NULL\t");
		if (paths->next)
			ft_printf("%d\t", paths->next->path_id);
		else
			ft_printf("NULL\t");
		ft_path_lst_iter(paths->path_lst);
		paths = paths->next;
		ft_printf("\n");
	}
	ft_printf("---------------------------------------------------------\n");
}
