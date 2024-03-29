# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 16:16:51 by andvieir          #+#    #+#              #
#    Updated: 2023/06/26 13:38:22 by marvin           ###   ########.fr        #
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
		src/handle_errors_2.c \
		src/dir_file_errors.c \
		src/handle_quotes.c \
		src/handle_heredoc.c \
		src/built-ins/env.c \
		src/built-ins/unset.c \
		src/built-ins/export.c \
		src/built-ins/export_2.c \
		src/built-ins/echo.c \
		src/built-ins/pwd.c \
		src/built-ins/exit.c \
		src/built-ins/cd.c \

#----------COMMANDS----------#

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
AR = ar rcs
RM = rm -rf

OBJ = ${SRC:.c=.o}

#----------COLORS----------#
GREEN = \033[0;32m
YELLOW = \033[0;33m
CYAN = \033[1;36m

#--------ART & TEXT--------#
MS = " [ Compiled Minishell ] "
LFT = " [ Compiled Libft ] "

#----------RULES----------#
.c.o:
#@$(CC) $(CFLAGS) -c -I$(HEADERDIR) $< -o ${<:.c=.o}
			@mkdir -p bin/$(dir $<)
			@$(CC) $(CFLAGS) -c -I$(HEADERDIR) $< -o bin/$*.o

all:		$(NAME)
			@echo "$(GREEN)$(MS)"
			@echo "$(CYAN) [ Generated: $(NAME) ] "

$(LIBFT):
			@cd $(LIBFTDIR) && $(MAKE) -s
			@echo "$(YELLOW)$(LFT)"

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
