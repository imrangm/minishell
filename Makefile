# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/08 17:38:26 by imran             #+#    #+#              #
#    Updated: 2022/06/07 16:33:51 by nmadi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=		minishell

SRCS=		main.c \
			_misc/parse.c \
 			_misc/master_execute.c \
			_misc/get_cmd_path.c \
			_misc/error.c \
			_misc/check.c \
			_misc/handle_signals.c \
			_misc/ft_split_chars.c \
			_misc/ft_split_path.c \
			_misc/ft_split_line.c \
			_misc/ft_split_rd.c \
			_misc/ft_split_pp.c \
			_misc/expand_envs.c \
			_misc/set_quote_mode.c \
			_misc/init_envp.c \
			_misc/free_struct.c \
			_misc/smart_split.c \
			parsing/checks/p_valid.c \
			parsing/checks/p_quotes.c \
			parsing/checks/p_chars.c \
			parsing/checks/p_export.c \
			parsing/checks/p_redirs.c \
			parsing/checks/p_mode.c \
			builtins/b_env.c \
			builtins/b_pwd.c \
			builtins/b_echo.c \
			builtins/b_cd.c \
			builtins/b_export.c \
			builtins/b_unset.c \
			builtins/b_exit.c \
			execution/e_cmd.c \
			execution/e_process.c \
			execution/e_pipe.c \
			execution/e_fork.c \
			execution/e_child.c \
			execution/e_file.c \
			utils/utility.c \
			utils/u_env.c \
			utils/u_cd.c \
			utils/u_free.c \

CC =		gcc

LDFLAGS =	-lreadline -L ./libs/readline/lib/
CFLAGS=	-Wall -Wextra -Werror -I ./libs/readline/include/

LIBFT_A =	./libs/libft/libft.a

SRCS_DIR =	./srcs

.SILENT:

OBJS =		$(addprefix $(SRCS_DIR)/, $(SRCS:c=o))

$(NAME): $(OBJS)
	mkdir -p ./objs
	mv ./srcs/_misc/*.o objs/
	mv ./srcs/builtins/*.o objs/
	mv ./srcs/execution/*.o objs/
	mv ./srcs/utils/*.o objs/
	mv ./srcs/parsing/checks/*.o objs/
	mv ./srcs/main.o objs/
	$(MAKE) -C ./libs/libft/
	@echo "\033[0;32mCompiled libft.\033[0m"
	$(CC) ./objs/*.o $(LIBFT_A) $(LDFLAGS) -o $(NAME)
	@echo "\033[0;32mCompiled minishell.\033[0m"

all: $(NAME)

clean:
	rm -rf ./objs/
	@echo "\033[0;32mCleaned minishell object files.\033[0m"
	$(MAKE) clean -C ./libs/libft/
	@echo "\033[0;32mCleaned libft object files.\033[0m"

fclean: clean
	rm -rf minishell
	@echo "\033[0;32mCleaned executable.\033[0m"
	$(MAKE) fclean -C ./libs/libft/
	@echo "\033[0;32mCleaned libft archive file.\033[0m"

re: fclean all

valgrind: $(NAME)
	@echo "\033[0;32mRunning in Valgrind.\033[0m"
	@valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --suppressions=.ignore_readline ./minishell

mega: all clean

.PHONY: all clean fclean re