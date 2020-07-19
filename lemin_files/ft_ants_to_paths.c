/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ants_to_paths.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:11:44 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/17 16:41:56 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** Precalculation of the number of lines we are going to need to move
** all the ants from source room to sink.
** The final result lines is max_lines - 2 because in the path_size
** source room and sink room are included but while moving the ants
** we do not need to include them in the lines.
** The reason is because in the beginning the subject assumes that
** all ants are at the source room so we start printing lines from the
** next room. Here we save 1 line.
** Also, as soon as the last ant reached the end we are over so we do not
** an extra line to move the ant from sink to somewhere else. And here we save
** the second line.
*/

void				ft_calculate_lines(t_ant_farm *ant_farm)
{
	t_paths			*paths;
	size_t			total_size;
	size_t			max_lines;

	max_lines = 0;
	paths = ant_farm->paths;
	while (paths != NULL)
	{
		if (paths->ants_lst != NULL)
		{
			// ft_printf("path_id %d, paths_size %d, ants %d\n", paths->path_id, paths->path_size, paths->ants_amount);
			total_size = paths->path_size + paths->ants_amount;
			if (total_size > max_lines)
				max_lines = total_size;
		}
		paths = paths->next;
	}
	ant_farm->lines = max_lines - 2;
	// ft_printf(ANSI_COLOR_CYAN"Lines Needed: %d \n\n", ant_farm->lines);
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

int					ft_all_ants_in_same_path(t_ant_farm *ant_farm)
{
	t_paths			*tmp;
	t_ants			*ant;
	size_t			i;

	i = 1;
	tmp = ant_farm->paths;
	// ft_printf("All ants in same path\n");
	while (i <= ant_farm->ants)
	{
		ant = (t_ants *)ft_memalloc(sizeof(t_ants));
		ant->ant_id = i;
		ant->path = tmp;
		// ft_printf(ANSI_COLOR_BLUE"ant_id: %d in path_id: %d\n"ANSI_COLOR_RESET, ant->ant_id, ant->path->path_id);
		ft_ants_to_pathlst_addend(&(tmp->ants_lst), ant);
		i += 1;
	}
	tmp->ants_amount = i - 1;
	return (SUCCESS);
}

/*
** Comparing the total_size (path_size + ants_amount) of current_path,
** next_path and first_path and we decide to assign the ant to the
** current, next or first path respectively.
*/

void				ft_compare_sizes(t_ant_farm *ant_farm, t_paths **cur, \
									size_t i)
{
	t_paths			*first;
	t_paths			*next;
	t_ants			*ant;
	size_t			first_size;
	size_t			next_size;

	ant = (t_ants *)ft_memalloc(sizeof(t_ants));
	ant->ant_id = i;
	first = ant_farm->paths;
	first_size = first->path_size + first->ants_amount;
	if ((*cur)->next != NULL)
		next = (*cur)->next;
	else
		next = ant_farm->paths;
	next_size = next->path_size + next->ants_amount;
	// ft_printf(ANSI_COLOR_BLUE"cur_pathid: %d, size = %d\n"ANSI_COLOR_RESET, 
	// cur->path_id, cur->path_size + cur->ants_amount);
	// if ((*cur)->next != NULL)
	// {
	// 		ft_printf(ANSI_COLOR_YELLOW_PAST"next_pathid: %d, size = %d\n" 
	// 		ANSI_COLOR_RESET, next->path_id, next_size);
	// }
	// else
	// {
	// 		ft_printf(ANSI_COLOR_YELLOW_PAST"next_pathid: %d, size = %d\n" 
	// 		ANSI_COLOR_RESET, next->path_id, next_size);
	// }
	if (((*cur)->path_size + (*cur)->ants_amount <= next_size) && \
	((*cur)->path_size + (*cur)->ants_amount <= first_size))
	{
		// assign to current path
		ant->path = (*cur);
		(*cur)->ants_amount += 1;
	}
	else if (((*cur)->path_size + (*cur)->ants_amount <= next_size) && \
	((*cur)->path_size + (*cur)->ants_amount > first_size))
	{
		// assign to first path
		ant->path = first;
		first->ants_amount += 1;
		(*cur) = first;
	}
	else
	{
		// assign ant to next path
		ant->path = next;
		next->ants_amount += 1;
		(*cur) = next;
	}
	ft_ants_to_pathlst_addend(&(ant->path->ants_lst), ant);
	// return (ant);
}

int					ft_ants_to_paths(t_ant_farm *ant_farm)
{
	t_paths			*tmp;
	// t_path_list		*tmp_lst;
	size_t			i;

	// ft_printf("\nAssigning Ants to Paths\n");
	// ft_printf("========================\n");
	// ft_printf("Number of ants : %d \n", ant_farm->ants);
	// ft_printf("Max paths : %d \n", ant_farm->max_paths);
	// ft_printf("Discovered paths : %d \n", ant_farm->discovered_paths);
	// ft_print_paths_list(ant_farm);
	if (ant_farm->ants == 0)
		return (SUCCESS);
	if (ant_farm->discovered_paths == 0)
		return (SUCCESS);
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
		// tmp_lst = tmp->path_lst->next;
		while ((tmp != NULL) && (i <= ant_farm->ants))
		{
			ft_compare_sizes(ant_farm, &tmp, i);
			i += 1;
		}
	}
	ft_calculate_lines(ant_farm);
	return (0);
}
