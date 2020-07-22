/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sort_paths.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominiquesaripapazoglou <dominiquesarip      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/27 16:53:31 by dominiquesa   #+#    #+#                 */
/*   Updated: 2020/07/19 19:32:04 by dsaripap      ########   odam.nl         */
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
	// ft_printf(" splitting len %d\n", len);
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
	// ft_printf(" splitting patha %d pathb %d \n", (*ahalf)->path_id, (*bhalf)->path_id);
}

/*
** The merging part of merge sort
*/

static t_paths		*ft_mergeback(t_paths **ahalf, t_paths **bhalf)
{
	t_paths			*result_list;

	result_list = NULL;
	// ft_printf("  merge back\n");
	if (*ahalf == NULL)
		return (*bhalf);
	else if (*bhalf == NULL)
		return (*ahalf);
	else
	{
		// ft_printf("   ahalf %d, %d\n", (*ahalf)->path_id, \
		// ft_path_size(*ahalf));
		// ft_printf("   bhalf %d, %d\n", (*bhalf)->path_id, \
		// ft_path_size(*bhalf));
		if ((*ahalf)->path_size > (*bhalf)->path_size)
		{
			// ft_printf("    bigger \n");
			result_list = *bhalf;
			result_list->next = ft_mergeback(&((*bhalf)->next), ahalf);
			result_list->next->prev = *bhalf;
		}
		else
		{
			// ft_printf("    smaller \n");
			result_list = *ahalf;
			result_list->next = ft_mergeback(&((*ahalf)->next), bhalf);
			result_list->next->prev = *ahalf;
		}
	}
	// ft_printf("  result %d -> %d \n", result_list->path_id, result_list->next->path_id);
	// ft_printf("  result %d -> prev %d \n", result_list->next->path_id, result_list->next->prev->path_id);
	return (result_list);
}

/*
** Doing a presort in the Sorted Stack by implementing
** the Merge Sort algorithm
*/

t_paths 			*ft_mergesort(t_ant_farm *ant_farm, t_paths **completelist)
{
	t_paths			*first_half;
	t_paths			*second_half;

	first_half = NULL;
	second_half = NULL;
	while ((*completelist) != NULL && (*completelist)->run != ant_farm->best_run)
	{
		// ft_printf(">> iterating through Path %d\n", paths->path_id);
		(*completelist) = (*completelist)->next;
	}
	// ft_printf(">> Merge Sort paths Starting from Path %d\n", paths->path_id);
	// ft_printf("\nmerge complete %d\n", (*completelist)->path_id);
	if ((*completelist)->next == NULL)
		return (0);
	ft_splitlist((*completelist), &first_half, &second_half);
	ft_mergesort(ant_farm, &first_half);
	ft_mergesort(ant_farm, &second_half);
	// ft_printf("  apath %d\n", first_half->path_id);
	// ft_printf("  bpath %d\n", second_half->path_id);
	*completelist = ft_mergeback(&first_half, &second_half);
	return (*completelist);
	// ft_printf("complete %d\n", (*completelist)->path_id);
	// ft_printf("complete %d\n", (*completelist)->next->path_id);
	// if ((*completelist)->next->next != NULL)
	// 	ft_printf("complete %d\n", (*completelist)->next->next->path_id);
	// ft_printf("  complete %d\n", (*completelist)->next->next->path_id);
}
