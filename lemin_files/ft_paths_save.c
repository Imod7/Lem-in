/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_paths_save.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/07 08:05:25 by dominique     #+#    #+#                 */
/*   Updated: 2020/05/21 07:31:38 by dominique     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_room				*ft_get_end_room(t_ant_farm *ant_farm)
{
	t_room			*temp;

	temp = ant_farm->rooms_lst;
	while (temp != NULL)
	{
		if (temp->position == END)
			break ;
		temp = temp->next;
	}
	return (temp);
}

void				ft_save_paths_bfs(t_ant_farm *ant_farm)
{
	t_room			*temp;
	t_path_list		*path;
	t_path_list		*prev_pathlst;
	t_paths			*total_paths;

	temp = ft_get_end_room(ant_farm);
	total_paths = ant_farm->paths;
	prev_pathlst = NULL;
	while (total_paths != NULL)
		total_paths = total_paths->next;
	total_paths = (t_paths *)ft_memalloc(sizeof(t_paths));
	ft_path_addend(&(ant_farm->paths), total_paths);
	if ((total_paths != NULL) && (total_paths->prev != NULL))
	{
		prev_pathlst = total_paths->prev->path_lst;
		while (prev_pathlst->next != NULL)
		{
			// ft_printf("room %s \n", prev_pathlst->room->name);
			prev_pathlst = prev_pathlst->next;
		}
		// ft_printf("prev room %s\n", prev_pathlst->prev->room->name);
	}
	path = (t_path_list *)ft_memalloc(sizeof(t_path_list));
	path->room = temp;
	// ft_printf("temp parent %s\n", temp->parent->name);
	// ft_printf("Saving path %d \n", total_paths->path_id);
	if (((prev_pathlst != NULL) && \
	(ft_strcmp(prev_pathlst->prev->room->name, temp->parent->name) != 0)) || \
	(prev_pathlst == NULL))
	{
		ft_pathlst_addstart(&(total_paths->path_lst), path);
		path = path->next;
		while (temp->parent != NULL)
		{
			// ft_printf("parent of %s is %s \n", temp->name, temp->parent->name);
			temp = temp->parent;
			temp->state = COMPLETED;
			temp->score = total_paths->path_id;
			path = (t_path_list *)ft_memalloc(sizeof(t_path_list));
			path->room = temp;
			path->room->path = total_paths;
			ft_pathlst_addstart(&(total_paths->path_lst), path);
			path = path->next;
		}
	}
	else
	{
		// ft_printf("free \n");
		ft_path_del_last(ant_farm);
	}
}

t_paths				*ft_create_path_list(t_ant_farm *ant_farm)
{
	t_paths			*paths;

	paths = ant_farm->paths;
	while (paths != NULL)
		paths = paths->next;
	paths = (t_paths *)ft_memalloc(sizeof(t_paths));
	ft_path_addend(&(ant_farm->paths), paths);
	return (paths);
}

/*
** In DFS we save each room as we go but when a room
** has a parent room that is the same as the parent of
** the previous room in the path then we free the previous
** room in the path
*/

void				ft_save_paths_dfs(t_path_list **path_lst, t_room *room)
{
	t_path_list		*path;
	t_path_list		*last_node;
	t_path_list		*prevlast_node;

	last_node = *path_lst;
	prevlast_node = *path_lst;
	// ft_printf("Saving room %s to path \n", room->name);
	while (last_node != NULL)
	{
		prevlast_node = last_node;
		// ft_printf("prev room  %s \n", prevlast_node->room->name);
		last_node = last_node->next;
	}
	// if (prevlast_node != NULL)
	// {
	// 	if ((prevlast_node->room->parent != NULL) && (room->parent != NULL))
	// 		ft_printf("comparing parent of '%s' is '%s' and of room '%s' is '%s'\n", prevlast_node->room->name, prevlast_node->room->parent->name, room->name, room->parent->name);
	// 	ft_printf("comparing levels %s %d - %s %d \n", prevlast_node->room->name, prevlast_node->room->level, room->name, room->level);
	// }
	// if ((prevlast_node != NULL) && (prevlast_node->room->level == room->level))
	// (ft_strcmp(prevlast_node->room->parent->name, room->parent->name) == 0))
	// {
	// 	prevlast_node->prev->next = NULL;
	// 	free(prevlast_node);
	// }
	path = (t_path_list *)ft_memalloc(sizeof(t_path_list));
	path->room = room;
	if (prevlast_node != NULL)
		path->room->parent = prevlast_node->room;
	else
		path->room->parent = NULL;
	ft_pathlst_addend(path_lst, path);
}