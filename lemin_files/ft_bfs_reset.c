/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bfs_reset.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/21 13:12:57 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/21 13:21:28 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** This function checks which rooms have state different to COMPLETED
** and sets them to state UNEXPLORED
*/

void				ft_bfs_reset(t_ant_farm *ant_farm)
{
	t_room			*temp;

	temp = ant_farm->rooms_lst;
	while (temp != NULL)
	{
		if (temp->state != COMPLETED)
			temp->state = UNEXPLORED;
		temp = temp->next;
	}
}

/*
** This function sets the state of all rooms of the graph
** to state UNEXPLORED
*/

void				ft_bfs_fullreset(t_ant_farm *ant_farm)
{
	t_room			*temp;

	temp = ant_farm->rooms_lst;
	while (temp != NULL)
	{
		temp->state = UNEXPLORED;
		temp = temp->next;
	}
}

/*
** Deletes the path_list given.
** Before freeing I set the score of the corresponding rooms to 0
** because they don't belong anymore to a path.
** This is helpful when augmenting the graph.
*/

static void			ft_reset_score_pathlst(t_path_list *path_lst)
{
	t_path_list		*curr_node;
	// t_path_list		*next_node;

	curr_node = path_lst;
	while (curr_node != NULL)
	{
		curr_node->room->score = 0;
		// ft_printf(" room name %s - score %d\n", curr_node->room->name, curr_node->room->score);
		curr_node = curr_node->next;
	}
	// ft_printf(" RESET DONE \n");
	// path_lst = NULL;
}

/*
** Deletes the path from the linked list of paths (ant_farm->paths)
** based on the path_id given.
*/

void				ft_reset_score_on_pathid(t_ant_farm *ant_farm, int path_id)
{
	t_paths			*curr_node;

	curr_node = ant_farm->paths;
	while (curr_node->next != NULL)
	{
		// prev_node = curr_node;
		if (curr_node->path_id == path_id)
			break ;
		curr_node = curr_node->next;
	}
	// ft_printf(" reseting score in path id %d of run %d\n", curr_node->path_id, curr_node->run);
	ft_reset_score_pathlst(curr_node->path_lst);
}
