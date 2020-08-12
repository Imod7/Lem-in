/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_paths.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:38:25 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 13:57:02 by svan-der      ########   odam.nl         */
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
		ft_free_ants_lst(&(curr_node->ants_lst));
		ft_free_pathlst(curr_node->path_lst);
		next_node = curr_node->next;
		free(curr_node);
		curr_node = next_node;
	}
	ant_farm->paths = NULL;
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
		if (curr_node->path_id == path_id)
			break ;
		curr_node = curr_node->next;
	}
	ft_free_pathlst(curr_node->path_lst);
	tmp_next = curr_node->next;
	if (curr_node->prev != NULL)
		curr_node->prev->next = tmp_next;
	else
		ant_farm->paths = tmp_next;
	if (tmp_next != NULL)
		tmp_next->prev = curr_node->prev;
	free(curr_node);
}

/*
** Function that frees/deletes the ants_list of the given path
** and sets ants_amount of this path to 0
*/

void				ft_free_paths_ants_lst(t_ant_farm *ant_farm)
{
	t_paths			*curr_node;

	curr_node = ant_farm->paths;
	while (curr_node != NULL)
	{
		ft_free_ants_lst(&(curr_node->ants_lst));
		curr_node->ants_amount = 0;
		curr_node = curr_node->next;
	}
}

/*
** Function that frees/deletes the mallocked t_lines struct
** where we save just the number of lines of every path in a
** doubly linked list.
*/

void				ft_free_path_lines(t_lines *lines_head)
{
	t_lines			*tmp;

	while (lines_head != NULL)
	{
		tmp = lines_head;
		lines_head = lines_head->next;
		free(tmp);
	}
}
