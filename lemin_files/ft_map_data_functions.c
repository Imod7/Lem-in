/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_map_data_functions.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:39:29 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 14:08:50 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** Functions ft_input_newnode & ft_input_addend
** are used to save the lines of the input file/map
** into a linked list.
*/

t_input			*ft_input_newnode(char *line)
{
	t_input		*newnode;

	newnode = ft_memalloc(sizeof(t_input));
	if (newnode == NULL)
		return (NULL);
	newnode->line = line;
	newnode->next = NULL;
	return (newnode);
}

void			ft_input_addend(t_input **lst, t_input *new)
{
	t_input		*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

/*
** Function that prints the linkedlist with the raw input lines
** that we retrieved from the map
*/

void			print_input_list(t_input *input_data)
{
	t_input		*temp;

	temp = input_data;
	ft_printf("\n   Linked List with Raw Input Lines      \n");
	ft_printf("-----------------------------------------\n");
	ft_printf("|line\t\t\tnext_line\t|\n");
	while (temp != NULL)
	{
		ft_printf("|%s\t\t", temp->line);
		if (temp->next != NULL)
			ft_printf("\t-> %s\t|\n", temp->next->line);
		else
			ft_printf("\t-> NULL\t|\n");
		temp = temp->next;
	}
	ft_printf("----------------------------------------\n");
}

void			ft_print_mapdata(t_ant_farm *ant_farm)
{
	t_input		*lines;

	lines = ant_farm->input;
	while (lines != NULL)
	{
		ft_printf("%s\n", lines->line);
		lines = lines->next;
	}
	ft_printf("\n");
}
