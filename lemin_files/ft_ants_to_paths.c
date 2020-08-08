/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ants_to_paths.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:11:44 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/07 19:46:11 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int					ft_all_ants_in_same_path(t_ant_farm *ant_farm)
{
	t_paths			*tmp;
	t_ants			*ant;
	long long		i;

	i = 1;
	tmp = ant_farm->paths;
	while (tmp != NULL && tmp->run != ant_farm->best_run)
		tmp = tmp->next;
	// ft_printf("All ants in same path\n");
	while (i <= ant_farm->ants)
	{
		ant = (t_ants *)ft_memalloc(sizeof(t_ants));
		ant->ant_id = i;
		ant->path = tmp;
		// ft_printf(ANSI_COLOR_BLUE"ant_id: %d in path_id: %d\n"ANSI_COLOR_RESET, ant->ant_id, ant->path->path_id);
		ft_add_ant_to_antslist(&(tmp->ants_lst), ant);
		i += 1;
	}
	tmp->ants_amount = i - 1;
	return (SUCCESS);
}

void				ft_assign_based_on_size(t_ants **ant, t_paths **cur, \
											t_paths *first, t_paths *next)
{
	size_t			first_size;
	size_t			next_size;

	first_size = first->path_size + first->ants_amount;
	next_size = next->path_size + next->ants_amount;
	if (((*cur)->path_size + (*cur)->ants_amount <= next_size) && \
	((*cur)->path_size + (*cur)->ants_amount <= first_size))
	{
		// assign to current path
		(*ant)->path = (*cur);
		(*cur)->ants_amount += 1;
	}
	else if (((*cur)->path_size + (*cur)->ants_amount <= next_size) && \
	((*cur)->path_size + (*cur)->ants_amount > first_size))
	{
		// assign to first path
		(*ant)->path = first;
		first->ants_amount += 1;
		(*cur) = first;
	}
	else
	{
		// assign ant to next path
		(*ant)->path = next;
		next->ants_amount += 1;
		(*cur) = next;
	}
}

/*
** We compare the total_size (path_size + ants_amount) of current_path,
** next_path and first_path and we decide in which path to assign the ant.
*/

void				ft_compare_sizes(t_ant_farm *ant_farm, t_paths **cur, \
									size_t i)
{
	t_paths			*first;
	t_paths			*next;
	t_ants			*ant;

	ant = (t_ants *)ft_memalloc(sizeof(t_ants));
	ant->ant_id = i;
	first = ant_farm->paths;
	while (first != NULL && first->run != ant_farm->best_run)
		first = first->next;
	// ft_printf(">> Compare sizes best run %d next \n", ant_farm->best_run);
	if ((*cur)->next != NULL && (*cur)->next->run == ant_farm->best_run)
		next = (*cur)->next;
	else
	{
		next = ant_farm->paths;
		while (next != NULL && next->run != ant_farm->best_run)
			next = next->next;
	}
	// ft_printf(ANSI_COLOR_BLUE"cur_pathid: %d, size = %d\n"ANSI_COLOR_RESET, 
	// (*cur)->path_id, (*cur)->path_size + (*cur)->ants_amount);
	// if ((*cur)->next != NULL && (*cur)->next->run == ant_farm->best_run)
	// {
			// ft_printf(ANSI_COLOR_YELLOW_PAST"next_pathid: %d, size = %d\n" 
			// ANSI_COLOR_RESET, next->path_id, next_size);
	// }
	// else
	// {
			// ft_printf(ANSI_COLOR_YELLOW_PAST"next_pathid: %d, size = %d\n" 
			// ANSI_COLOR_RESET, next->path_id, next_size);
	// }
	ft_assign_based_on_size(&ant, cur, first, next);
	ft_add_ant_to_antslist(&(ant->path->ants_lst), ant);
	// ft_printf("ant_id:%d,path_id=%d\n\n", ant->ant_id, ant->path->path_id);
}

int					ft_ants_to_paths(t_ant_farm *ant_farm)
{
	t_paths			*tmp;
	long long		i;

	// ft_printf("\nAssigning Ants to Paths\n");
	// ft_printf("Number of ants : %d \n", ant_farm->ants);
	// ft_printf("Max paths : %d \n", ant_farm->max_paths);
	// ft_printf("Discovered paths : %d \n", ant_farm->discovered_paths);
	// ft_print_paths_list(ant_farm);
	if ((ant_farm->ants == 0) || (ant_farm->discovered_paths == 0))
		return (SUCCESS);
	// if (ant_farm->discovered_paths == 0)
	// 	return (SUCCESS);
	if ((ant_farm->discovered_paths == 1) || (ant_farm->ants == 1))
	{
		// ft_printf("all ants in same path \n");
		ft_all_ants_in_same_path(ant_farm);
		ft_calculate_lines(ant_farm);
		return (SUCCESS);
	}
	i = 1;
	while (i <= ant_farm->ants)
	{
		tmp = ant_farm->paths;
		while (tmp != NULL && tmp->next != NULL && tmp->run != ant_farm->best_run)
			tmp = tmp->next;
		// ft_printf("I am at path id %d and in ant %d\n", tmp->path_id, i);
		// tmp_lst = tmp->path_lst->next;
		while ((tmp != NULL && tmp->run == ant_farm->best_run && i <= ant_farm->ants))
		{
			// ft_printf("I am at path id %d and in ant %d\n", tmp->path_id, i);
			ft_compare_sizes(ant_farm, &tmp, i);
			i += 1;
		}
	}
	ft_calculate_lines(ant_farm);
	return (0);
}
