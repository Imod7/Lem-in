/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_rooms.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/28 10:48:46 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/07 17:36:07 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void			ft_print_header(void)
{
	ft_printf("\n                      Rooms (Linked List)                \n");
	ft_printf("-------------------------------------------------------------");
	ft_printf("------------------------------------------------------------\n");
	ft_printf("|room_name\tx_coord\ty_coord\tpos\tstate\tlvl_source\t");
	ft_printf("lvl_sink\tscore\tpath_id\tparent_room\tnext_room|\n");
}

static void			ft_print_footer(void)
{
	ft_printf("-------------------------------------------------------------");
	ft_printf("------------------------------------------------------------\n");
}

void				ft_print_rooms_list(t_room *rooms_lst)
{
	t_room			*temp;

	temp = rooms_lst;
	ft_print_header();
	while (temp != NULL)
	{
		ft_printf("|%s\t\t%d\t%d", temp->name, temp->x_coord, temp->y_coord);
		ft_printf("\t%d\t%d\t", temp->position, temp->state);
		ft_printf("%d\t\t%d\t", temp->level_source, temp->level_sink);
		ft_printf("\t%d\t", temp->score);
		if (temp->path != NULL)
			ft_printf("%d\t", temp->path->path_id);
		else
			ft_printf("0\t");
		if (temp->parent != NULL)
			ft_printf("%s\t\t", temp->parent->name);
		else
			ft_printf("NULL\t\t");
		if (temp->next != NULL)
			ft_printf("%s\t|\n", temp->next->name);
		else
			ft_printf("NULL\t|\n");
		temp = temp->next;
	}
	ft_print_footer();
}
