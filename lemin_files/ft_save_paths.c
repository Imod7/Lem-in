/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_save_paths.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:38:35 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/29 20:39:18 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** Retracing all the path by following all the parent rooms 
*/

static void			ft_retrace_path(t_room *temp, size_t flag, \
									t_paths *new_path)
{
	t_path_list		*path_list;

	while (temp->parent != NULL)
	{
		// ft_printf("parent of %s is %s \n", temp->name, temp->parent->name);
		temp = temp->parent;
		temp->state = COMPLETED;
		temp->score = new_path->path_id;
		path_list = (t_path_list *)ft_memalloc(sizeof(t_path_list));
		path_list->room = temp;
		// ft_printf(" ++ save room %s \n", path_list->room->name);
		path_list->room->path = new_path;
		// ft_pathlst_addstart(&(new_path->path_lst), path_list);
		if (flag == 0)
			ft_pathlst_addend(&(new_path->path_lst), path_list);
		else
			ft_pathlst_addstart(&(new_path->path_lst), path_list);
		// ft_print_paths(ant_farm);
		new_path->path_size += 1;
			// path_list = path_list->next;
	}
}

/*
** In BFS we save the path after we arrive at the sink.
** We will start at the sink/end room and we will go backwards
** by checking the parent room each time and save the corresponding
** parent room to the path
** CAUTION : check if flag is still necessary to keep
** otherwise DELETE
*/

void				ft_save_paths_bfs(t_ant_farm *ant_farm, size_t flag, \
									size_t run)
{
	t_room			*temp;
	t_path_list		*path_list;
	t_path_list		*prev_pathlst;
	t_paths			*new_path;

	// (void)flag;
	if (flag == 0)
		temp = ft_get_start_room(ant_farm->rooms_lst);
	else
		temp = ft_get_end_room(ant_farm);
	// temp = ft_get_end_room(ant_farm);
	prev_pathlst = NULL;
	// while (total_paths != NULL)
	// 	total_paths = total_paths->next;
	new_path = (t_paths *)ft_memalloc(sizeof(t_paths));
	new_path->run = run;
	ft_path_addend(&(ant_farm->paths), new_path);
	// ft_printf("\n Saving the path %d \n", new_path->path_id);
	// ft_print_paths(ant_farm);
	if ((new_path != NULL) && (new_path->prev != NULL))
	{
		prev_pathlst = new_path->prev->path_lst;
		while (prev_pathlst->next != NULL)
		{
			// ft_printf(" ** room %s \n", prev_pathlst->room->name);
			prev_pathlst = prev_pathlst->next;
		}
		// ft_printf("prev room %s\n", prev_pathlst->prev->room->name);
	}
	// if (prev_pathlst != NULL) 
	// 	ft_printf("prev_pathlst->room->name %s\n", prev_pathlst->prev->room->name);
	// else
	// 	ft_printf("prev_path NULL\n");
	// ft_print_paths(ant_farm);
	// ft_printf("Saving path %d \n", new_path->path_id);
	// ft_printf("...parent of end %s \n", temp->parent->name);
	// if (((prev_pathlst != NULL) && \
	// (ft_strcmp(prev_pathlst->prev->room->name, temp->parent->name) != 0)) || \
	// (prev_pathlst == NULL))
	// {
	path_list = (t_path_list *)ft_memalloc(sizeof(t_path_list));
	path_list->room = temp;
	// ft_printf("path lst room %s\n", path_list->room->name);
	// ft_printf(" --> add room %s to path \n", path_list->room->name);
	// if (flag == 0)
	ft_pathlst_addstart(&(new_path->path_lst), path_list);
	// else
	// 	ft_pathlst_addend(&(new_path->path_lst), path_list);
	// ft_print_paths(ant_farm);
	new_path->path_size += 1;
	// path_list = path_list->next;
	ft_retrace_path(temp, flag, new_path);
	// while (temp->parent != NULL)
	// {
	// 	// ft_printf("parent of %s is %s \n", temp->name, temp->parent->name);
	// 	temp = temp->parent;
	// 	temp->state = COMPLETED;
	// 	temp->score = new_path->path_id;
	// 	path_list = (t_path_list *)ft_memalloc(sizeof(t_path_list));
	// 	path_list->room = temp;
	// 	// ft_printf(" ++ save room %s \n", path_list->room->name);
	// 	path_list->room->path = new_path;
	// 	// ft_pathlst_addstart(&(new_path->path_lst), path_list);
	// 	if (flag == 0)
	// 		ft_pathlst_addend(&(new_path->path_lst), path_list);
	// 	else
	// 		ft_pathlst_addstart(&(new_path->path_lst), path_list);
	// 	// ft_print_paths(ant_farm);
	// 	new_path->path_size += 1;
	// 		// path_list = path_list->next;
	// }
	// else
	// {
	// 	ft_printf("free last one %s %s %p\n", prev_pathlst->prev->room->name, temp->parent->name, prev_pathlst);
	// 	// free(path_list);
	// 	ft_path_del_last(ant_farm);
	// 	// ft_print_paths(ant_farm);
	// }
}

t_paths				*ft_create_path(t_ant_farm *ant_farm)
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
** In DFS we save each room as we go
** the rest for now commented
** when a room
** has a parent room that is the same as the parent of
** the previous room in the path then we free the previous
** room in the path
*/

void				ft_save_room_to_dfs_path(t_path_list **path_lst, \
											t_room *room)
{
	t_path_list		*path;
	t_path_list		*last_node;
	t_path_list		*prevlast_node;

	last_node = *path_lst;
	prevlast_node = *path_lst;
	// ft_printf("Saving room %s to path\n", room->name);
	while (last_node != NULL)
	{
		prevlast_node = last_node;
		// ft_printf("prev room  %s \n", prevlast_node->room->name);
		last_node = last_node->next;
	}
	path = (t_path_list *)ft_memalloc(sizeof(t_path_list));
	path->room = room;
	if (prevlast_node != NULL)
		path->room->parent = prevlast_node->room;
	else
		path->room->parent = NULL;
	ft_pathlst_addend(path_lst, path);
}
