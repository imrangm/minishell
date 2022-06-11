# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/08 17:38:26 by imran             #+#    #+#              #
#    Updated: 2022/06/11 17:27:16 by nmadi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=		minishell

SRCS=		main.c \
			parsing/checks/pc_valid.c \
			parsing/checks/pc_quotes.c \
			parsing/checks/pc_chars.c \
			parsing/checks/pc_export.c \
			parsing/checks/pc_redirs.c \
			parsing/checks/pc_mode.c \
			parsing/checks/pc_end.c \
			parsing/checks/pc_pipe.c \
			parsing/extractors/pe_rd.c \
			parsing/extractors/pe_env.c \
			parsing/extractors/pe_splitrd.c \
			parsing/extractors/pe_splitpp.c \
			parsing/extractors/pe_splits.c \
			parsing/extractors/pe_splitpath.c \
			builtins/b_env.c \
			builtins/b_pwd.c \
			builtins/b_echo.c \
			builtins/b_cd.c \
			builtins/b_export.c \
			builtins/b_unset.c \
			builtins/b_exit.c \
			execution/e_exec.c \
			execution/e_cmd.c \
			execution/e_process.c \
			execution/e_pipe.c \
			execution/e_fork.c \
			execution/e_child.c \
			execution/e_file.c \
			execution/e_signal.c \
			execution/e_rd.c \
			utils/utility.c \
			utils/u_env.c \
			utils/u_struct.c \
			utils/u_cd.c \
			utils/u_free.c \
			utils/u_error.c \
			utils/u_cmd.c \

CC =		gcc

# Homebrew Flags
LDFLAGS =	-lreadline -L /opt/homebrew/opt/readline/lib/
CFLAGS=	-Wall -Wextra -Werror -I /opt/homebrew/opt/readline/include/

# M1 Flags
# LDFLAGS =	-lreadline -L ./libs/readline/lib/
# CFLAGS=	-Wall -Wextra -Werror -I ./libs/readline/include/

# 42 Flags
# LDFLAGS	=	-lreadline -L /usr/local/Cellar/readline/8.1/lib/
# CFLAGS	=	-Wall -Wextra -Werror -I /usr/local/Cellar/readline/8.1/include/

# Linux Flags
# LDFLAGS =	-lreadline
# CFLAGS =	-Wall -Wextra -Werror

LIBFT_A =	./libs/libft/libft.a

SRCS_DIR =	./srcs

.SILENT:

OBJS =		$(addprefix $(SRCS_DIR)/, $(SRCS:c=o))

$(NAME): $(OBJS)
	mkdir -p ./objs
	mv ./srcs/builtins/*.o objs/
	mv ./srcs/execution/*.o objs/
	mv ./srcs/utils/*.o objs/
	mv ./srcs/parsing/checks/*.o objs/
	mv ./srcs/parsing/extractors/*.o objs/
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