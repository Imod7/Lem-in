/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lemin.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:40:12 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/06/26 17:56:43 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"
# include <stdio.h>
# include <errno.h>

typedef enum			e_prgm_signal
{
	SUCCESS = 0,
	success_ants_saved = 1,
	CONTINUE = 2,
	ERROR = -1,
	error_empty_line = -2,
	error_L_beginning_of_line = -3,
	error_invalid_start_room = -4,
	error_invalid_end_room = -5,
	error_invalid_intermediate_room = -6,
	error_in_link = -7,
	KO = -8
}						t_prgm_signal;

typedef enum		e_position
{
	MIDDLE = 0,
	START = 1,
	END = 2
}					t_position;

typedef enum		e_state
{
	UNEXPLORED = 0,
	EXPLORED = 1,
	COMPLETED = 2
}					t_state;

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
	struct s_stack		*stack;
	struct s_paths		*paths;
	size_t				max_paths;
	size_t				discovered_paths;
	t_prgm_signal		signal;
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
	size_t				level;
	int					score;
	size_t				ant_id;
	// struct s_ants		*ants;
	t_state				state;
	t_position			position;
	struct s_paths		*path;
	// int					path_id;
	struct s_room		*parent;
	struct s_room		*next;
	struct s_neighbor	*neighbors;
}						t_room;

typedef struct			s_neighbor
{
	// unsigned int		key;
	struct s_hash_item	*hash_item;
	struct s_neighbor	*next;
	struct s_neighbor	*prev;
}						t_neighbor;

typedef struct			s_input
{
	char				*line;
	struct s_input		*next;
}						t_input;

typedef struct			s_stack
{
	struct s_room		*room;
	struct s_stack		*next;
}						t_stack;

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

typedef struct			s_path_list
{
	struct s_room		*room;
	struct s_path_list	*next;
	struct s_path_list	*prev;
}						t_path_list;

typedef struct			s_paths
{
	int					path_id;
	int					path_size;
	size_t				ants_amount;
	struct s_path_list	*path_lst;
	struct s_path_list  *tail;
	struct s_ants		*ants_lst;
	struct s_paths		*next;
	struct s_paths		*prev;
}						t_paths;

typedef struct			s_ants
{
	int					ant_id;
	struct s_paths		*path;
	struct s_ants		*next;
	struct s_ants		*prev;
}						t_ants;

/*
** Functions to do Input Validation and Saving
*/

t_prgm_signal			ft_saveinput(t_ant_farm *ant_farm, char *line, \
										size_t *j);
int						ft_check_if_is_room(t_ant_farm *ant_farm, char *line, \
											char *link);
int						lm_check_if_ants_amount(t_ant_farm *ant_farm, \
												char *line, size_t j);
int						ft_save_inputline(t_ant_farm *ant_farm, char *line, \
											t_position pos);
int						ft_save_neighbors(t_ant_farm *ant_farm);

/*
** Functions to Exit the program
*/

int						ft_exit_msg(t_prgm_signal signal);
int						ft_exitprogram(t_ant_farm *ant_farm);

/*
** Printing Functions
*/

void					print_input_list(t_input *input_data);
void					print_rooms_list(t_room *rooms_lst);
void					print_hash_table(t_hash_table *hash_table);
void					print_neighbors_list(t_hash_table *hash_table);
void					print_neighbors_list_debug(t_hash_table *hash_table);

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
void					ft_free_paths(t_ant_farm *ant_farm);
void					ft_free_pathlst(t_path_list *path_lst);
void					ft_path_del_last(t_ant_farm *ant_farm);

/*
** Functions related to the hashing process and
** and the hashing process
*/

unsigned int			ft_hash_function(char *name, int size);
int						ft_hashing_process(t_ant_farm *ant_farm);
t_hash_item				*ft_retrieve_hash_item(t_hash_table *hash_table, \
											char *str);

/*
** Functions to explore the graph
*/

void					ft_bfs(t_ant_farm *ant_farm);
void					ft_dfs(t_ant_farm *ant_farm);
int						ft_dfs_stack_len(t_stack *lst);

/*
** Functions related to paths
*/

void					ft_save_paths_bfs(t_ant_farm *ant_farm);
void					ft_path_addend(t_paths **lst, t_paths *new);
void					ft_pathlst_addstart(t_path_list **l, t_path_list *new);
void					ft_pathlst_addend(t_path_list **lst, t_path_list *new);
size_t					ft_find_maxpaths(t_ant_farm *ant_farm);
t_paths					*ft_create_path_list(t_ant_farm *ant_farm);
void					ft_print_paths(t_ant_farm *ant_farm);
void					ft_print_paths_list(t_ant_farm *ant_farm);
void					ft_print_paths_list_detail(t_ant_farm *ant_farm);
void					ft_save_room_to_dfs_path(t_path_list **path_lst, \
												t_room *room);
t_room					*ft_get_start_room(t_room *temp);
t_room					*ft_get_end_room(t_ant_farm *ant_farm);

/*
** Functions to implement a queue and its FIFO functionalities
** for BFS implementation
*/

void					ft_dequeue(t_queue	*q);
int						ft_queue_is_empty(t_queue *q);
void					ft_enqueue(t_queue	*q, t_room	*temp);
void					ft_print_queue(t_queue *q);
void					ft_free_queue(t_queue *q);

/*
** Functions to implement a stack and its LIFO functionalities
** for DFS implementation
*/

void					ft_pop(t_stack **stack);
void					ft_push(t_stack **stack, t_room *temp);
int						ft_stack_empty(t_stack *stack);
void					ft_print_stack(t_stack *s);
int						ft_sort_neighbors(t_neighbor **completelist, \
											t_room **room);

/*
** Functions related to ants
*/

int						ft_ants_to_paths(t_ant_farm *ant_farm);
void					ft_print_move(t_ant_farm *ant_farm);
void					ft_keep_ants_moving(t_ant_farm *ant_farm);
void					ft_print_ants(t_ant_farm *ant_farm);
void					ft_move_ants(t_ant_farm *ant_farm);

#endif
