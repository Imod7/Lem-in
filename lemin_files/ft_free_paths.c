/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_paths.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:38:25 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/06/28 12:34:13 by dsaripap      ########   odam.nl         */
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
		curr_node->room->path = NULL;
		// ft_printf(" freeing path node %d - %s\n", curr_node->room->path_id, curr_node->room->name);
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
		ft_free_pathlst(curr_node->path_lst);
		// ft_printf(" freeing path id  %d\n", curr_node->path_id);
		curr_node->path_id = 0;
		next_node = curr_node->next;
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

	curr_node = ant_farm->paths;
	while (curr_node->next != NULL)
	{
		curr_node = curr_node->next;
	}
	ft_free_pathlst(curr_node->path_lst);
	curr_node->prev->next = NULL;
	curr_node->path_id = 0;
	free(curr_node);
}
