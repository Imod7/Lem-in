/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_paths_auxfunc.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:38:16 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/06/19 10:38:18 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void				ft_pathlst_addstart(t_path_list **lst, t_path_list *new)
{
	t_path_list		*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	*lst = new;
	new->next = temp;
	temp->prev = new;
}

void				ft_pathlst_addend(t_path_list **lst, t_path_list *new)
{
	t_path_list		*temp;

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

void				ft_path_addend(t_paths **path, t_paths *new)
{
	t_paths			*temp;

	if (*path == NULL)
	{
		*path = new;
		new->path_id = 1;
		return ;
	}
	temp = *path;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
	new->path_id = temp->path_id + 1;
}

size_t				ft_find_maxpaths(t_ant_farm *ant_farm)
{
	t_room			*temp;
	t_neighbor		*neighbors_lst;
	size_t			count_s;
	size_t			count_e;
	size_t			max_paths;

	count_s = 0;
	count_e = 0;
	temp = ft_get_start_room(ant_farm->rooms_lst);
	neighbors_lst= temp->neighbors;
	while (neighbors_lst != NULL)
	{
		count_s += 1;
		neighbors_lst = neighbors_lst->next;
	}
	temp = ft_get_end_room(ant_farm);
	neighbors_lst= temp->neighbors;
	while (neighbors_lst != NULL)
	{
		count_e += 1;
		neighbors_lst = neighbors_lst->next;
	}
	max_paths = (count_s <= count_e) ? count_s : count_e;
	return (max_paths);
}
