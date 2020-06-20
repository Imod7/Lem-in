/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ants_to_paths.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:11:44 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/06/20 15:05:33 by dominiquesa   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void				ft_calculate_lines(t_ant_farm *ant_farm)
{
	t_paths			*paths;
	size_t			total_size;
	size_t			max_lines;

	max_lines = 0;
	paths = ant_farm->paths;
	while (paths != NULL)
	{
		total_size = paths->path_size + paths->ants_amount;
		if (total_size > max_lines)
			max_lines = total_size;
		paths = paths->next;
	}
	ant_farm->lines = max_lines - 1;
	ft_printf(ANSI_COLOR_CYAN"Lines Needed : %d \n\n", ant_farm->lines);
}

int					ft_all_ants_in_same_path(t_ant_farm *ant_farm)
{
	t_paths			*tmp;
	t_ants			*ant;
	size_t			i;

	i = 1;
	tmp = ant_farm->paths;
	ft_printf("All ants in same path\n");
	while (i <= ant_farm->ants)
	{
		ant = (t_ants *)ft_memalloc(sizeof(t_ants));
		ant->ant_id = i;
		ant->path = tmp;
		// ft_printf(ANSI_COLOR_BLUE"ant_id: %d in path_id: %d\n"ANSI_COLOR_RESET, ant->ant_id, ant->path->path_id);
		i += 1;
	}
	return (0);
}

void				ft_ants_to_pathlst_addend(t_ants **lst, t_ants *new)
{
	t_ants			*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

int					ft_ants_to_paths(t_ant_farm *ant_farm)
{
	t_paths			*tmp;
	t_path_list		*tmp_lst;
	size_t			i;
	t_paths			*cur;
	t_paths			*next;
	t_ants			*ant;

	ft_printf("\nAssigning Ants to Paths\n");
	ft_printf("========================\n");
	ft_printf("Number of ants : %d \n", ant_farm->ants);
	// ft_printf("Max paths : %d \n", ant_farm->max_paths);
	ft_printf("Discovered paths : %d \n", ant_farm->discovered_paths);
	// ft_print_paths_list(ant_farm);
	if (ant_farm->ants == 0)
		return (SUCCESS);
	if (ant_farm->discovered_paths == 0)
		return (SUCCESS);
	if (ant_farm->discovered_paths == 1)
	{
		ft_all_ants_in_same_path(ant_farm);
		return (SUCCESS);
	}
	i = 1;
	while (i <= ant_farm->ants) //&& (ant_farm->discovered_paths > 1))
	{
		tmp = ant_farm->paths;
		tmp_lst = tmp->path_lst->next;
		while ((tmp != NULL) && (i <= ant_farm->ants))
		{
			ant = (t_ants *)ft_memalloc(sizeof(t_ants));
			ant->ant_id = i;
			cur = tmp;
			if (cur->next != NULL)
				next = cur->next;
			else
				next = ant_farm->paths;
			// ft_printf(ANSI_COLOR_BLUE"cur_pathid: %d, size = %d\n"ANSI_COLOR_RESET, cur->path_id, cur->path_size + cur->ants_amount);
			if (tmp->next != NULL)
			{
				// ft_printf(ANSI_COLOR_YELLOW_PAST"next_pathid: %d, size = %d\n" \
				// ANSI_COLOR_RESET, next->path_id, \
				// next->path_size + next->ants_amount);
			}
			else
			{
				// ft_printf(ANSI_COLOR_YELLOW_PAST"next_pathid: %d, size = %d\n" \
				// ANSI_COLOR_RESET, ant_farm->paths->path_id, \
				// ant_farm->paths->path_size + ant_farm->paths->ants_amount);
			}
			if (cur->path_size + cur->ants_amount <= next->path_size + next->ants_amount)
			{
				// assign to current path
				ant->path = cur;
				cur->ants_amount += 1;
			}
			else
			{
				// assign ant to next path
				ant->path = next;
				next->ants_amount += 1;
				tmp = next;
			}
			// ft_ants_addend(&(tmp_lst->room->ants), ant);
			ft_ants_to_pathlst_addend(&(ant->path->ants_lst), ant);
			// ft_printf(ANSI_COLOR_GREEN_EMER"ant_id: %d, path_id = %d\n\n"ANSI_COLOR_RESET, ant->ant_id, ant->path->path_id);
			i += 1;
		}
	}
	ft_print_ants_in_paths(ant_farm);
	ft_calculate_lines(ant_farm);
	return (0);
}
