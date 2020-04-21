/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lemin.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/18 09:25:17 by dominique     #+#    #+#                 */
/*   Updated: 2020/04/20 09:12:21 by dominique     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

typedef enum		e_position
{
	START = 1,
	END = 2
}					t_position;

typedef struct		s_ant_farm
{
	size_t			ants;

}					t_ant_farm;

/*
** The hash_name will be produced by our hash function
*/

typedef struct		s_room
{
	size_t			hash_name;
	size_t			x_coord;
	size_t			y_coord;
	size_t			explored;
	t_position		position;
}					t_room;

typedef struct		s_link
{
	struct s_room	*room_src;
	struct s_room	*room_dest;
}					t_link;

typedef struct		s_queue
{
	size_t			count;
	struct s_room	*room_rear;
	struct s_room	*room_front;
}					t_queue;

typedef struct 		*graph[MAX_SIZE]
/*
** I can represent a graph with an adjacency list
*/

#endif
