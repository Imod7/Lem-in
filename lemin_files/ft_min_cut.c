/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_min_cut.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/13 08:23:30 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/29 15:20:19 by dsaripap      ########   odam.nl         */
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

	// ft_printf(" B.3 In DELETE neighbor : bottleneck room %s\n", btl_room);
	// ft_printf("  Previous Room %s \n", temp_item->room_name);
	neigbors_lst = temp_item->room->neighbors;
	// ft_printf(" delete it first from the neightbors list of %s \n", temp_item->room->neighbors->hash_item->room->name);
	while (neigbors_lst != NULL)
	{
		// ft_printf("  neighbor %s \n", neigbors_lst->hash_item->room_name);
		if (ft_strcmp(btl_room, neigbors_lst->hash_item->room_name) == 0) 
		// if (temp_item->room_name == neigbors_lst->hash_item->room_name)
		{
			// ft_printf("  Deleting neighbor %s \n", neigbors_lst->hash_item->room_name);
			temp = neigbors_lst->next;
			// if (temp != NULL)
			// 	ft_printf("  next %s \n", temp->hash_item->room->name);
			if (neigbors_lst->prev != NULL)
				neigbors_lst->prev->next = temp;
			else
			{
				temp_item->room->neighbors = temp;
				// ft_printf("  prev is NULL %s \n", 
				// temp_item->room->neighbors->hash_item->room->name);
			}
			if ((temp != NULL) && (neigbors_lst != NULL))
				temp->prev = neigbors_lst->prev;
			else if ((temp != NULL) && (neigbors_lst == NULL))
				temp->prev = NULL;
			free(neigbors_lst);
			neigbors_lst = temp;
			// if (neigbors_lst != NULL)
			// 	ft_printf("  so now i continue from %s \n", 
			// 	neigbors_lst->hash_item->room_name);
		}
		if (neigbors_lst != NULL)
			neigbors_lst = neigbors_lst->next;
	}
	// ft_printf(" so now head is %s \n", temp_item->room->neighbors->hash_item->room->neighbors->hash_item->room->name);
	// ft_printf(" so now next of head is %s \n", temp_item->room->neighbors->hash_item->room->neighbors->next->hash_item->room->name);
	// ft_printf(" so now prev of head is %p \n", temp_item->room->neighbors->hash_item->room->neighbors->prev);
	// ft_printf(" so now next of next is %p \n", temp_item->room->neighbors->hash_item->room->neighbors->next->next);
	// ft_printf(" so now prev of next is %s \n", temp_item->room->neighbors->hash_item->room->neighbors->next->prev->hash_item->room->name);
}

/*
** In function cut_edge iterate through the path_list of the bottleneck path,
** finds the bottleneck room and get the previous one.
** I call function delete_edge_from_item to remove the bottleneck room
** from the neighbors of previous room.
*/

static void				ft_min_cut(t_ant_farm *ant_farm, \
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
			// ft_printf(" B.2 In MIN CUT : bottleneck room %s\n", bottleneck_room->name);
			room_item = ft_retrieve_hash_item(ant_farm->hash_table, \
			tmp_pathlst->prev->room->name);
			prev_room = tmp_pathlst->prev->room;
			// ft_printf("from room %s to del bottleneck %s\n", room_item->room_name, bottleneck_room->name);
			ft_delete_neighbor(room_item, bottleneck_room->name);
			room_item = ft_retrieve_hash_item(ant_farm->hash_table, \
			tmp_pathlst->room->name);
			// ft_printf("from room %s to del %s\n", room_item->room_name, prev_room->name);
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

static void				find_path_of_bottleneck_room(t_ant_farm *ant_farm, \
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
	// ft_printf(" B.4 Reset score in path %d of run %d\n", tmp_path->path_id, tmp_path->run);
	ft_reset_score_on_pathid(ant_farm, tmp_path->path_id);
	// return (tmp_path->path_id);
}

/*
** In function ft_check_cut_edge I will add the neighbor if
** it is unexplored  AND (lvl_source bigger or lvl_sink smaller).
** If I couldn't add any neighbors I call function ft_check_cut_edge
*/

size_t				ft_check_min_cut(t_ant_farm *ant_farm, \
									t_neighbor *neighbors, t_room *temp, \
									size_t current_run)
{
	size_t			flag;
	t_neighbor		*neighb_tmp;

	(void)temp;
	neighb_tmp = neighbors;
	flag = 0;
	ft_printf(ANSI_COLOR_SAND"\n~~~~~~~~~~ MIN CUT FUNCTION ~~~~~~~~~~ \n");
	ft_printf(" From Room %s cant move , lvl_source %d, lvl_sink %d\n", temp->name, temp->level_source, temp->level_sink);
	// ft_printf(" Neighbors of Front Room %s , level_source %d, lvl_sink %d\n", temp->name, temp->level_source, temp->level_sink);
	while (neighb_tmp != NULL)
	{
		ft_printf("    neighb %s ", neighb_tmp->hash_item->room->name);
		ft_printf("    state %d ", neighb_tmp->hash_item->room->state);
		ft_printf("    level_source %d, ", neighb_tmp->hash_item->room->level_source);
		ft_printf("    level_sink %d, ", neighb_tmp->hash_item->room->level_sink);
		ft_printf("    score %d ", neighb_tmp->hash_item->room->score);
		ft_printf("    run %d ", neighb_tmp->hash_item->room->run);
		if (neighb_tmp->hash_item->room->state == UNEXPLORED && \
		neighb_tmp->hash_item->room->score != 0 && \
		neighb_tmp->hash_item->room->run != current_run && \
		neighb_tmp->hash_item->room->level_sink != 0)
		// neighb_tmp->hash_item->room->level_sink != 0)
		{
			// ft_print_paths(ant_farm);
			// print_neighbors_list(ant_farm->hash_table);
			// ft_printf("neighbor pushed %s \n", neighb_tmp->hash_item->room->name);
			ft_enqueue(ant_farm->queue, neighb_tmp->hash_item->room);
			neighb_tmp->hash_item->room->parent = ant_farm->queue->front->room;
			neighb_tmp->hash_item->room->parent->run = current_run;
			// ft_printf("parent of room %s is %s\n", neighb_tmp->hash_item->room->name, neighb_tmp->hash_item->room->parent->name);
			ft_printf(" -> MINCUT - Enqueued %s\n", neighb_tmp->hash_item->room->name);
			// ft_push(&(ant_farm->stack), neighb_tmp->hash_item->room);
			find_path_of_bottleneck_room(ant_farm, neighb_tmp->hash_item->room);
			// ft_printf(" \n room name %s path_id %d\n",neighb_tmp->hash_item->room->name, temp->path->path_id);
			// temp->path->path_id = path_id;
			// ft_print_paths(ant_farm);
			// ft_print_stack(ant_farm->stack);
			// print_neighbors_list(ant_farm->hash_table);
			flag += 1;
			// ft_printf(" \n  AFTER THE CUT\n");
			break ;
		}
		else
			ft_printf("\n");
		neighb_tmp = neighb_tmp->next;
	}
	// ft_printf(ANSI_COLOR_RESET);
	// ft_printf("~~~~~~~~~~ MIN CUT DONE flag = %d ~~~~~~~~~~\n", flag);
	return (flag);
}
