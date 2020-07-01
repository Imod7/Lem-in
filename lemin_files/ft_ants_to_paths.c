/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ants_to_paths.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:11:44 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/01 12:58:55 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
// void				ft_assign_and_move(t_ant_farm *ant_farm, t_paths *path, 
// 										t_ants *ant)
// {
// 	t_path_list		*path_lst;
// 	// t_paths			*path;

// 	(void)ant_farm;
// 	// ft_printf("Try to assign %d to path %d\n", ant_id, path->path_id);
// 	path_lst = path->path_lst->next;
// 	while (path_lst != NULL)
// 	{
// 		if (path_lst->room->ants != NULL)
// 			path_lst = path_lst->next;
// 		else
// 			break ;
// 	}
// 	path_lst = path_lst->prev;
// 	while (path_lst != NULL)
// 	{
// 		if (path_lst->room->position == END)
// 		{
// 			ft_printf(" END room\n");
			// ft_ants_addend(&(path_lst->room->ants), ant);
// 		}
// 		if (path_lst->room->ants != NULL)
// 		{
// 			ft_printf("   Ant %d to room %s", path_lst->room->ants->ant_id, path_lst->next->room->name);
// 			path_lst->next->room->ants = path_lst->room->ants;
// 			ft_printf(" Ant %d to room %s\n", ant->ant_id, path_lst->room->name);
// 			path_lst->room->ants = ant;
// 			// ft_printf("ant %d, room %s \n",path_lst->room->ant_id, path_lst->room->name);
// 		}
// 		else
// 		{
// 			// path_lst->room->ant_id = ant_id;
// 			break ;
// 		}
// 			// path_lst->room->ant_id = path_lst->prev->room->ant_id;
// 		path_lst = path_lst->prev;
// 	}
// 	// ft_printf("\n");	
// }

int					ft_all_ants_in_same_path(t_ant_farm *ant_farm)
{
	t_paths			*tmp;
	t_ants			*ant;
	size_t			i;

	i = 1;
	tmp = ant_farm->paths;
	while (i <= ant_farm->ants)
	{
		ant = (t_ants *)ft_memalloc(sizeof(t_ants));
		ant->ant_id = i;
		ant->path = tmp;
		ft_printf(ANSI_COLOR_BLUE"ant_id: %d in path_id: %d\n"ANSI_COLOR_RESET, ant->ant_id, ant->path->path_id);
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
	// t_path_list		*tmp_lst;
	size_t			i;
	t_paths			*cur;
	t_paths			*next;
	t_ants			*ant;

	ft_printf("\nAssigning Ants to Paths\n");
	ft_printf("========================\n");
	// ft_printf("Number of ants : %d \n", ant_farm->ants);
	// ft_printf("Max paths : %d \n", ant_farm->max_paths);
	// ft_printf("Discovered paths : %d \n", ant_farm->discovered_paths);
	// ft_print_paths_list(ant_farm);
	if (ant_farm->ants == 0)
		return (0);
	if (ant_farm->discovered_paths == 0)
		return (0);
	if (ant_farm->discovered_paths == 1)
	{
		ft_all_ants_in_same_path(ant_farm);
		return (0);
	}
	i = 1;
	while ((i <= ant_farm->ants) && (ant_farm->discovered_paths > 1))
	{
		tmp = ant_farm->paths;
		// tmp_lst = tmp->path_lst->next;
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
				// ft_printf(ANSI_COLOR_YELLOW_PAST"next_pathid: %d, size = %d\n"ANSI_COLOR_RESET, next->path_id, next->path_size + next->ants_amount);
				// ft_printf(ANSI_COLOR_YELLOW_PAST"next_pathid: %d, size = %d\n"ANSI_COLOR_RESET, ant_farm->paths->path_id, ant_farm->paths->path_size + ant_farm->paths->ants_amount);
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
	ft_print_ants(ant_farm);
	ft_move_ants(ant_farm);
	// ft_keep_ants_moving(ant_farm);
	return (0);
}
