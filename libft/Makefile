# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/23 14:12:00 by roruiz-v          #+#    #+#              #
#    Updated: 2023/08/08 13:19:42 by roruiz-v         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

HDRS = libft.h

SRC		=	ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_strlen.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_freedom.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_p0x_fd_len.c \
			ft_pp_fd_len.c \
			ft_printf.c \
			ft_putchar_fd_len.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd_len.c \
			ft_putnbr_fd.c \
			ft_putnhex_fd_len.c \
			ft_putstr_fd_len.c \
			ft_putstr_fd.c \
			ft_putuint_fd_len.c \
			get_next_line.c \
			get_next_line_utils.c

OBJS = $(SRC:.c=.o)

SRCB	=	ft_lstnew_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstmap_bonus.c				

OBJSB = $(SRCB:.c=.o)

FLAGS	= -Wall -Werror -Wextra

.c.o:
	gcc -c $(FLAGS) $< -o $(<:.c=.o)

all:	$(NAME)

$(NAME): $(OBJS)
	ar -crs $(NAME) $(OBJS)
		
clean:
	rm -f $(OBJS) $(OBJSB)

fclean: clean
	rm -f $(NAME)

re:	fclean all

bonus: $(OBJS) $(OBJSB) $(HDRS)
	ar -cr $(NAME) $(OBJS) $(OBJSB)
	ranlib $(NAME)

.PHONY: all clean fclean re bonus

# ar -s crea la indexación
# hace lo mismo que ranlib $(NAME), por ejemplo