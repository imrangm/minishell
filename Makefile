# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/08 17:38:26 by imran             #+#    #+#              #
#    Updated: 2022/05/27 14:14:40 by nmadi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=		minishell

SRCS=		main.c \
			process.c \
			parse.c \
			utility.c \
 			master_execute.c \
			pipe.c \
			fork.c \
			child.c \
			find.c \
			free.c \
			file.c \
			error.c \
			check.c \
			ft_split_chars.c \
			ft_split_path.c \
			ft_split_line.c \
			ft_split_rd.c \
			handle_signals.c \
			preliminary_check.c \
			p_contains_unclosed_quotes.c \
			p_is_empty_input.c \
			p_contains_illegal_special_chars.c \
			p_contains_invalid_redirs.c \
			b_env.c \
			b_pwd.c \
			b_echo.c \
			b_cd.c \
			exec_cmd_child.c \
			exec_cmd_parent.c \
			utils_env.c \
			m_atoi.c \
			are_digits.c \
			expand_envs.c \
			p_env_error.c \
			set_quote_mode.c \
			is_redir_mode.c \
			ft_split_pp.c \
			is_pipe_mode.c \
			b_export.c \
			b_unset.c \
			b_exit.c \
			cmp_str.c \
			init_envp.c \
			free_struct.c \
			# utils_shlvl.c \

CC =		gcc

# For home
# LDFLAGS =	-lreadline -L /opt/homebrew/opt/readline/lib/
# CFLAGS=	-Wall -Wextra -Werror -I /opt/homebrew/opt/readline/include/

# For 42
LDFLAGS	=	-lreadline -L /usr/local/Cellar/readline/8.1/lib/
CFLAGS	=	-Wall -Wextra -Werror -I /usr/local/Cellar/readline/8.1/include/

# For Linux
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