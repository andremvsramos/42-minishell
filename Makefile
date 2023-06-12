# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 16:16:51 by andvieir          #+#    #+#              #
#    Updated: 2023/06/12 14:37:43 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft.a

#----------DIRS----------#

SRCDIR = ./src/
LIBFTDIR = ./libft/
HEADERDIR = ./headers/

SRC =	src/main.c \
		src/get_env.c \
		src/get_exp.c \
		src/env_exp_utils.c \
		src/prompt.c \
		src/cleanup_lists.c \
		src/cleanup.c \
		src/parsing.c \
		src/executer.c \
		src/exe_utils.c \
		src/expander.c \
		src/input_handling.c \
		src/signals.c \
		src/utils.c \
		src/utils_2.c \
		src/splitter.c \
		src/redirects.c \
		src/handle_errors.c \
		src/handle_quotes.c \
		src/handle_heredoc.c \
		src/built-ins/env.c \
		src/built-ins/unset.c \
		src/built-ins/export.c \
		src/built-ins/export_2.c \
		src/built-ins/echo.c \
		src/built-ins/pwd.c \
		src/built-ins/exit.c \

#----------COMMANDS----------#

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
AR = ar rcs
RM = rm -rf

OBJ = ${SRC:.c=.o}

#----------COLORS----------#
GREEN = \033[0;32m

#----------ART----------#
ART = " \n \
   ▄▄▄▄███▄▄▄▄    ▄█  ███▄▄▄▄    ▄█     ▄████████    ▄█    █▄       ▄████████  ▄█        ▄█       \n \
 ▄██▀▀▀███▀▀▀██▄ ███  ███▀▀▀██▄ ███    ███    ███   ███    ███     ███    ███ ███       ███       \n \
 ███   ███   ███ ███▌ ███   ███ ███▌   ███    █▀    ███    ███     ███    █▀  ███       ███       \n \
 ███   ███   ███ ███▌ ███   ███ ███▌   ███         ▄███▄▄▄▄███▄▄  ▄███▄▄▄     ███       ███       \n \
 ███   ███   ███ ███▌ ███   ███ ███▌ ▀███████████ ▀▀███▀▀▀▀███▀  ▀▀███▀▀▀     ███       ███       \n \
 ███   ███   ███ ███  ███   ███ ███           ███   ███    ███     ███    █▄  ███       ███       \n \
 ███   ███   ███ ███  ███   ███ ███     ▄█    ███   ███    ███     ███    ███ ███▌    ▄ ███▌    ▄ \n \
  ▀█   ███   █▀  █▀    ▀█   █▀  █▀    ▄████████▀    ███    █▀      ██████████ █████▄▄██ █████▄▄██ \n \
                                                                              ▀         ▀         \n"

#----------RULES----------#
.c.o:
#@$(CC) $(CFLAGS) -c -I$(HEADERDIR) $< -o ${<:.c=.o}
			@mkdir -p bin/$(dir $<)
			@$(CC) $(CFLAGS) -c -I$(HEADERDIR) $< -o bin/$*.o

all:		$(NAME)
			@echo $(ART)

$(LIBFT):
			@cd $(LIBFTDIR) && $(MAKE) -s

$(NAME):	$(OBJ) $(LIBFT)
			@$(CC) $(CFLAGS) $(OBJ:%=bin/%) -lreadline $(LIBFTDIR)$(LIBFT) -o $(NAME)

clean:
			@$(RM) $(OBJ:%=bin/%) $(OBJ_CHECKER)
			@rm -r bin/src
			@cd $(LIBFTDIR) && $(MAKE) -s clean

fclean:		clean
			@$(RM) $(NAME) $(BONUS) $(LIBFT)
			@cd $(LIBFTDIR) && $(MAKE) -s fclean

#aclean:		all clean

re:			fclean all
