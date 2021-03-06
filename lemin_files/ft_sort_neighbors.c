/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sort_neighbors.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:39:48 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 14:41:58 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int					ft_stack_len(t_neighbor *lst)
{
	t_neighbor		*temp;
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

/*
** The splitting part of merge sort
*/

void				ft_splitlist(t_neighbor *completelist, \
								t_neighbor **ahalf, t_neighbor **bhalf)
{
	int				len;
	int				split;
	t_neighbor		*splitnode;

	len = ft_stack_len(completelist);
	split = (len % 2 == 0) ? (len / 2) : ((len / 2) + 1);
	if (len == 1)
	{
		*ahalf = completelist;
		(*ahalf)->next = NULL;
		*bhalf = NULL;
	}
	else
	{
		splitnode = completelist;
		while (split - 1 > 0)
		{
			splitnode = splitnode->next;
			split--;
		}
		*ahalf = completelist;
		*bhalf = splitnode->next;
		(*bhalf)->prev = NULL;
		splitnode->next = NULL;
	}
}

/*
** The merging part of merge sort
*/

t_neighbor			*ft_mergeback(t_neighbor **ahalf, t_neighbor **bhalf, \
									size_t flag)
{
	t_neighbor		*result_list;

	result_list = NULL;
	if (*ahalf == NULL)
		return (*bhalf);
	else if (*bhalf == NULL)
		return (*ahalf);
	if ((flag == 0 && (*ahalf)->hash_item->room->score > \
	(*bhalf)->hash_item->room->score) || \
	(flag == 1 && (*ahalf)->hash_item->room->level_sink > \
	(*bhalf)->hash_item->room->level_sink))
	{
		result_list = *bhalf;
		result_list->next = ft_mergeback(&((*bhalf)->next), ahalf, flag);
		result_list->next->prev = *bhalf;
	}
	else
	{
		result_list = *ahalf;
		result_list->next = ft_mergeback(&((*ahalf)->next), bhalf, flag);
		result_list->next->prev = *ahalf;
	}
	return (result_list);
}

/*
** Doing a presort in the Sorted Stack by implementing
** the Merge Sort algorithm
*/

t_neighbor			*ft_merge_sort(t_neighbor **completelist, size_t flag)
{
	t_neighbor		*first_half;
	t_neighbor		*second_half;

	first_half = NULL;
	second_half = NULL;
	if ((*completelist)->next == NULL)
		return (*completelist);
	ft_splitlist((*completelist), &first_half, &second_half);
	ft_merge_sort(&first_half, flag);
	ft_merge_sort(&second_half, flag);
	*completelist = ft_mergeback(&first_half, &second_half, flag);
	return (*completelist);
}

/*
** Sorts the neighbors of the given room
** flag = 0 sorts by score
** flag = 1 sorts by level_sink
** Checks which room has the smallest score and puts that first
*/

int					ft_sort_neighbors(t_neighbor **completelist, \
									t_room **room, size_t flag)
{
	(*room)->neighbors = ft_merge_sort(completelist, flag);
	return (0);
}
