/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_paths_print.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/11 15:14:08 by dominique     #+#    #+#                 */
/*   Updated: 2020/05/18 12:47:08 by dominique     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void				ft_print_paths(t_ant_farm *ant_farm)
{
	t_path_list		*path_temp;
	t_paths			*paths;

	ft_printf(ANSI_COLOR_CYAN"Printing the discovered paths \n");
	paths = ant_farm->paths;
	while (paths != NULL)
	{
		ft_printf("Path ID %d : ", paths->path_id);
		path_temp = paths->path_lst;
		while (path_temp != NULL)
		{
			// ft_printf("path list not NULL  \n");
			ft_printf("%s", path_temp->room->name);
			path_temp = path_temp->next;
			if (path_temp != NULL)
				ft_printf(" -> ");
		}
		paths = paths->next;
		ft_printf("\n");
		// ft_printf("next path %p \n", paths);
	}
	ft_printf("----------------------\n");
	ft_printf(ANSI_COLOR_RESET);
}

void				ft_print_paths_list(t_ant_farm *ant_farm)
{
	t_path_list		*paths_lst;
	t_paths			*paths;

	paths = ant_farm->paths;
	ft_printf("\n               Paths List          \n");
	ft_printf("---------------------------------------------------------\n");
	ft_printf("|path_id\tprev\tnext\tpaths_list\t\t|\n");
	while (paths != NULL)
	{
		ft_printf("%d\t\t", paths->path_id);
		if (paths->prev)
			ft_printf("%d\t", paths->prev->path_id);
		else
			ft_printf("NULL\t");
		if (paths->next)
			ft_printf("%d\t", paths->next->path_id);
		else
			ft_printf("NULL\t");
		paths_lst = paths->path_lst;
		while (paths_lst != NULL)
		{
			ft_printf("%s", paths_lst->room->name);
			paths_lst = paths_lst->next;
			if (paths_lst != NULL)
				ft_printf(" -> ");
		}
		paths = paths->next;
		ft_printf("\n");
	}
	ft_printf("---------------------------------------------------------\n");
	ft_printf(ANSI_COLOR_RESET);
}

void				ft_print_paths_list_detail(t_ant_farm *ant_farm)
{
	t_path_list		*paths_lst;
	t_paths			*paths;

	paths = ant_farm->paths;
	ft_printf("\n               Paths List          \n");
	ft_printf("---------------------------------------------------------\n");
	ft_printf("|path_id\tprev\tnext\n");
	while (paths != NULL)
	{
		ft_printf("%d\t\t", paths->path_id);
		if (paths->prev)
			ft_printf("%d\t", paths->prev->path_id);
		else
			ft_printf("NULL\t");
		if (paths->next)
			ft_printf("%d\t", paths->next->path_id);
		else
			ft_printf("NULL\t");
		paths_lst = paths->path_lst;
		ft_printf("\npaths_list\tnext\tprev\n|");
		while (paths_lst != NULL)
		{
			ft_printf("%s\t\t", paths_lst->room->name);
			if (paths_lst->next != NULL)
				ft_printf("%s\t", paths_lst->next->room->name);
			else
				ft_printf("NULL\t");
			if (paths_lst->prev != NULL)
				ft_printf("%s\t", paths_lst->prev->room->name);
			else
				ft_printf("NULL\t");
			paths_lst = paths_lst->next;
			if (paths_lst != NULL)
				ft_printf("\n -> ");
		}
		paths = paths->next;
		ft_printf("\n");
	}
	ft_printf("---------------------------------------------------------\n");
	ft_printf(ANSI_COLOR_RESET);
}
