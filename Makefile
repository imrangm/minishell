# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/24 16:11:16 by nmadi             #+#    #+#              #
#    Updated: 2022/09/24 16:37:17 by nmadi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=		minishell

SRCS=		main.c \
			parsing/p_ast.c \
			parsing/p_redir.c \
			parsing/p_node.c \
			parsing/p_process.c \
			parsing/p_execute.c \
			parsing/p_lexer.c \
			parsing/p_token.c \
			parsing/p_toks.c \
			parsing/p_parse.c \
			parsing/p_scan.c \
			parsing/p_free.c \
			parsing/p_expansion.c \
			parsing/p_expander.c \
			parsing/p_print.c \
			checks/pc_valid.c \
			checks/pc_export.c \
			checks/pc_redirs.c \
			extractors/pe_env.c \
			extractors/pe_splits.c \
			extractors/pe_splitpath.c \
			extractors/pe_quotes.c \
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
			execution/e_signal.c \
			execution/e_rd.c \
			execution/e_redir.c \
			execution/e_fds.c \
			utils/u_env.c \
			utils/u_env_ii.c \
			utils/u_struct.c \
			utils/u_cmd.c \
			utils/u_misc.c \
			utils/u_misc_ii.c \
			utils/u_pipe.c \
			utils/u_redir.c \
			utils/u_child.c \
			utils/u_ast.c \
			utils/u_expansion.c \
			utils/u_readline.c \
			utils/u_readpipe.c \
			utils/u_fork.c \
			utils/u_redirs.c \
			utils/u_quote.c

CC =		gcc


ifeq ($(shell uname -s), Linux)
	CFLAGS =	-Wall -Wextra -Werror
	LDFLAGS =	-lreadline
endif

ifeq ($(shell uname -s), Darwin)
	CFLAGS	=	-Wall -Wextra -Werror -I /usr/local/Cellar/readline/8.1/include/
	LDFLAGS	=	-lreadline -L /usr/local/Cellar/readline/8.1/lib/
endif

LIBFT_A =	./libs/libft/libft.a

SRCS_DIR =	./srcs

.SILENT:

OBJS =		$(addprefix $(SRCS_DIR)/, $(SRCS:c=o))

all: $(NAME)
	echo "\033[0;32mCompiled minishell.\033[0m"

$(NAME): $(OBJS)
	$(MAKE) -C ./libs/libft/
	$(CC) $(OBJS) $(LIBFT_A) $(LDFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJS)
	$(MAKE) clean -C ./libs/libft/

fclean: clean
	rm -rf minishell
	$(MAKE) fclean -C ./libs/libft/

re: fclean all

valgrind:
	@clear
	@echo "\033[0;32mRunning in Valgrind.\033[0m"
	@valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=.ignore_readline ./minishell

.PHONY: all clean fclean re
