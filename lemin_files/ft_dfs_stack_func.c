/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dfs_stack_func.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:37:24 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/06/19 11:16:08 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void				ft_pop(t_stack **stack)
{
	t_stack			*temp;

	if (*stack != NULL)
	{
		temp = *stack;
		(*stack) = (*stack)->next;
		free(temp);
	}
}

int					ft_dfs_stack_len(t_stack *lst)
{
	t_stack			*temp;
	int				len;

	temp = lst;
	len = 0;
	if (temp == NULL)
		return (0);
	while (temp != NULL)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}

void				ft_push(t_stack **stack, t_room *room)
{
	t_stack			*new;

	new = (t_stack *)ft_memalloc(sizeof(t_stack));
	new->room = room;
	if (*stack == NULL)
	{
		*stack = new;
		return ;
	}
	new->next = *stack;
	*stack = new;
}

int					ft_stack_empty(t_stack *stack)
{
	int				result;

	result = (stack == NULL) ? 1 : 0;
	return (result);
}

void				ft_print_stack(t_stack *s)
{
	t_stack			*temp;

	temp = s;
	ft_printf(ANSI_COLOR_GREEN_EMER"Stack (len = %d)\n", ft_dfs_stack_len(s));
	ft_printf("------\n");
	if (temp == NULL)
		ft_printf("stack is empty\n");
	while (temp != NULL)
	{
		ft_printf("%s\n", temp->room->name);
		temp = temp->next;
	}
	ft_printf(ANSI_COLOR_RESET);
}
