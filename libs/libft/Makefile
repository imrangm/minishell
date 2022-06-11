# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/05 19:01:08 by nmadi             #+#    #+#              #
#    Updated: 2022/06/10 16:18:52 by nmadi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_atoi.c \
		ft_bzero.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_memset.c \
		ft_strchr.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memcmp.c \
		ft_memchr.c \
		ft_memcpy.c \
		ft_strnstr.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_memmove.c \
		ft_strlcat.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_itoa.c \
		ft_striteri.c \
		ft_strmapi.c \
		ft_split.c \
		ft_matoi.c \
		ft_isspace.c \
		ft_isquote.c \
		ft_aredigits.c \
		ft_arespaces.c \
		ft_strcmp.c \
		ft_countoccurance.c \
		ft_counttochars.c \
		ft_count2darr.c

SRCS_BONUS = ft_lstadd_back.c \
		ft_lstadd_front.c \
		ft_lstclear.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstlast.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_lstsize.c

.SILENT:

CC = gcc
CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRCS:.c=.o)
OBJ_BONUS = $(SRCS_BONUS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) -c $(FLAGS) $(SRCS)
	ar -rc $(NAME) $(OBJ)

bonus : $(NAME) $(OBJ_BONUS)
	$(CC) -c $(FLAGS) $(SRCS_BONUS)
	ar -rc $(NAME) $(OBJ) $(OBJ_BONUS)

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
