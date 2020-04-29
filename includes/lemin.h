/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lemin.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/18 09:25:17 by dominique     #+#    #+#                 */
/*   Updated: 2020/04/28 22:59:45 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"

#define 			MAX_ROOMS 20

typedef enum		e_position
{
	START = 1,
	END = 2
}					t_position;

typedef struct		s_ant_farm
{
	size_t			ants;
	size_t			rooms;
	struct s_room	*rooms_array[MAX_ROOMS];
	struct s_input	*input;
}					t_ant_farm;

typedef struct		s_room
{
	size_t			hashed_name;
	size_t			x_coord;
	size_t			y_coord;
	size_t			explored;
	t_position		position;
	struct s_room	*next;
}					t_room;

typedef struct		s_link
{
	struct s_room	*room_src;
	struct s_room	*room_dest;
}					t_link;

typedef struct		s_input
{
	char			*line;
	struct s_input	*next;
}					t_input;

typedef struct		s_queue
{
	size_t			count;
	struct s_room	*room_rear;
	struct s_room	*room_front;
}					t_queue;

/*
** Functions to check if the input is valid
** and then save it
*/

int					ft_saveinput(t_ant_farm *ant_farm, char *line, \
										size_t *j);
int					check_if_valid(t_ant_farm *ant_farm, char *str);
int					add_commands(t_ant_farm *ant_farm, char *line);
int					ft_exit_msg(t_ant_farm *ant_farm, size_t flag);
int					ft_exitprogram(t_ant_farm *ant_farm);

/*
** Printing Functions
*/

void				print_input_list(t_input *input_data);

/*
** Functions to save the input data in a temp linked list
*/

t_input				*ft_input_newnode(char *line);
void				ft_input_addend(t_input **lst, t_input *new);

/*
** Functions to free allocated memory
*/

void				ft_free_inputlst(t_input *input_lst);

#endif
