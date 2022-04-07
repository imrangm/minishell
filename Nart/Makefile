# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/07 12:55:48 by nmadi             #+#    #+#              #
#    Updated: 2022/04/07 18:11:05 by nmadi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c \
		minishell.c \
		interpret.c \
		parse.c \

.SILENT:

OBJS = $(SRCS:c=o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LFLAGS = -lreadline

LIBFT = ./libft/libft.a

$(NAME): $(OBJS)
	$(MAKE) -C ./libft/
	@echo "\033[0;32mCompiled libft.\033[0m"
	$(CC) $(CFLAGS) $(LIBFT) $(LFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[0;32mCompiled minishell.\033[0m"

all: $(NAME)

clean:
	rm -rf $(OBJS)
	@echo "\033[0;32mCleaned minishell object files.\033[0m"
	$(MAKE) clean -C ./libft/
	@echo "\033[0;32mCleaned libft object files.\033[0m"

fclean: clean
	rm -rf minishell
	@echo "\033[0;32mCleaned executable.\033[0m"
	$(MAKE) fclean -C ./libft/
	@echo "\033[0;32mCleaned libft archive file.\033[0m"

re: fclean all

.PHONY: all clean fclean re