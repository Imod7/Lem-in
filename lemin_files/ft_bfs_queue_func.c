/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bfs_queue_func.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/07 09:53:11 by dominique     #+#    #+#                 */
/*   Updated: 2020/06/02 14:28:04 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void				ft_dequeue(t_queue	*q)
{
	t_queue_item	*q_item;

	q_item = q->front;
    q->front = q->front->next;
	if (q->front == NULL)
		q->back = NULL;
    free(q_item);
}

void				ft_enqueue(t_queue *q, t_room *temp)
{
	t_queue_item	*q_item;

	q_item = (t_queue_item *)ft_memalloc(sizeof(t_queue_item));
	q_item->room = temp;
	if(!ft_queue_is_empty(q))
	{
		q->back->next = q_item;
		q->back = q_item;
	}
	else
		q->front = q->back = q_item;
	q_item->room->state = EXPLORED;
}

int					ft_queue_is_empty(t_queue *q)
{
	return (q->back == NULL);
}

void				ft_print_queue(t_queue *q)
{
	t_queue_item	*temp;

	temp = q->front;
	ft_printf("Queue\n");
	ft_printf("------\n");
	if (temp == NULL)
		ft_printf("queue is empty\n");
	while (temp != NULL)
	{
		ft_printf("%s\n", temp->room->name);
		temp = temp->next;
	}
}

void				ft_free_queue(t_queue *q)
{
	if (q == NULL)
		return ;
	while (!ft_queue_is_empty(q))
		ft_dequeue(q);
	free(q);
}
