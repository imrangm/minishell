# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imran <imran@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/08 17:38:26 by imran             #+#    #+#              #
#    Updated: 2022/04/08 17:43:05 by imran            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell

INCLUDE= imran.h

SRCS= 	execute.c \
		find.c \
		libft.c \
		main.c \

CFLAGS= -Wall -Wextra -Werror

LFLAGS = -lreadline

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(SRCS) $(INCLUDE)
	gcc $(CFLAGS) $(LFLAGS) $(SRCS) -I $(INCLUDE) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean
re: fclean all