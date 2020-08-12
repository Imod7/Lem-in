/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sort_paths.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/11 20:27:45 by svan-der      #+#    #+#                 */
/*   Updated: 2020/08/12 14:42:48 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** The splitting part of merge sort
*/

static void			ft_splitlist(t_paths *completelist, \
								t_paths **ahalf, t_paths **bhalf)
{
	int				len;
	int				split;
	t_paths			*splitnode;

	len = ft_path_size(completelist);
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

static t_paths		*ft_mergeback(t_paths **ahalf, t_paths **bhalf)
{
	t_paths			*result_list;

	result_list = NULL;
	if (*ahalf == NULL)
		return (*bhalf);
	else if (*bhalf == NULL)
		return (*ahalf);
	else
	{
		if ((*ahalf)->path_size > (*bhalf)->path_size)
		{
			result_list = *bhalf;
			result_list->next = ft_mergeback(&((*bhalf)->next), ahalf);
			result_list->next->prev = *bhalf;
		}
		else
		{
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

t_paths				*ft_mergesort(t_ant_farm *ant_farm, t_paths **completelist)
{
	t_paths			*first_half;
	t_paths			*second_half;

	first_half = NULL;
	second_half = NULL;
	while ((*completelist) != NULL \
	&& (*completelist)->run != ant_farm->best_run)
	{
		(*completelist) = (*completelist)->next;
	}
	if ((*completelist)->next == NULL)
		return (0);
	ft_splitlist((*completelist), &first_half, &second_half);
	ft_mergesort(ant_farm, &first_half);
	ft_mergesort(ant_farm, &second_half);
	*completelist = ft_mergeback(&first_half, &second_half);
	return (*completelist);
}
