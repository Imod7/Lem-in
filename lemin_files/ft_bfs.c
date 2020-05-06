/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bfs.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/05 16:11:02 by dominique     #+#    #+#                 */
/*   Updated: 2020/05/06 20:51:25 by dominique     ########   odam.nl         */
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

static int			ft_queue_is_empty(t_queue *q)
{
	return (q->back == NULL);
}

void				ft_enqueue(t_queue	*q, t_room	*temp)
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
	q_item->room->explored = 1;
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

void				ft_print_paths(t_ant_farm *ant_farm)
{
	t_room			*temp;

	temp = ant_farm->rooms_lst;
	while (temp != NULL)
	{
		if (temp->position == END)
			break ;
		temp = temp->next;
	}
	ft_printf("%s", temp->name);
	while (temp->parent != NULL)
	{
		ft_printf("->%s", temp->parent->name);
		temp = temp->parent;
	}
}

void				ft_bfs(t_ant_farm *ant_farm)
{
	t_room			*temp;
	t_neighbor		*neighbors;
	t_queue			*queue;

	queue = (t_queue *)ft_memalloc(sizeof(t_queue));
	temp = ant_farm->rooms_lst;
	while (temp != NULL)
	{
		if (temp->position == START)
			break ;
		temp = temp->next;
	}
	// while (queue->front != NULL)
	ft_enqueue(queue, temp);
	while (!ft_queue_is_empty(queue))
	{
		print_rooms_list(ant_farm->rooms_lst);
		neighbors = queue->front->room->neighbors;
		while (neighbors != NULL)
		{
			if (!(neighbors->hash_item->room->explored))
			{
				ft_enqueue(queue, neighbors->hash_item->room);
				neighbors->hash_item->room->parent = queue->front->room;
			}
			neighbors = neighbors->next;
		}
		ft_printf("enqueued the neighbors that are not explored \n");
		ft_print_queue(queue);
		ft_dequeue(queue);
		ft_printf("removing front of queue \n");
		ft_print_queue(queue);
	}
	ft_printf("The end \n");
	ft_print_queue(queue);
	// ft_print_paths(ant_farm);
}
