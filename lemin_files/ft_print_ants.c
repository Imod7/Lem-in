/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_ants.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/27 09:42:42 by dominique     #+#    #+#                 */
/*   Updated: 2020/05/27 09:56:08 by dominique     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void				ft_print_ants(t_ant_farm *ant_farm)
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
		paths = paths->next;
		ft_printf("\n");
		// ft_printf("next path %p \n", paths);
	}
	ft_printf("----------------------\n");
	ft_printf(ANSI_COLOR_RESET);
}
