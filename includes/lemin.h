/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lemin.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:40:12 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/14 05:24:04 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"

typedef struct			s_data
{
	int					valid;
	int					min;
	char				*argument;
}						t_data;

typedef enum			e_prgm_signal
{
	SUCCESS = 0,
	success_ants_saved = 1,
	succes_room_saved = 4,
	succes_link_saved = 5,
	CONTINUE = 2,
	BREAK = 3,
	ERROR = -1,
	error_empty_line = -2,
	error_L_beginning_of_line = -3,
	error_invalid_start_room = -4,
	error_invalid_end_room = -5,
	error_invalid_intermediate_room = -6,
	error_in_link = -7,
	KO = -8,
	error_invalid_ants_amount = -9,
	error_invalid_room_data = -10,
	error_end_room_exists = -11,
	error_start_room_exists = -12,
	error_end_room_missing = -13,
	error_start_room_missing = -14,
	error_empty_file = -15,
	error_coord_not_number = -16,
	error_no_links = -17,
	error_no_rooms = -18,
	error_start_room_con = -19,
	error_end_room_con = -20,
	error_no_solution = -21,
	error_file_missing = -22
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
** The enum t_option helps to set the options of the program
** which are the bonuses of the project
*/

typedef enum			e_option
{
	OPTION_U = (1 << 0),
	OPTION_M = (1 << 1),
	OPTION_A = (1 << 2),
	OPTION_L = (1 << 3)
}						t_option;

/*
** Struct t_lines saves the number of lines
** each path requires in order to compare
** more easily and choose the more efficient one.
*/

typedef struct			s_lines
{
	size_t				lines;
	size_t				run;
	struct s_lines		*next;
	struct s_lines		*prev;
}						t_lines;

/*
** Struct t_ant_farm with all the main information
** of the program like the rooms, neighbors, ants and paths.
*/

typedef struct			s_ant_farm
{
	long long			ants;
	size_t				rooms;
	struct s_data		*data;
	struct s_hash_table	*hash_table;
	struct s_input		*input;
	struct s_room		*rooms_lst;
	struct s_queue		*queue;
	struct s_stack		*stack;
	struct s_paths		*paths;
	size_t				total_runs;
	size_t				best_run;
	size_t				lines;
	size_t				max_paths;
	size_t				discovered_paths;
	t_lines				*lines_lst;
	t_option			options;
	t_prgm_signal		signal;
}						t_ant_farm;

typedef struct			s_hash_item
{
	char				*room_name;
	unsigned int		hashed_key;
	struct s_room		*room;
	struct s_hash_item	*colision_prev;
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
	size_t				level_source;
	size_t				level_sink;
	int					score;
	size_t				run;
	struct s_ants		*ants_lst;
	t_state				state;
	t_position			position;
	struct s_paths		*path;
	struct s_room		*parent;
	struct s_room		*next;
	struct s_neighbor	*neighbors;
}						t_room;

typedef struct			s_neighbor
{
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

typedef struct			s_ants
{
	int					ant_id;
	struct s_paths		*path;
	struct s_ants		*next;
	struct s_ants		*prev;
}						t_ants;

typedef struct			s_paths
{
	int					path_id;
	int					path_size;
	size_t				ants_amount;
	size_t				run;
	struct s_path_list	*path_lst;
	struct s_path_list	*tail;
	struct s_ants		*ants_lst;
	struct s_paths		*next;
	struct s_paths		*prev;
}						t_paths;

/*
** Functions to do Input Validation and Saving
*/

t_prgm_signal			ft_saveinput(t_ant_farm *ant_farm, char *line, \
										size_t *j, t_data *data);
int						ft_is_number(char *str);
int						check_argv(int *signal, char *str);
int						add_num(char *str, int sign);
int						ft_precheck_if_valid(t_ant_farm *ant_farm, \
											t_data *data, int i);
int						check_dup_rooms_lst(t_room **rooms_lst);
int						set_prgm_options(char *argv, t_ant_farm *ant_farm);
int						ft_check_if_is_room(t_ant_farm *ant_farm, char *line, \
											char *link, t_data *data);
int						ft_check_if_ants_amount(t_ant_farm *ant_farm, \
												char *line, size_t j);
int						ft_save_inputline(t_ant_farm *ant_farm, char *line, \
											t_position pos);
int						ft_save_neighbors(t_ant_farm *ant_farm);
int						ft_check_links(t_ant_farm *ant_farm);
size_t					array_size(char **array);
int						ft_check_str_length(char *str);
t_prgm_signal			save_start_end(t_ant_farm *ant_farm, char **line, \
									t_position pos, int i);

/*
** Functions to Exit the program
*/

int						ft_exit_msg(t_ant_farm *ant_farm, t_prgm_signal signal);
int						ft_exitprogram(t_ant_farm *ant_farm);

/*
** Printing Functions
*/

void					print_input_list(t_input *input_data);
void					ft_print_rooms_list(t_room *rooms_lst);
void					print_hash_table(t_hash_table *hash_table);
void					ft_print_neighbors_list(t_hash_table *hash_table);
void					ft_print_mapdata(t_ant_farm *ant_farm);

/*
** Functions to save the input data in a linked list
*/

t_input					*ft_input_newnode(char *line);
void					ft_input_addend(t_input **lst, t_input *newline);

/*
** Functions related to Rooms
*/

void					ft_room_addend(t_room **lst, t_room *new);

/*
** Functions to save the hash_items in the hash table
*/

t_hash_item				*ft_hashitem_newnode(t_room *room, unsigned int	key);
void					ft_hashitem_addend(t_hash_item **lst, t_hash_item *new);

/*
** Functions to Free Allocated Memory
*/

void					ft_free_data(t_data *data);
void					ft_free_inputlst(t_input *input_lst);
void					ft_free_roomslst(t_room *rooms_lst);
void					ft_free_hashtable(t_hash_table *hash_table);
void					ft_free_string(char **string, size_t size);
void					ft_free_paths(t_ant_farm *ant_farm);
void					ft_free_pathlst(t_path_list *path_lst);
void					ft_free_path_on_pathid(t_ant_farm *ant_farm, \
												int path_id);
void					ft_free_path_lines(t_lines *lines_head);

/*
** Functions related to the hashing process and
** and the hashing process
*/

unsigned int			ft_hash_function(char *name, int size);
int						ft_hashing_process(t_ant_farm *ant_farm);
t_hash_item				*ft_retrieve_hash_item(t_hash_table *hash_table, \
											char *str);

/*
** Functions related to BFS exploration of the graph
*/

int						ft_bfs_runs(t_ant_farm *ant_farm);
int						ft_bfs_algorithm(t_ant_farm *ant_farm, size_t run);
void					ft_bfs_reset(t_ant_farm *ant_farm);
void					ft_bfs_fullreset(t_ant_farm *ant_farm);
void					ft_bfs_fullreset_and_score(t_ant_farm *ant_farm);
int						ft_run_bfs_reset_score(t_ant_farm *ant_farm, \
											int flag_stop, size_t *i);
int						lvl_sink(t_ant_farm *ant_farm);
int						lvl_source(t_ant_farm *ant_farm);
size_t					ft_check_min_cut(t_ant_farm *ant_farm, \
									t_neighbor *neighbors, \
									size_t run);
void					ft_reset_score_on_pathid(t_ant_farm *ant_farm, \
											int path_id);
void					ft_bfs_reset(t_ant_farm *ant_farm);
void					ft_bfs_fullreset(t_ant_farm *ant_farm);
size_t					ft_bfs_sink(t_ant_farm *ant_farm, size_t run);
size_t					ft_check_min_cut_sink(t_ant_farm *ant_farm, \
									t_neighbor *neighbors, \
									size_t current_run);

/*
** Functions related to paths
*/

int						ft_save_paths_bfs(t_ant_farm *ant_farm, size_t flag, \
									size_t run);
void					ft_path_addend(t_paths **lst, t_paths *new);
void					ft_pathlst_addstart(t_path_list **l, t_path_list *new);
void					ft_pathlst_addend(t_path_list **lst, t_path_list *new);
size_t					ft_find_maxpaths(t_ant_farm *ant_farm);
void					ft_print_paths(t_ant_farm *ant_farm);
void					ft_print_paths_sizes(t_ant_farm *ant_farm);
void					ft_print_paths_list(t_ant_farm *ant_farm);
t_room					*ft_get_start_room(t_room *temp);
t_room					*ft_get_end_room(t_ant_farm *ant_farm);
void					ft_paths_discovered(t_ant_farm *ant_farm);
void					ft_sort_paths_on_size(t_ant_farm *ant_farm);
t_paths					*ft_mergesort(t_ant_farm *ant_farm, \
									t_paths **completelist);
size_t					ft_path_size(t_paths *lst);
void					check_if_valid_path(t_ant_farm *ant_farm);

/*
** Functions to implement a queue and its FIFO functionalities
** for BFS implementation
*/

void					ft_dequeue(t_queue	*q);
int						ft_queue_is_empty(t_queue *q);
int						ft_enqueue(t_queue	*q, t_room	*temp);
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
										t_room **room, size_t flag);

/*
** Function related to the bottleneck room and the checking
** of cutting an edge
*/

size_t					ft_check_cut_edge(t_ant_farm *ant_farm, \
										t_neighbor *neighbors, t_room *temp);

/*
** Functions related to ants
*/

void					ft_add_ants_to_list(t_ants **lst, t_ants *new);
int						ft_ants_to_paths(t_ant_farm *ant_farm);
int						choose_ant(t_paths *path, int ant_id);
int						ft_move_ants(t_ant_farm *ant_farm);
int						add_ant_to_room(t_paths *path, t_room *room, \
										int ant_id);
void					ft_add_ant_to_antslist(t_ants **lst, t_ants *new);
void					ft_print_move(t_ant_farm *ant_farm);
void					ft_print_ants_in_paths(t_ant_farm *ant_farm);
void					ft_print_ants_in_rooms(t_ant_farm *ant_farm);
void					ft_free_ants_lst(t_ants **ants_lst);
void					ft_free_paths_ants_lst(t_ant_farm *ant_farm);

/*
** Functions related to ants move
*/

int						check_ant_vs_room(t_paths *path, t_room *room, \
										int ant_id);
int						choose_and_check(t_paths *path, t_path_list *path_lst);

/*
** Functions related to the moving of the ants.
** like the calculation of needed lines to move all the ants
** from source to sink
*/

void					ft_calculate_lines(t_ant_farm *ant_farm);
void					ft_lines_list_addend(t_lines **lst, t_lines *new);

#endif
