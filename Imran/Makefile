# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/08 17:38:26 by imran             #+#    #+#              #
#    Updated: 2022/04/19 11:28:10 by imustafa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell

INCLUDE= imran.h

SRCS= 	execute.c \
		pipe.c \
		find.c \
		free.c \
		error.c \
		main.c \

CFLAGS= -Wall -Wextra -Werror

LFLAGS = -lreadline

LIBFT = ./libft/libft.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(SRCS) $(INCLUDE)
	$(MAKE) -C ./libft/
	gcc $(CFLAGS) $(LIBFT) $(LFLAGS) $(SRCS) -I $(INCLUDE) -o $(NAME)

clean:
	rm -f $(NAME)
	$(MAKE) clean -C ./libft/

fclean: clean
	$(MAKE) fclean -C ./libft/
	
re: fclean all