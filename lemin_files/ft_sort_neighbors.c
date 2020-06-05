/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sort_neighbors.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 08:57:54 by dominique     #+#    #+#                 */
/*   Updated: 2020/05/20 11:27:28 by dominique     ########   odam.nl         */
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

t_neighbor			*ft_mergeback(t_neighbor **ahalf, t_neighbor **bhalf)
{
	t_neighbor		*result_list;

	result_list = NULL;
	if (*ahalf == NULL)
		return (*bhalf);
	else if (*bhalf == NULL)
		return (*ahalf);
	else
	{
		// if (((*ahalf)->hash_item->room != NULL) && ((*bhalf)->hash_item->room != NULL))
		// 	ft_printf("ahalf %s = %d, bhalf %s = %d \n", (*ahalf)->hash_item->room->name, (*ahalf)->hash_item->room->score, (*bhalf)->hash_item->room->name, (*bhalf)->hash_item->room->score);
		if ((*ahalf)->hash_item->room->score < (*bhalf)->hash_item->room->score)
		{
			// ft_printf("bhalf first \n");
			result_list = *bhalf;
			result_list->next = ft_mergeback(&((*bhalf)->next), ahalf);
			result_list->next->prev = *bhalf;
		}
		else
		{
			// ft_printf("ahalf first \n");
			result_list = *ahalf;
			result_list->next = ft_mergeback(&((*ahalf)->next), bhalf);
			result_list->next->prev = *ahalf;
		}
	}
	return (result_list);
}

/*
** Doing a presort in the Sorted Stack by implementing
** the Merge Sort algorithm
*/

t_neighbor			*ft_merge_sort(t_neighbor **completelist)
{
	t_neighbor		*first_half;
	t_neighbor		*second_half;

	// ft_printf("merge sort \n");
	first_half = NULL;
	second_half = NULL;
	if ((*completelist)->next == NULL)
		return (*completelist);
	ft_splitlist((*completelist), &first_half, &second_half);
	ft_merge_sort(&first_half);
	ft_merge_sort(&second_half);
	*completelist = ft_mergeback(&first_half, &second_half);
	// ft_printf(" list %s \n", (*completelist)->hash_item->room->name);
	return (*completelist);
}

int					ft_sort_neighbors(t_neighbor **completelist, t_room **room)
{
	(*room)->neighbors = ft_merge_sort(completelist);
	// ft_printf(" after merge %s", (*room)->neighbors->hash_item->room->name);
	return (0);
}