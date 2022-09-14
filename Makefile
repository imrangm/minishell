# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/08 17:38:26 by imran             #+#    #+#              #
#    Updated: 2022/09/14 13:06:53 by imustafa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=		minishell

SRCS=		main.c \
			parsing/p_AST.c \
			parsing/p_redir.c \
			parsing/p_node.c \
			parsing/p_process.c \
			parsing/p_execute.c \
			parsing/p_lexer.c \
			parsing/p_parse.c \
			parsing/p_scan.c \
			parsing/p_utils.c \
			parsing/p_free.c \
			parsing/p_print.c \
			checks/pc_valid.c \
			checks/pc_export.c \
			checks/pc_redirs.c \
			checks/pc_pipe.c \
			extractors/pe_env.c \
			extractors/pe_splits.c \
			extractors/pe_splitpath.c \
			builtins/b_env.c \
			builtins/b_pwd.c \
			builtins/b_echo.c \
			builtins/b_cd.c \
			builtins/b_export.c \
			builtins/b_unset.c \
			builtins/b_exit.c \
			execution/e_exec.c \
			execution/e_cmd.c \
			execution/e_pipe.c \
			execution/e_fork.c \
			execution/e_child.c \
			execution/e_file.c \
			execution/e_signal.c \
			execution/e_rd.c \
			execution/e_builtin.c \
			execution/e_fds.c \
			utils/u_env.c \
			utils/u_env_ii.c \
			utils/u_struct.c \
			utils/u_cmd.c \
			utils/u_token.c \
			utils/u_misc.c \
			utils/u_misc_ii.c \
			utils/u_misc_iii.c \
			utils/u_pipe.c

CC =		gcc

# # Homebrew Flags
# LDFLAGS =	-lreadline -L /opt/homebrew/opt/readline/lib/
# CFLAGS=	-Wall -Wextra -Werror -g3 -I /opt/homebrew/opt/readline/include/

# M1 Flags
LDFLAGS =	-lreadline -L ./libs/readline/lib/
CFLAGS=	-Wall -Wextra -Werror -I ./libs/readline/include/

# 42 Flags
# LDFLAGS	=	-lreadline -L /usr/local/Cellar/readline/8.1/lib/
# CFLAGS	=	-Wall -Wextra -Werror -I /usr/local/Cellar/readline/8.1/include/ -g3

# Linux Flags
# LDFLAGS =	-lreadline
# CFLAGS =	-Wall -Wextra -Werror -g3

LIBFT_A =	./libs/libft/libft.a

SRCS_DIR =	./srcs

.SILENT:

OBJS =		$(addprefix $(SRCS_DIR)/, $(SRCS:c=o))

$(NAME): $(OBJS)
	$(MAKE) -C ./libs/libft/
	$(CC) $(OBJS) $(LIBFT_A) $(LDFLAGS) -o $(NAME)
	@echo "\033[0;32mCompiled minishell.\033[0m"

all: $(NAME)

clean:
	rm -rf $(OBJS)
	$(MAKE) clean -C ./libs/libft/

fclean: clean
	rm -rf minishell
	$(MAKE) fclean -C ./libs/libft/

re: fclean all

valgrind: re $(clear)
	@echo "\033[0;32mRunning in Valgrind.\033[0m"
	@valgrind --leak-check=full --track-fds=yes --track-origins=yes --show-leak-kinds=all --suppressions=.ignore_readline ./minishell

v: $(clear)
	@echo "\033[0;32mRunning in Valgrind.\033[0m"
	@valgrind --leak-check=full --track-fds=yes --track-origins=yes --show-leak-kinds=all --suppressions=.ignore_readline ./minishell

run: re clean
	@clear && ./minishell

.PHONY: all clean fclean re