/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_min_cut.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/13 08:23:30 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 14:10:07 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** In function delete_edge_from_item we iterate through all the neighbors
** (the neighbor_list) of the previous room from the bottleneck,
** we find the bottleneck room and we remove it.
*/

static void			ft_delete_neighbor(t_hash_item *temp_item, char *btl_room)
{
	t_neighbor		*neigbors_lst;
	t_neighbor		*temp;

	neigbors_lst = temp_item->room->neighbors;
	while (neigbors_lst != NULL)
	{
		if (ft_strcmp(btl_room, neigbors_lst->hash_item->room_name) == 0)
		{
			temp = neigbors_lst->next;
			if (neigbors_lst->prev != NULL)
				neigbors_lst->prev->next = temp;
			else
			{
				temp_item->room->neighbors = temp;
			}
			if ((temp != NULL) && (neigbors_lst != NULL))
				temp->prev = neigbors_lst->prev;
			else if ((temp != NULL) && (neigbors_lst == NULL))
				temp->prev = NULL;
			free(neigbors_lst);
			neigbors_lst = temp;
		}
		if (neigbors_lst != NULL)
			neigbors_lst = neigbors_lst->next;
	}
}

/*
** In function cut_edge iterate through the path_list of the bottleneck path,
** finds the bottleneck room and get the previous one.
** I call function delete_edge_from_item to remove the bottleneck room
** from the neighbors of previous room.
*/

static void			ft_min_cut(t_ant_farm *ant_farm, \
								t_paths *tmp_path, \
								t_room *bottleneck_room)
{
	t_path_list		*tmp_pathlst;
	t_hash_item		*room_item;
	t_room			*prev_room;

	tmp_pathlst = tmp_path->path_lst;
	while (tmp_pathlst != NULL)
	{
		if (tmp_pathlst->room->name == bottleneck_room->name)
		{
			room_item = ft_retrieve_hash_item(ant_farm->hash_table, \
			tmp_pathlst->prev->room->name);
			prev_room = tmp_pathlst->prev->room;
			ft_delete_neighbor(room_item, bottleneck_room->name);
			room_item = ft_retrieve_hash_item(ant_farm->hash_table, \
			tmp_pathlst->room->name);
			ft_delete_neighbor(room_item, prev_room->name);
		}
		tmp_pathlst = tmp_pathlst->next;
	}
}

/*
** In function find_path_cut_edge finds the path_id of the path that the
** bottleneck room belongs to, passes this path to the ft_cut_edge
** function to remove the neighbor and then free this path
*/

static void			find_path_of_bottleneck_room(t_ant_farm *ant_farm, \
							t_room *bottleneck_room)
{
	t_paths			*tmp_path;

	tmp_path = ant_farm->paths;
	while (tmp_path != NULL)
	{
		if (tmp_path->path_id == bottleneck_room->score)
			break ;
		tmp_path = tmp_path->next;
	}
	ft_min_cut(ant_farm, tmp_path, bottleneck_room);
	ft_reset_score_on_pathid(ant_farm, tmp_path->path_id);
}

/*
** In function ft_check_cut_edge I will add the neighbor if
** it is unexplored  AND (lvl_source bigger or lvl_sink smaller).
** If I couldn't add any neighbors I call function ft_check_cut_edge
*/

size_t				ft_check_min_cut(t_ant_farm *ant_farm, \
									t_neighbor *neighbors, size_t current_run)
{
	size_t			flag;
	t_neighbor		*neighb_tmp;

	neighb_tmp = neighbors;
	flag = 0;
	while (neighb_tmp != NULL)
	{
		if (neighb_tmp->hash_item->room->state == UNEXPLORED && \
		neighb_tmp->hash_item->room->score != 0 && \
		neighb_tmp->hash_item->room->run != current_run && \
		neighb_tmp->hash_item->room->level_sink != 0)
		{
			ft_enqueue(ant_farm->queue, neighb_tmp->hash_item->room);
			neighb_tmp->hash_item->room->parent = ant_farm->queue->front->room;
			neighb_tmp->hash_item->room->parent->run = current_run;
			find_path_of_bottleneck_room(ant_farm, neighb_tmp->hash_item->room);
			flag += 1;
			break ;
		}
		neighb_tmp = neighb_tmp->next;
	}
	return (flag);
}
