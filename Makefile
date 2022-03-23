# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/06 13:59:16 by npinheir          #+#    #+#              #
#    Updated: 2022/03/23 18:34:19 by fcaquard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the program
NAME = minishell

# Compiling flags
FLAGS = -Wall -Wextra -Werror -g

# Folders
SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./include/
LIBFT_DIR = ./libft/

# Source files and object files
SRC_FILES = main.c		\
	input.c				\
	signals.c			\
	init.c				\
	parse_quotes.c		\
	parse_params.c		\
	parse_cmd.c			\
	parse_verify.c		\
	clear.c				\
	clear_all.c			\
	parse_redir.c		\
	parse_redir2.c		\
	parse_redir_fill.c	\
	find_path.c			\
	variables.c			\
	variables_replace.c	\
	env_tolist.c 	 	\
	env_toarray.c		\
	env_list.c		  	\
	builtins_route.c	\
	builtins_cd.c		\
	builtins_pwd.c		\
	builtins_unset.c	\
	builtins_echo.c		\
	builtins_export.c	\
	builtins_env.c		\
	builtins_exit.c		\
	apply_redir.c		\
	apply_redir_create_files.c	\
	error_handling.c	\
	utils.c				\
	utils_bis.c			\
	exec.c				\
	exec_pipeline.c		\
	ft_realloc.c		\
	debug.c				\
	

OBJ_FILES = $(SRC_FILES:.c=.o)

# Paths
SRC	:= $(wildcard $(SRC_DIR)*.c)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

# Libft and Minilibx linkers
LNK = -L $(LIBFT_DIR) -lft -lreadline

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
NONE = \033[0m

# all rule
all: obj $(LIBFT) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)
	@echo "\t$(GREEN)✔ Object folder created in minishell !$(NONE)"
	
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@gcc $(FLAGS) -I $(LIBFT_DIR) -I $(INC_DIR) -o $@ -c $<
	
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Compiling
$(NAME): $(OBJ)
	@gcc $(OBJ) $(LNK) -lm -o $(NAME)
	@echo "\t$(GREEN)✔ Minishell ready to run !$(NONE)"

# clean rule
clean:
	@rm -Rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "\t$(GREEN)✔ All objects removed !$(NONE)"

# fclean rule
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "\t$(GREEN)✔ Project fully cleaned !$(NONE)"

# re rule
re:	fclean all

# c rule
c:	all clean

# phony
.PHONY: all clean fclean re
