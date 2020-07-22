/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_paths.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:38:25 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/21 13:19:55 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** Deletes the path_list given.
** Before freeing I set the score of the corresponding rooms to 0
** because they don't belong anymore to a path.
** This is helpful when augmenting the graph.
*/

void				ft_free_pathlst(t_path_list *path_lst)
{
	t_path_list		*curr_node;
	t_path_list		*next_node;

	curr_node = path_lst;
	while (curr_node != NULL)
	{
		curr_node->room->score = 0;
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

	// ft_printf("Delete Last Path\n");
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
	ft_printf(" curr node %p\n", curr_node);
	ft_printf(" prev path id %d prev next  %p\n", curr_node->prev->path_id, curr_node->prev->next);
	free(curr_node);
}

/*
** Deletes the path from the linked list of paths (ant_farm->paths)
** based on the path_id given.
*/

void				ft_free_path_on_pathid(t_ant_farm *ant_farm, int path_id)
{
	t_paths			*curr_node;
	t_paths			*tmp_next;

	curr_node = ant_farm->paths;
	while (curr_node->next != NULL)
	{
		// prev_node = curr_node;
		if (curr_node->path_id == path_id)
			break ;
		curr_node = curr_node->next;
	}
	// ft_printf(" freeing path id  %d\n", curr_node->path_id);
	ft_free_pathlst(curr_node->path_lst);
	// ft_printf(" prev path id  %d\n", prev_node->path_id);
	// prev_node->next = NULL;
	tmp_next = curr_node->next;
	if (curr_node->prev != NULL)
		curr_node->prev->next = tmp_next;
	else
		ant_farm->paths = tmp_next;
	if (tmp_next != NULL)
		tmp_next->prev = curr_node->prev;
	// curr_node->prev->next = NULL;
	// curr_node->path_id = 0;
	// curr_node = NULL;
	// ft_printf(" curr node %p\n", curr_node);
	free(curr_node);
}

void				ft_free_paths_ants_lst(t_ant_farm *ant_farm)
{
	t_paths			*curr_node;
	// t_paths			*next_node;

	curr_node = ant_farm->paths;
	while (curr_node != NULL)
	{
		// ft_printf(" .freeing from path id %d the ants list\n", curr_node->path_id);
		ft_free_ants_lst(&(curr_node->ants_lst));
		curr_node->ants_amount = 0;
		// ft_printf(" .freeing from path id %d the paths list\n", curr_node->path_id);
		// ft_free_pathlst(curr_node->path_lst);
		// ft_printf(" freeing path id  %d\n", curr_node->path_id);
		// curr_node->path_id = 0;
		curr_node = curr_node->next;
		// curr_node = NULL;
		// free(curr_node);
		// curr_node = next_node;
	}
	// ant_farm->paths = NULL;
}
