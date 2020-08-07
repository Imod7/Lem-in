/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_check_dup_rooms.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/07 16:25:34 by svan-der      #+#    #+#                 */
/*   Updated: 2020/08/07 16:30:39 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int		check_dup_room_name(t_room **rooms_lst)
{
	t_room *fast;
	t_room *slow;

	fast = *rooms_lst;
	slow = *rooms_lst;
	while (slow && slow->next)
	{
		while (fast->next != NULL)
		{
			if (ft_strequ(slow->name, fast->next->name))
			{
				// ft_printf("Duplicate room name:%s\n", slow->name);
				return (ERROR);
			}
			else
				fast = fast->next;
		}
		slow = slow->next;
		fast = slow;
	}
	return (1);
}

static int		check_dup_y_coord(t_room **rooms_lst)
{
	t_room *fast;
	t_room *slow;

	fast = *rooms_lst;
	slow = *rooms_lst;
	while (slow && slow->next)
	{
		// ft_printf("slow_y:%i\t fast_y:%i\n", slow->y_coord, fast->next->y_coord);
		while (fast->next != NULL)
		{
			if (slow->y_coord == fast->next->y_coord \
			&& slow->x_coord == fast->next->x_coord)
			{
				// ft_printf("DUPLICATE Y_COORD\n");
				// ft_printf("Duplicate slow y_coord:%i fast y_coord:%i room:%s\n", slow->y_coord, fast->next->y_coord, slow->name);
				return (ERROR);
			}
			else
				fast = fast->next;
		}
		slow = slow->next;
		fast = slow;
	}
	return (1);
}

static int		check_dup_x_coord(t_room **rooms_lst)
{
	t_room *fast;
	t_room *slow;

	fast = *rooms_lst;
	slow = *rooms_lst;
	while (slow && slow->next)
	{
		// ft_printf("slow_x:%i\t fast_x:%i\n", slow->x_coord, fast->next->x_coord);
		while (fast->next != NULL)
		{
			if (slow->x_coord == fast->next->x_coord \
			&& slow->y_coord == fast->next->y_coord)
			{
				// ft_printf("DUPLICATE X_COORD\n");
				// ft_printf("Duplicate slow x_coord:%i fast x_coord:%i room:%s\n", slow->x_coord, fast->next->x_coord, slow->name);
				return (ERROR);
			}
			else
				fast = fast->next;
		}
		slow = slow->next;
		fast = slow;
	}
	return (1);
}

int				check_dup_rooms_lst(t_room **rooms_lst)
{
	int x_ret;
	int	y_ret;
	int name_ret;

	if (rooms_lst == NULL)
		return (ERROR);
	x_ret = check_dup_x_coord(rooms_lst);
	y_ret = check_dup_y_coord(rooms_lst);
	name_ret = check_dup_room_name(rooms_lst);
	// ft_printf("x_ret:%i\ty_ret:%i\tname__ret:%i\n", x_ret, y_ret, name_ret);
	if (x_ret != 1 || y_ret != 1 || name_ret != 1)
		return (ERROR);
	return (1);
}
