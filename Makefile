# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/08 17:38:26 by imran             #+#    #+#              #
#    Updated: 2022/04/21 18:06:38 by imustafa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell

INCLUDE= imran.h

SRCS= 	execute.c \
		pipe.c \
		here_doc.c \
		chars_split.c \
		find.c \
		free.c \
		error.c \
		main.c \

.SILENT:

CC = gcc

CFLAGS= -Wall -Wextra -Werror

LFLAGS = -lreadline

LIBFT = ./libs/libft/libft.a

OBJS_DIR = ./objs

SRCS_DIR = ./srcs

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:c=o))

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C ./libs/libft/
	@echo "\033[0;32mCompiled libft.\033[0m"
	$(CC) $(CFLAGS) $(LIBFT) $(LFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[0;32mCompiled minishell.\033[0m"

all: $(NAME)

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJS_DIR)
	@echo "\033[0;32mCleaned minishell object files.\033[0m"
	$(MAKE) clean -C ./libs/libft/
	@echo "\033[0;32mCleaned libft object files.\033[0m"

fclean: clean
	rm -rf minishell
	@echo "\033[0;32mCleaned executable.\033[0m"
	$(MAKE) fclean -C ./libs/libft/
	@echo "\033[0;32mCleaned libft archive file.\033[0m"

re: fclean all

.PHONY: all clean fclean re