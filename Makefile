# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/18 13:12:22 by roruiz-v          #+#    #+#              #
#    Updated: 2023/12/13 19:34:16 by roruiz-v         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

LIB = -L /Users/roruiz-v/.brew/opt/readline/lib -lreadline

# INCLUDE para 42:
#INCLUDE = -I /System/Volumes/Data/sgoinfre/goinfre/Perso/roruiz-v/homebrew/opt/readline/include

# INCLUDE para casa:
#  export LDFLAGS="-L/usr/local/opt/readline/lib"
INCLUDE = -I/usr/local/opt/readline/include

SRC		=	main.c \
			msh_signals.c \
			msh_simple_lexer.c \
			msh_simple_parser.c \
			msh_executor.c \
			msh_builtin_executor.c \
			msh_builtin_echo.c \
			msh_builtin_exit.c \
			msh_builtin_export.c \
			msh_builtin_cd.c \
			msh_builtin_cd_movements.c \
			msh_builtins_env_pwd_unset.c \
			msh_redir_heredoc.c \
			msh_redir_in_out_file.c \
			msh_env_lst_utils_dupl_env.c \
			msh_env_lst_utils_add_nds.c \
			msh_env_lst_utils_mfy_nds.c \
			msh_env_lst_utils_del_nds.c \
			msh_env_lst_utils_print_nds.c \
			msh_export_index_lst_creation.c \
			msh_export_index_lstadd_node.c \
			msh_get_cmd_path.c \
			msh_exec_external_cmd.c \
			msh_cmd_lst_utils_del_list.c \
			msh_utils.c	\
			msh_errors.c	

OBJS	= $(SRC:.c=.o)
OFILES = $(addprefix obj/, $(OBJS))

CC		= gcc

FLAGS	= -Wall -Werror -Wextra -g -fsanitize=address

#LEAKS = memory-leaks/memory_leaks.a

LIBFT_PATH = libft/libft.a

all:	$(NAME)

#	We cannot call (LIBFT) or (MLX42) in (NAME) because it would be searching for the
#	".a" files before creating them, resulting in an error. We 1st create the rules to
#	compile both libft and MLX42, and then we compile the .a files of both libraries
#	with the apropiate flags and frameworks.

$(NAME): $(OFILES) $(LIBFT_PATH)
		$(CC) $(FLAGS) $(LIB) $(OFILES) $(LIBFT_PATH) -o $(NAME)
		clear
		
$(OFILES): $(SRC)
		@mkdir -p obj/
		$(CC) $(FLAGS) $(INCLUDE) -c $(SRC)
		@mv *.o obj/

$(LIBFT_PATH):
		make -C libft all

# If a debug with lldb is needed, do 'make' with this rule:
debug: $(LIBFT_PATH)
		$(CC) $(FLAGS) $(SRC) $(LIBFT_PATH) -o $(NAME) -g
		clear

clean:
		rm -rf obj
		make -C libft clean

fclean: clean
		@make fclean -C libft/
		@rm $(NAME)

re:	fclean all

.PHONY: all clean fclean re
