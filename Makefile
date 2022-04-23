# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/08 17:38:26 by imran             #+#    #+#              #
#    Updated: 2022/04/23 04:22:10 by nmadi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=		minishell

SRCS=		main.c \
 			execute.c \
			pipe.c \
			find.c \
			free.c \
			error.c \
			ft_split_path.c \
			is_valid_input.c \
			are_valid_backslashes.c \
			are_valid_quotes.c \
			is_valid_redirection_syntax.c \
			handle_signals.c \
			is_valid_syntax.c \
			ft_split_line.c

CC =		gcc

.SILENT:

# For Nart's home
LDFLAGS =	-lreadline -L /opt/homebrew/opt/readline/lib/

# For Nart's 42
# LDFLAGS =	-lreadline -L /usr/local/Cellar/readline/8.1/lib/

# For Nart's home
CFLAGS=		-Wall -Wextra -Werror -I /opt/homebrew/opt/readline/include/

# For Nart's 42
# CFLAGS=		-Wall -Wextra -Werror -I /usr/local/Cellar/readline/8.1/include/

LIBFT_A =	./libs/libft/libft.a

SRCS_DIR =	./srcs

OBJS =		$(addprefix $(SRCS_DIR)/, $(SRCS:c=o))

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ./libs/libft/
	@echo "\033[0;32mCompiled libft.\033[0m"
	$(CC) $(OBJS) $(LIBFT_A) $(LDFLAGS) -o $(NAME)
	@echo "\033[0;32mCompiled minishell.\033[0m"

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