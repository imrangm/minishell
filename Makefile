# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/08 17:38:26 by imran             #+#    #+#              #
#    Updated: 2022/04/27 17:16:25 by imustafa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=		minishell

SRCS=		main.c \
 			execute.c \
			pipe.c \
			find.c \
			free.c \
			here_doc.c \
			file.c \
			append.c \
			error.c \
			chars_split.c \
			ft_split_path.c \
			handle_signals.c \
			preliminary_check.c \
			p_contains_unclosed_quotes.c \
			p_first_element.c \
			p_illegal_chars.c \
			p_contains_invalid_redirs.c \

CC =		gcc

# For Nart's home
# LDFLAGS =	-lreadline -L /opt/homebrew/opt/readline/lib/ -g3
# CFLAGS=	-Wall -Wextra -Werror -I /opt/homebrew/opt/readline/include/ -g3

# For Nart's 42
LDFLAGS	=	-lreadline -L /usr/local/Cellar/readline/8.1/lib/
CFLAGS	=	-Wall -Wextra -Werror -I /usr/local/Cellar/readline/8.1/include/

# For Dale's Linux
# LDFLAGS =	-lreadline
# CFLAGS =	-Wall -Wextra -Werror

LIBFT_A =	./libs/libft/libft.a

SRCS_DIR =	./srcs

.SILENT:

OBJS =		$(addprefix $(SRCS_DIR)/, $(SRCS:c=o))

$(NAME): $(OBJS)
	$(MAKE) -C ./libs/libft/
	@echo "\033[0;32mCompiled libft.\033[0m"
	$(CC) $(OBJS) $(LIBFT_A) $(LDFLAGS) -o $(NAME)
	@echo "\033[0;32mCompiled minishell.\033[0m"

all: $(NAME)

clean:
	rm -rf $(OBJS)
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