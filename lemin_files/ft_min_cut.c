/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_min_cut.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/13 08:23:30 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/07/17 15:13:37 by dsaripap      ########   odam.nl         */
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

void				ft_min_cut(t_ant_farm *ant_farm, \
								t_paths *tmp_path, \
								t_room *bottleneck_room)
{
	t_path_list		*tmp_pathlst;
	t_hash_item		*room_item;

	tmp_pathlst = tmp_path->path_lst;
	while (tmp_pathlst != NULL)
	{
		if (tmp_pathlst->room->name == bottleneck_room->name)
		{
			// ft_printf(" B.2 In MIN CUT : bottleneck room %s\n", bottleneck_room->name);
			room_item = ft_retrieve_hash_item(ant_farm->hash_table, \
			tmp_pathlst->next->room->name);
			ft_delete_neighbor(room_item, bottleneck_room->name);
		}
		tmp_pathlst = tmp_pathlst->next;
	}
}

/*
** In function find_path_cut_edge finds the path_id of the path that the
** bottleneck room belongs to, passes this path to the ft_cut_edge
** function to remove the neighbor and then free this path
*/

int					find_path_of_bottleneck_room(t_ant_farm *ant_farm, \
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
	// ft_printf(" B.4 Free path %d of run %d\n", tmp_path->path_id, tmp_path->run);
	ft_free_path_on_pathid(ant_farm, tmp_path->path_id);
	return (tmp_path->path_id);
}

/*
** In function ft_check_cut_edge I will add the neighbor if
** it is unexplored  AND (lvl_source bigger or lvl_sink smaller).
** If I couldn't add any neighbors I call function ft_check_cut_edge
*/

size_t				ft_check_min_cut(t_ant_farm *ant_farm, \
									t_neighbor *neighbors, t_room *temp)
{
	size_t			flag;
	t_neighbor		*neighb_tmp;
	int				path_id;

	(void)temp;
	neighb_tmp = neighbors;
	flag = 0;
	// ft_printf(ANSI_COLOR_SAND" \n  ~~~~~~~~~~ CUT FUNCTION ~~~~~~~~~~ \n");
	// ft_printf(" \nB.1 Blocked in prev room of %s\n", temp->name);
	// ft_printf("  From Room %s cant move , lvl_source %d, lvl_sink %d\n", temp->name, temp->level_source, temp->level_sink);
	// ft_printf(" Neighbors of Front Room %s , level_source %d, lvl_sink %d\n", temp->name, temp->level_source, temp->level_sink);
	while (neighb_tmp != NULL)
	{
		// ft_printf("    neighb %s ", neighb_tmp->hash_item->room->name);
		// ft_printf("    state %d ", neighb_tmp->hash_item->room->state);
		// ft_printf("    level_source %d, ", neighb_tmp->hash_item->room->level_source);
		// ft_printf("    level_sink %d, ", neighb_tmp->hash_item->room->level_sink);
		// ft_printf("    score %d \n", neighb_tmp->hash_item->room->score);
		// if (neighb_tmp->hash_item->room->state == UNEXPLORED && 
		// (temp->level_source >= neighb_tmp->hash_item->room->level_source && 
		// temp->level_sink <= neighb_tmp->hash_item->room->level_sink) && 
		// neighb_tmp->hash_item->room->score != 0 &&
		// neighb_tmp->hash_item->room->position != START)
		if (neighb_tmp->hash_item->room->state == UNEXPLORED && \
		neighb_tmp->hash_item->room->score != 0)
		{
			// ft_printf(" \n  CUTTING EDGE\n");
			// ft_print_paths(ant_farm);
			// print_neighbors_list(ant_farm->hash_table);
			// ft_printf("neighbor pushed %s \n", neighb_tmp->hash_item->room->name);
			ft_enqueue(ant_farm->queue, neighb_tmp->hash_item->room);
			neighb_tmp->hash_item->room->parent = ant_farm->queue->front->room;
			// ft_printf("parent of room %s is %s\n", neighb_tmp->hash_item->room->name, neighb_tmp->hash_item->room->parent->name);
			// ft_printf(" \nB.1 Enqueued %s\n", neighb_tmp->hash_item->room->name);
			// ft_push(&(ant_farm->stack), neighb_tmp->hash_item->room);
			path_id = find_path_of_bottleneck_room(ant_farm, neighb_tmp->hash_item->room);
			// ft_printf(" \n room name %s path_id %d\n",neighb_tmp->hash_item->room->name, temp->path->path_id);
			// temp->path->path_id = path_id;
			// ft_printf(" \n  AFTER THE CUT\n");
			// ft_print_paths(ant_farm);
			// ft_print_stack(ant_farm->stack);
			// print_neighbors_list(ant_farm->hash_table);
			flag += 1;
		}
		neighb_tmp = neighb_tmp->next;
	}
	// ft_printf(ANSI_COLOR_RESET);
	return (flag);
}
