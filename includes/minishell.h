/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:32:39 by imran             #+#    #+#             */
/*   Updated: 2022/04/25 21:51:16 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/all_includes.h"
# include "../libs/libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <unistd.h>

typedef struct s_data
{
	int	in_main_shell;
} t_data;

typedef struct	s_pipe
{
	char			**cmd;
	struct s_input	*prev;
	struct s_input	*next;
}	t_pipe;

# define DQUOTE 34
# define SQUOTE 39

char	*find_exec(char *prg, char	**paths);
char	*cmd_path(char	*cmd);
void	ft_free_arg(char **arr);
void	pipes(char *line);
void	execute(char *line);
void	err_print(int error);
void	err_free_parent(int **pipes, int *pids);
void	err_free_pipex(int **pipes, char ***args);
void	ft_free(int **arr);
void	ft_free_arg(char **arr);
void	ft_free_args(char ***arr);
char	**ft_split_path(char *s, char c);

//* Parsing
int		preliminary_check(char *str);
int		p_contains_unclosed_quotes(char *str);
int		p_first_element(char *str);
int		p_contains_backslashes(char *str);
int		p_contains_semicolons(char *str);
int		p_contains_invalid_redirs(char *str);

//* Signals
void	handle_signals(int signum);
int		in_minishell_var(int is_true);

#endif