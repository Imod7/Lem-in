/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_paths.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:38:25 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/07 16:44:49 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void				ft_free_pathlst(t_path_list *path_lst)
{
	t_path_list		*curr_node;
	t_path_list		*next_node;

	curr_node = path_lst;
	while (curr_node != NULL)
	{
		next_node = curr_node->next;
		// curr_node->room->path_id = 0;
		// ft_printf(" freeing from path %d - node %s\n", curr_node->room->path->path_id, curr_node->room->name);
		// ft_printf("   freeing from path - node %s\n", curr_node->room->name);
		// curr_node->room->path = NULL;
		// curr_node = NULL;
		free(curr_node);
		curr_node = next_node;
	}
	path_lst = NULL;
}

void				ft_free_paths(t_ant_farm *ant_farm)
{
	t_paths			*curr_node;
	t_paths			*next_node;

	curr_node = ant_farm->paths;
	while (curr_node != NULL)
	{
		// ft_printf(" .freeing from path id %d the ants list\n", curr_node->path_id);
		ft_free_ants_lst(&(curr_node->ants_lst));
		// ft_printf(" .freeing from path id %d the paths list\n", curr_node->path_id);
		ft_free_pathlst(curr_node->path_lst);
		// ft_printf(" freeing path id  %d\n", curr_node->path_id);
		// curr_node->path_id = 0;
		next_node = curr_node->next;
		// curr_node = NULL;
		free(curr_node);
		curr_node = next_node;
	}
	ant_farm->paths = NULL;
}

/*
** Deletes the last path from the linked list of paths (ant_farm->paths)
** The path that it deletes depends on the paths that are already saved in
** ant_farm->paths linked list right before this function is called
*/

void				ft_path_del_last(t_ant_farm *ant_farm)
{
	t_paths			*curr_node;
	// t_paths			*prev_node;

	curr_node = ant_farm->paths;
	while (curr_node->next != NULL)
	{
		// prev_node = curr_node;
		curr_node = curr_node->next;
	}
	// ft_printf(" freeing path id  %d\n", curr_node->path_id);
	ft_free_pathlst(curr_node->path_lst);
	// ft_printf(" prev path id  %d\n", prev_node->path_id);
	// prev_node->next = NULL;
	curr_node->prev->next = NULL;
	// curr_node->path_id = 0;
	// curr_node = NULL;
	// ft_printf(" curr node %p\n", curr_node);
	free(curr_node);
}
