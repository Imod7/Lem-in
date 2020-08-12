# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dominique <dominique@student.codam.nl>       +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/21 13:51:27 by dominique     #+#    #+#                  #
#    Updated: 2020/08/12 15:15:23 by svan-der      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME_LEMIN = lem-in
LIBFT = libft/libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror -g
# FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LEMIN_SRCDIR = lemin_files
LEMIN_OBJDIR = .obj-lemin
EXEDIR = ./

RED=\033[0;31m
GREEN=\033[0;32m
CYAN=\033[0;36m
NC=\033[0m # No Color

SRC_LEMIN =	\
		lemin.c \
		ft_ants_to_paths.c \
		ft_ants_move.c \
		ft_ants_functions.c \
		ft_bfs.c \
		ft_bfs_queue_func.c \
		ft_bfs_levels.c \
		ft_bfs_reset.c \
		ft_bfs_sink.c \
		ft_check_dup_rooms.c\
		ft_free_lists_tables.c \
		ft_free_other.c \
		ft_free_paths.c \
		ft_hashing.c \
		ft_input_parsing.c \
		ft_input_checking.c \
		ft_input_validation_func.c \
		ft_input_validation_order.c\
		ft_lines_move.c \
		ft_min_cut.c \
		ft_min_cut_sink.c\
		ft_map_data_functions.c \
		ft_paths_commonfunc.c \
		ft_paths_mainfunc.c \
		ft_print_ants_move.c \
		ft_print_hash_table.c \
		ft_print_neighbors.c \
		ft_print_rooms.c \
		ft_print_paths.c \
		ft_print_ants.c \
		ft_prgm_functions.c \
		ft_prgm_options.c \
		ft_rooms_functions.c \
		ft_save_hash_items.c \
		ft_save_neighbors.c \
		ft_save_paths.c \
		ft_sort_neighbors.c \
		ft_sort_paths.c \

OBJ_LEMIN = $(SRC_LEMIN:%.c=$(LEMIN_OBJDIR)/%.o)

INCL = libft/libft.a

all: $(EXEDIR)$(NAME_LEMIN)

$(LIBFT):
	@echo "${CYAN} [ * ] ${NC}Calling libft makefile"
	@$(MAKE) -C libft

$(EXEDIR)$(NAME_LEMIN): $(OBJ_LEMIN) $(LIBFT)
	@echo "${GREEN} [ + ] ${NC}Creating lem-in object files"
	@echo "${GREEN} [ + ] ${NC}Creating lem-in executable"
	@$(CC) $(FLAGS) $(OBJ_LEMIN) -o $(EXEDIR)$(NAME_LEMIN) $(INCL)

$(LEMIN_OBJDIR)/%.o: $(LEMIN_SRCDIR)/%.c $(INCL)
	@mkdir -p $(LEMIN_OBJDIR)
	@$(CC) $(FLAGS) -c -o $@ $<

.PHONY: clean

clean:
	@echo "${RED} [ - ] ${NC}Deleting lem-in object files"
	@rm -rf $(LEMIN_OBJDIR)
	@$(MAKE) clean -C libft

fclean: clean
	@echo "${RED} [ - ] ${NC}Deleting lem-in executable"
	@rm -f $(EXEDIR)$(NAME_LEMIN)
	@echo "${RED} [ - ] ${NC}Deleting the libft.a file"
	@rm -f $(LIBFT)

re: fclean all

lldb: re
	gcc -g main.c -L. -lft

norm:
	norminette $(SRC) $(INCL) | grep -e "Error" -e "Warning" -B 1
