/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ants_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 09:58:56 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 09:53:45 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** Function that chooses the next ant assigned in the given path
** It returns it to the function push_ant_to_next_room and there it moves
** it all along the path.
*/

int					choose_ant(t_paths *path, int ant_id)
{
	t_ants			*ant_lst;

	ant_lst = path->ants_lst;
	while (ant_lst != NULL)
	{
		if ((ant_lst->next != NULL) && (ant_id == ant_lst->ant_id))
			return (ant_lst->next->ant_id);
		ant_lst = ant_lst->next;
	}
	return (0);
}

/*
** Function that adds the ant to the ants_list given as parameters.
** This function is used either to add in the room's ants_list
** either to the path's ants_list. It depends on the arguments that
** are given when the function is called.
*/

void				ft_add_ant_to_antslist(t_ants **lst, t_ants *new)
{
	t_ants			*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

/*
** Function that mallocs an ant and assigns it to the given room
*/

int					add_ant_to_room(t_paths *path, t_room *room, int ant_id)
{
	t_ants			*ant;

	ant = (t_ants *)ft_memalloc(sizeof(t_ants));
	if (ant == NULL)
		return (ERROR);
	ant->ant_id = ant_id;
	ant->path = path;
	ft_add_ant_to_antslist(&(room->ants_lst), ant);
	return (SUCCESS);
}
