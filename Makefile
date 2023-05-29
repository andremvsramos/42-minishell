# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 16:16:51 by andvieir          #+#    #+#              #
#    Updated: 2023/05/29 11:14:48 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft.a

#----------DIRS----------#

SRCDIR = ./src/
LIBFTDIR = ./libft/
HEADERDIR = ./headers/

SRC =	src/main.c \
		src/env.c \
		src/prompt.c \
		src/cleanup_lists.c \
		src/parsing.c \
		src/executer.c \
		src/expander.c \
		src/input_handling.c \
		src/signals.c \
		src/utils.c \
		src/splitter.c \
		src/handle_errors.c \
		src/handle_quotes.c \
		src/handle_heredoc.c \
		src/built-ins/env_print.c \
		src/built-ins/unset.c \
		src/built-ins/export.c \
		src/built-ins/echo.c \

#----------COMMANDS----------#

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
AR = ar rcs
RM = rm -rf

OBJ = ${SRC:.c=.o}

#----------RULES----------#
.c.o:
			@$(CC) $(CFLAGS) -c -I$(HEADERDIR) $< -o ${<:.c=.o}

all:		$(NAME)

$(LIBFT):
			cd $(LIBFTDIR) && $(MAKE)

$(NAME):	$(OBJ) $(LIBFT)
			@$(CC) $(CFLAGS) $(OBJ) -lreadline $(LIBFTDIR)$(LIBFT) -o $(NAME)

clean:
			$(RM) $(OBJ) $(OBJ_CHECKER)
			cd $(LIBFTDIR) && $(MAKE) clean

fclean:		clean
			$(RM) $(NAME) $(BONUS) $(LIBFT)
			cd $(LIBFTDIR) && $(MAKE) fclean

aclean:		all clean

re:			fclean all
