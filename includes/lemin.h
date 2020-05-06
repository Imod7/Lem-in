/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lemin.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/18 09:25:17 by dominique     #+#    #+#                 */
/*   Updated: 2020/05/05 18:29:08 by dominique     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"

# define MAX_ROOMS 20

typedef enum		e_position
{
	MIDDLE = 0,
	START = 1,
	END = 2
}					t_position;

/*
** Struct t_ant_farm 
*/

typedef struct			s_ant_farm
{
	size_t				ants;
	size_t				rooms;
	struct s_hash_table	*hash_table;
	struct s_input		*input;
	struct s_room		*rooms_lst;
	struct s_queue		*queue;
}						t_ant_farm;

typedef struct			s_hash_item
{
	char				*room_name;
	// unsigned int		hashed_key;
	struct s_room		*room;
	struct s_hash_item	*colision_next;
}						t_hash_item;

typedef struct			s_hash_table
{
	size_t				size;
	struct s_hash_item	**array;
}						t_hash_table;

typedef struct			s_room
{
	char				*name;
	unsigned int		key;
	size_t				x_coord;
	size_t				y_coord;
	size_t				explored;
	t_position			position;
	struct s_room		*parent;
	struct s_room		*next;
	struct s_neighbor	*neighbors;
}						t_room;

typedef struct			s_neighbor
{
	// unsigned int		key;
	struct s_hash_item	*hash_item;
	struct s_neighbor	*next;
}						t_neighbor;

// typedef struct			s_link
// {
// 	struct s_room		*room_src;
// 	struct s_room		*room_dest;
// }						t_link;

typedef struct			s_input
{
	char				*line;
	struct s_input		*next;
}						t_input;

typedef struct			s_queue_item
{
	struct s_room		*room;
	struct s_queue_item	*next;
}						t_queue_item;

typedef struct			s_queue
{
	struct s_queue_item	*front;
	struct s_queue_item	*back;
}						t_queue;

/*
** Functions to check if the input is valid
** and then save it
*/

int						ft_saveinput(t_ant_farm *ant_farm, char *line, \
										size_t *j);
int						ft_exit_msg(t_ant_farm *ant_farm, size_t flag);
int						ft_exitprogram(t_ant_farm *ant_farm);
void					ft_save_neighbors(t_ant_farm *ant_farm);

/*
** Printing Functions
*/

void					print_input_list(t_input *input_data);
void					print_rooms_list(t_room *rooms_lst);
void					print_hash_table(t_hash_table *hash_table);
void					print_neighbors_list(t_hash_table *hash_table);

/*
** Functions to save the input data in a linked list
*/

t_input					*ft_input_newnode(char *line);
void					ft_input_addend(t_input **lst, t_input *newline);

/*
** Functions to save the rooms data in a linked list
*/

// t_room					*ft_room_newnode(char *str);
void					ft_room_addend(t_room **lst, t_room *new);

/*
** Functions to save the hash_items in the hash table
*/

t_hash_item				*ft_hashitem_newnode(t_room *room);
void					ft_hashitem_addend(t_hash_item **lst, t_hash_item *new);

/*
** Functions to free allocated memory
*/

void					ft_free_inputlst(t_input *input_lst);
void					ft_free_roomslst(t_room *rooms_lst);
void					ft_free_hashtable(t_hash_table *hash_table);
void					ft_free_line(char **line_items, size_t size);

/*
** Functions related to the hashing process and
** and the hashing process
*/

unsigned int			ft_hash_function(char *name, int size);
int						ft_hashing_process(t_ant_farm *ant_farm);
t_hash_item 			*ft_retrieve_hash_item(t_hash_table *hash_table, \
											char *str);

void					ft_bfs(t_ant_farm *ant_farm);

#endif
