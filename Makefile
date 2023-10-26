# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/18 13:12:22 by roruiz-v          #+#    #+#              #
#    Updated: 2023/10/20 20:59:25 by roruiz-v         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRC		=	main.c \
			msh_env_lst_utils_dupl_env.c \
			msh_env_lst_utils_add_mfy_nds.c \
			msh_env_lst_utils_del_nds.c \
			msh_env_lst_utils_print_nds.c \
			msh_index_lst_creation.c \
			msh_index_lstadd_node.c \
			msh_utils.c			

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
		$(CC) $(FLAGS) $(OFILES) $(LIBFT_PATH) -o $(NAME)
		clear
		
$(OFILES): $(SRC)
		@mkdir -p obj/
		$(CC) $(FLAGS) -c $(SRC)
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
