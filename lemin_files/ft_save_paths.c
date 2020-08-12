/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_save_paths.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:38:35 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 14:40:31 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** Retracing all the path by following all the parent rooms
*/

static int			ft_retrace_path(t_room *temp, size_t flag, \
									t_paths *new_path)
{
	t_path_list		*path_list;

	while (temp->parent != NULL)
	{
		temp = temp->parent;
		temp->state = COMPLETED;
		temp->score = new_path->path_id;
		path_list = (t_path_list *)ft_memalloc(sizeof(t_path_list));
		if (path_list == NULL)
			return (ERROR);
		path_list->room = temp;
		path_list->room->path = new_path;
		if (flag == 0)
			ft_pathlst_addend(&(new_path->path_lst), path_list);
		else
			ft_pathlst_addstart(&(new_path->path_lst), path_list);
		new_path->path_size += 1;
	}
	return (SUCCESS);
}

static int			ft_setup_paths_bfs(t_paths *new_path, size_t flag, \
									t_room *temp)
{
	t_path_list		*path_list;

	path_list = (t_path_list *)ft_memalloc(sizeof(t_path_list));
	if (path_list == NULL)
		return (ERROR);
	path_list->room = temp;
	ft_pathlst_addstart(&(new_path->path_lst), path_list);
	new_path->path_size += 1;
	ft_retrace_path(temp, flag, new_path);
	return (SUCCESS);
}

/*
** In BFS we save the path after we arrive at the sink.
** We will start at the sink/end room and we will go backwards
** by checking the parent room each time and save the corresponding
** parent room to the path
** CAUTION : check if flag is still necessary to keep
** otherwise DELETE
*/

int					ft_save_paths_bfs(t_ant_farm *ant_farm, size_t flag, \
									size_t run)
{
	t_room			*temp;
	t_path_list		*prev_pathlst;
	t_paths			*new_path;

	if (flag == 0)
		temp = ft_get_start_room(ant_farm->rooms_lst);
	else
		temp = ft_get_end_room(ant_farm);
	prev_pathlst = NULL;
	new_path = (t_paths *)ft_memalloc(sizeof(t_paths));
	if (new_path == NULL)
		return (ERROR);
	new_path->run = run;
	ft_path_addend(&(ant_farm->paths), new_path);
	if ((new_path != NULL) && (new_path->prev != NULL))
	{
		prev_pathlst = new_path->prev->path_lst;
		while (prev_pathlst->next != NULL)
			prev_pathlst = prev_pathlst->next;
	}
	if (ft_setup_paths_bfs(new_path, flag, temp) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
